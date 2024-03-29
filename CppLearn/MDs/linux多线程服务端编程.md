___this file is my knowledge about <linux多线程服务端编程>___


1.  对象要做到线程安全，唯一的要求就是在构造期间不要泄露this指针，即   
    1.  不要在构造函数中注册任何回调   
    2.  也不要在构造函数中把this传给跨线程的对象   
    3.  即使在构造函数的最后一行也不能泄露this指针    
    之所以这么规定，是因为在构造函数执行期间对象还没有完成初始化，如果this被泄露给了其他对象(其自身创建的子对象除外)，那么别的线程访问这个半成品对象，那么别的线程有可能访问这个半成品对象，这会造成难以预料的结果。   

    ```
	// 不能这么做
	class Foo : public Observer
	{
	public:
	    Foo(Observable *s)
	    {
	        s->register_(this); // 错误，非线程安全
	    }
	
	    virtual void update();
	};
	
	// 要这么做
	class Foo : public Observer
	{
	public:
	    Foo();
	    virtual void update();
	
	    //另外定义一个函数，在构造之后执行回调函数的注册工作
	    void observe(Observable *s)
	    {
	        s->register_(this);
	    }
	};
	
	Foo *pFoo = new Foo;
	Observable *s = getSubject();
	pFoo->observe(s);// 二段式构造，或者直接写s->register_(pFoo)
    ```

    这说明，二段式构造--即构造函数+initialize()，有时候这是一个好办法，这虽然不符合C++教条，但是多线程下别无选择。另外，既然允许二段式构造，哪儿构造函数不必主动抛出异常，调用方法仍然是靠initialize()的返回值来判断对象是否构造成功，这能简化错误的处理。   
    即使构造函数的最后一行也不要泄露this，因为Foo有可能是个基类，基类先于派生类构造，执行完Foo::Foo()的最后一行代码还会继续执行派生类的构造函数，这时候most-derived class的对象还处于构造中，仍然不安全。    
    总的来说，构造函数做到线程安全容易，析构函数做到线程安全麻烦。    
2.  对象析构，单线程不是问题，最多需要避免空悬指针和野指针。对一般成员函数而言，做到线程安全的办法是让他们顺序执行，而不要并发执行(关键是不要同时读写共享状态)，也就是让每个成员函数的临界区不重叠。   
3.  成员函数用来保护临界区的互斥器本身必须是有效的。而析构函数破坏了这一假设，他会把mutex成员变量销毁掉。      
4.  mutex并不是多线程的办法。mutex只能保证函数一个接一个的执行。考虑以下代码:    

    ```
    //
    Foo::~Foo()
    {
        MutexLockGuard lock(mutex_);
        //free internal state (1)
    }

    //
    void Foo::update()
    {
        MutexLockGuard lock(mutex_)// (2)
        // make use of internal state
    }
    ```

    此时A/B两个线程都能看到Foo对象x，线程A即将销毁x，而线程B正准备调用 `x->update()` 。   

    ```
    extern Foo *x;//visible by all threads

    //thread A
    delete x;
    x = NULL;//helpless

    //thread B
    if (x)
    {
        x->update();
    }
    ```

    尽管线程A在销毁独享之后把指针置为NULL，尽管线程B在调用x的成员函数之前检查了指针x的值，但是还是无法避免一种竞态条件.   
    -  线程A执行到了析构函数的(1)处，已经持有了互斥锁，即将向下执行。   
    -  线程B通过了if(x)检测，阻塞在(2)处。    
    接下来发生什么就不知道了。   

5.  如果要同时读写一个class的两个对象，有潜在的死锁的可能。比如有一个swap():   

    ```
	void swap(Counter &a, Counter &b)
	{
	    MutexLockGuard a_lock(a.mutex_); //potential dead lock
	    MutexLockGuard b_lock(b.mutex_);
	    int64_t value = a.value_;
	    a.value_ = b.value_;
	    b.value_ = value;
	}
    ```

    如果线程A执行swap(a,b)，而同时线程B执行swap(b,a)，就有可能死锁。operator=()也是这个道理。    

    ```
	Counter& Counter::operator::operator=(const Counter &rhs)
	{
	    if (this == &rhs)
	    {
	        return *this;
	    }
	
	    MutexLockGuard my_lock(mutex_); //potential dead lock
	    MutexLockGuard its_lock(rhs.mutex_);
	    value_ = rhs.value_;// 改成value_ = rhs.value()会死锁
	    return *this;
	}
    ```

    一个函数如果要锁住相同类型的多个对象，为了保证始终按相同的顺序加锁，我们可以比较mutex对象的地址，始终先加锁地址较小的mutex。     
6.  对象的关系主要有三种：composition(组合)/aggregation(聚合)/association(关联)。组合关系在多线程里面不会遇到什么麻烦，因为对象x的生命周期由其唯一的拥有者owner控制(我猜测就是一个class A内定义另一个class B，class B不是指针和引用，仅仅是class B的一个实例)。关联表示一个对象a用到了另一个对象b，调用了后者的成员函数。从代码形式看，a持有b的指针(或引用)，但是b的生命周期不由a单独控制。聚合关系从形式上看雨关联相同，除了a和b有逻辑上的整体与部分的关系。如果b是动态创建的并在整个程序结束前有可能被释放，就会出现竞态条件。一个简单的解决办法是：只创建不销毁。程序使用一个对象池来暂存用过的对象，下次申请新的对象时，如果对象池里有存货，就重复利用现有的对象，否则就新建立一个。对象用完了，不是直接放掉，而是放回池子里。这个方法有缺点，但是至少能避免访问失效对象的情况发生。这种山寨的方法是:   
    1.  对象池的线程安全，如果安全的、完整的把对象放回池子里，防止出现“部分放回”的竞态？(线程A认为对象x已经放回，线程B认为对象x还活着)。   
    2.  全局共享数据引发的锁竞争，这个集中化的对象池会不会把多线程并发的操作串行化？   
    3.  如果共享对象的类型不止一种，那么是重复实现对象池还是使用类模板？   
    4.  会不会造成内存泄露与分片？因为对象池占用的内存只增不减，而且多个对象池不能共享内存。    
    如果对象x注册了任何非静态成员函数回调，那么必然会在某处持有了指向x的指针，这就暴露在竞态条件之下。    

6.  一个典型的场景是观察着模式：   

    ```
    class Observer // : boost::noncopyable
    {
    public:
        virtual ~Observer();
        virtual void Update();

        //...
    };

    class Observable // : boost::noncopyable
    {
    pulic:
        void Register_(Observer *x);
        void Unregister(Observer *x);

        void NotifyObersers()
        {
            for (Oberver *x : observer_)
            {
                x->update();
            }
        }

    private:
        std::verctor<Observers*> observers_;
    };
    ```

    上面的代码中，在Observable通知每个Observer时，它从何得知Observer对象x还活着？
    
    ```    
    class Observer
    {
        void Observe(Observable *s)
        {
            s->Register_(this);
        }

        virtual ~Observer()
        {
            subject_->Unregister(this);
        }

        Observable *subject_;
    };
    ```

    这段代码中，让Observer的析构函数去调用Unregister(this), 这里有两个竞态条件。其一：`subject_->Unregister(this)`中，如果知道subject_还活着？其二：就算subjects_是永久存在的对象，还存在两个问题：
    1.  线程A执行到`subject_->Unregister(this)`之前，还没有来得及Unregiser本对象。  
    2.  线程B执行到`x->Update()`，x正好指向`subject_->Unregister(this)`中正在析构的对象。  
    这时候x所指向的Observer对象正在西沟，调用它的任何非京台成员函数都是不安全的，何况虚函数。更糟糕的是Observer是个基类，执行到 `subject_->Unregister` 的时候，派生类对象已经析构掉了。

7.  原始指针在多线程的时候不要使用。  
8.  shared\_ptr和weak\_ptr：  
    1.  shared\_ptr控制对象的生命期，shared\_ptr是强引用，只要有一个指向x对象的shared\_ptr存在，该x对象就不会析构。当指向对象x的最后一个shared\_ptr析构活着reset()的时候，x保证会被销毁。
    2.  weak\_ptr不控制对象的生命期，但是他知道对象是否活着。如果对象还活着，那么他可以提升为有效的shared\_ptr；如果对象已经死了，提升会失败，返回一个空的share\_ptr，"提升/lock()"行为是线程安全的。  
    3.  shared\_ptr/weak\_ptr的“计数”在主流平台是原子操作。 
    4.  shared\_ptr/weak\_ptr的线程安全级别与std::string和STL容器一样。  
9.  C++里面可能出现的内存问题大致有以下几个方面：
    1.  缓冲区溢出, 用std::vector<char>/std::string或者自己编写的buffer class来管理缓冲区，自动基础缓冲区的长度，并通过成员函数而不是裸指针来修改缓冲区。    
    2.  空悬指针/野指针，用shared\_ptr/weak\_ptr  
    3.  重复释放， 用scoped\_ptr，只在对象析构的时候释放一次 
    4.  内存释放， 用scoped\_ptr, 对象析构的时候自动释放内存  
    5.  不配对的new[]/delete，把new[]统统替换为std::vector/scoped\_array  
    6.  内存碎片   
    正确使用智能指针能轻易解决前面5个问题。
    需要注意：scoped\_ptr/shared\_ptr/weak_ptr都是值语意，要么是栈上面的对象，要么是其他对象的直接数据成员，或者是标准库容器里的元素，几乎不会出现下面的用法：

        ```
        shared_ptr<Foo> *Foo = new shared_ptr<Foo>(new Foo);
        ```

    还要注意，如果这几种智能指针是对象x的数据成员，而它的模板参数T是incoplete类型，那么x的析构函数不能是默认的或者内联的，必须在.cpp中显式定义，否则会出现编译或者运行出错。   

0.  上面Observer模式的竞态条件用下面的代码解决:   

    ```
    class Observable
    {
    public:
        void Register_(weak_ptr<Observer> x);
        void NotifyObservers();

    private:
        mutable MutexLock mutex_;
        std::vector<weak_ptr<Observer> observers_;
        typedef std::vector<weak_ptr<Observer> >::iterator Iterator;
    };

    void Observable::NotifyObservers()
    {
        MutexLockGuard lock(mutex_);
        Iterator it = observers_.begin();

        while (it != observers_.end())
        {
            shared_ptr<Observer> obj(it->lock());

            if (obj)
            {
                obj->Update(); //现在的引用计数值至少为2，而且没有竞态条件，因为obj在栈上，对象不可能在本作用域内被销毁。 
                ++it;
            }
            else
            {
                it = observers_.erase(it); //对象以销毁，从容器中拿掉weak_ptr
            }
        }
    }
    ```

    虽然上面的部分解决了线程安全问题，但还有以下几个一点：
    1.  __侵入性__: 强制要求Observer必须以shared\_ptr来管理。  
    2. __不是完全线程安全__: Observer的析构函数会调用`subject_->Unregister(this)`，万一subject\_已经不复存在了呢？为了解决它，又要求Observable本身是用shared\_ptr管理的，并且subject\_ 多半是个weak\_ptr<Observable>.  
    3.  __锁征用__: 即Observable的三个成员函数都用了互斥器同步，这会造成Register()和Unregister()等待NotifyObservers(), 而后者的执行时间是无线的，因为他同步回调了用户提供的Update()函数。我们希望Register()和Unregister()的执行时间不会超过某个固定的上限。
    4.  万一 `obj->Update()` 虚函数中调用了(un)register函数呢？如果mutex\_ 是不可重入的，那么会死锁；如果mutex\_是可重入的，程序会绵连迭代器失效。因为vector observers\_在遍历期间被意外的修改了。但是我觉得mutex最好是不可重入的。

1.  share\_ptr本身不是100%线程安全的。它的引用计数本身是安全且无锁的，但是对象的读写不是，因为shared\_ptr又两个数据成员，读写操作不能原子化。shared\_ptr的线程安全级别和内建类型、标准库容器、std::string一样，即： 
    1.  一个shared\_ptr对象实体可被多个线程同时读取
    2.  两个shared\_ptr对象实体可以被两个线程同时写入，“析构”算是写操作。  
    3.  如果要从多个线程读写同一个share\_ptr对象，那么需要加锁。
    以上仅仅是share\_ptr对象本身的线程安全级别，不是它管理的对象那个的线程安全级别。
    要在多个线程同时访问同一个shared\_ptr，正确的做法是用mutex保护：

    ```
    MutexLoc mutex; //不需要读写锁
    shared_ptr<Foo> globalPtr;

    void diit(const shared_ptr<Foo> &pFoo); //把globalPtr安全的传给doit()
    ```

    globalPtr能够被多个线程看到，那么它的读写需要加锁，我们不必使用读写锁，而是使用最简单的互斥锁。因为临界区非常小，用互斥锁也不会阻塞并发读。  
    
    ```
    为了拷贝globalPtr，需要在读取他的时候加锁，即： 
    void read()
    {
        shared_ptr<Foo> localPtr;
        
        {
            MutexLockGuard lock(mutex);
            localPtr = globalPtr; //read globalPtr
        } 

        doit(localPtr); //user local Ptr since here
    }

    void write()
    {
        shared_ptr<Foo> newPtr(new Foo); //对象的创建在临界区之外
    
        {
            MutexLockGuard lock(mutex);
            globalPtr = newPtr; //write to globalPtr
        
            doit(newPtr); //use newPtr since here, 无需加锁
        }
    }      
    ```

    注意到上面的read()和write()在临界区外都没有再访问globalPtr，而是使用了一个指向同一个Foo对象那个的栈上shared\_ptr local copy，只要有这么个存在，shared\_ptr作为参数传递时不必复制，用const引用作为参数即可。另外上面的new Foo是在临界区之外执行的。这种写法通常比在临界区诶写globalPtr.reset(new Foo)要好，因为缩短了临界区的长度。  
2.  __shared\_ptr 意外延长了对象那个的生命周期__, 只要指向x对象的shared\_ptr存在，那么该对象就不会析构掉。另外一个出错的地方可能是boost::bind， 因为boost::bind会把实参拷贝一份，如果参数是一个shared\_ptr，那么对象那个的生命周期就不会短于boost::function对象：

    ```
    class Foo
    {
        void doit();
    };

    shared_ptr pFoo(new Foo);
    boost::functioni<void()> func = boost::bind(&Foo::doit, pFoo); 延长了foo的生存期限 
    ```

    这里的func对象持有了shared\_ptr的一份拷贝，有可能在不经意期间延长了倒数第二行创建的Foo对象的生命周期。  
    __函数参数__：因为要修改引用计数(而且拷贝的时候通常要加锁)，shanred\_ptr的拷贝开销被拷贝原始指针要搞，但是需要拷贝的时候并不多，多数情况下可以使用const引用方式，一个线程只需要在最外层函数有一个实体对象，之后都可以用const引用的方式来使用这个shared\_ptr：

    ```
    void save(const shared_ptr<Foo> &pFoo);
    void validateAccount(const Foo &foo);

    bool validate(const shared_ptr<Foo> &pFoo)
    {
        if (validate(pFoo)) //没有拷贝pFoo
        {
            save(pFoo); //没有拷贝pFoo
        }
    }

    那么通常，我们可以传入常引用
    void onMessage(const string &msg)
    {
        shared_ptr<Foo> pFoo(new Foo(msg)); //只要在最外层持有一个实体，安全不成问题
        
        if (validate(pFoo)) //没有拷贝pFoo
        {
            save(pFoo); //没有拷贝pFoo
        }
    }
    ```

    遵照这个规则，基本上不会遇到反复拷贝shared\_ptr导致的性能问题，因为pFoo是栈上面的对象，不可能被别的线程看到，那么读取始终是线程安全的。   
    __析构动作在创建时被捕获__: 这意味着：   
    1.  虚析构不再是必须的
    2.  shared\_ptr<void>可以持有任何对象，而且能够安全的释放
    3.  shared\_ptr对象可以安全的扩月模块的边界，比如从DLL里返回，而不会造成从模块A分配的内存在模块B里被释放这种错误。
    4.  二进制的兼容性，几遍Foo对象的大小变了，那么旧的客户代码仍然可以使用新的动态库，而无需重新编译。前提是Foo的头文件中不出现访问对象的成员的inline函数，并且Foo对象由动态库中的Factory构造，返回其shared\_ptr。
    5.  析构动作可以定制，因为shared\_ptr<T>只有一个模板参数，而析构行为可以是函数指针、仿函数或者其他什么东西，这是泛型编程和面向对象编程的一次完美结合。
    __析构所在的线程__: 对象的析构是同步的，当最后一个指向x的shared\_ptr离开其作用域的时候x会同时在同一个线程析构，这个线程不一定是对象诞生的线程，这个特性是把双刃剑；如果对象的析构比较耗时，那么可能会拖慢关键线程的速度(如果最后一个shared\_ptr引发的析构发生在关键线程)；同时，我们可以用一个单独的线程来专门做析构，通过一个`BlockingQueue<shared_ptr<void>>`把对象的析构都转移到那个专用的线程，从而解放关键线程。
    __RAII__:shared\_ptr是管理共享资源的利器，需要注意避免循环引用，通常的做法是owner持有指向child的shared\_ptr，child持有指向owner的weak_ptr。  

3.  对象池  
    假设有一个Stock类，代表一只股票的价格，每只股票只有一个唯一的字符串的表示，为了节省系统资源，同一个程序里面每只股票只有一个Stock对象，如果多出用到同一只股票，那么Stock对象应该被共享。如果某一只股票没有再在任何地方用到，其对应的Stock对象应该析构，以释放资源，这隐含了“引用计数”。  
    为了实现以上，设计了一个StockFactory：根据key返回Stock对象。

    ```
    //有问题的代码
    class StockFactory : boost::noncopyable
    {
    public:
        shared_ptr<Sotck> get(const string &key);

    private:
        mutable MutexLock mutex_;
        std::map<string, shared_ptr<Stock> > stock_;
    };

    ```

    此处代码的问题是，Stock对象永远不会被销毁，因为map里面存的是shared\_ptr，那么shared\_ptr替换为weak\_ptr呢？

    ```
        shared_ptr<Stock> StockFactory::get(const string &key)
    {
        shared_ptr<Stock> p_Stock;
        MutexLockGuard lock(mutex_);
        weak_ptr<Stock> &wk_Stock = stock_[key]; //如果key不存在，会默认创建一个
        p_Stock = wk_Stock.lock();

        if (!p_Stock)
        {
            p_Stock.reset(new Sotck(key));
            wk_Stock = p_Stock; //这里更新了stock_[key], wk_Stock是个引用
        }

        return p_Stock;
    }

    ```

    这么做固然Stock对象时销毁了，但是程序却出现了轻微的内存泄露，为什么？因为stocks\_只增不减，stock\_.size()是曾经存活过的SOT查看对象那个的总数，即便获得Stock对象数目将为0.或许有人认为不算泄露，因为内存并不是彻底遗失不能访问了，而是别某个标准库容器占用了。(___不是太懂___)  
    解决办法是，利用shared\_ptr的定制析构功能。shared\_ptr的构造函数可以有一个额外的模板类型参数，传入一个函数指针或者仿函数d，在析构对象时执行d(ptr)，其中ptr时shared\_ptr保存的对象指针。shared\_ptr这么设计不是多余的，因为反正要在创建独享时捕获释放动作，始终需要一个bridge。   

    ```
    template<class Y, class D> shared_ptr::shared_ptr(Y *p, D d);
    template<class Y, class D> void shared_ptr::reset(Y *p, D d);
    ```

    只需要利用这一点，在析构Stock对象的同时清理stock\_。  

    ```
    class StockFactory : boost::noncopyable
    {
    public:
        shared_ptr<Sotck> get(const string &key);

    private:
        mutable MutexLock mutex_;
        std::map<string, weak_ptr<Stock> > stocks_;

        void deleteStock(Stock *stock)
        {
            if (stock)
            {
                MutexLockGuard lock(mutex_);
                stocks_.erase(stock->key());
            }

            delete stock;
        }
    };

    shared_ptr<Stock> StockFactory::get(const string &key)
    {
        shared_ptr<Stock> p_Stock;
        MutexLockGuard lock(mutex_);
        weak_ptr<Stock> &wk_Stock = stock_[key]; //如果key不存在，会默认创建一个
        p_Stock = wk_Stock.lock();

        if (!p_Stock)
        {
            p_Stock.reset(new Sotck(key), boost::bind(&StockFactory::deleteStock, this, _1));
            wk_Stock = p_Stock; //这里更新了stock_[key], wk_Stock是个引用
        }

        return p_Stock;
    }
    ```
    这里在析构Stock *p(指代的是模板里面的Y *p)时，调用本StockFactory对象的deleteStock成员函数。这里仍然有问题，那就是我们将一个原始的StockFactory this指针保存在了boost::function中，这里就会出现线程安全问题，如果这个StockFactory先于Stock对象析构，那么就会出席那core dump。解决这个问题的方法是弱回调技术。   
    1.  enable\_shared\_from\_this   StockFactory::get()把原始指针this保存到了boost::function中，如果StockFactory的生命周期比Stock段，那么Stock析构时去回调StockFactory就会core dump。似乎我们应该使用shared\_ptr来解决生命周期问题，但是StockFactory本身是个成员函数，如何获得一个指向当前对象的shared\_ptr<StockFactory>对象呢？就是使用enable\_shared\_from\_this。这是一个以其派生类为模板类型实参的鸡肋模板，继承他，this指针就能变身为shared\_ptr。 

        ```
        class StockFactory : public boost::enable_shared_from_this<StockFactory>, boost::noncopyable
        {};
        ```

        为了使用shared\_from\_this(), StockFactory不能使stack object, 必须是heap object且由shared\_ptr管理其生命期，即：

        ```
        sahred_ptr<StockFactory> stockFactory(new StockFactory);
        ```

        最新的版本为：
        
        ```
        shared_ptr<Stock> StockFactoy::get(const string &key)
        {       
            p_Stock.reset(new Stock(key), boost::bind(&StockFactory::deleteStock, shared_from_this(), _1)); 
        }       
        ```

        这样一来boost::function里面保存了一份shared\_ptr<StockFactory>，可以保证调用StockFactory::deleteStock()的时候那个StockFactory对象还活着。shared\_from\_this不能再构造函数里调用，因为在构造StockFactory的时候，他还没有被交给sahred\_ptr接管。然后，StockFactory的生命期被意外延长了。   
    2.  弱回调  
        把shared\_ptr绑到boost::function(boost::bind)里，那么回调的时候StockFactory对象始终存在，是安全的。这同时延长了对象的生命期，使之不短于绑定的boost::function对象。然后我们可以把weak_ptr绑到boost::functioni里，这样对象的生命期就不会被延长，然后回调的时候先尝试提升shared\_ptr，如果提升成功，说明接受回调的对象还健在，那么执行回调。   
        使用这一技术的完整StockFactory代码如下：   
        ```
        class StoryFactory : public boost::enable_shared_from_this<StoryFactory>, boost::noncopyable
        {
        public:
            shared_ptr<Stock> get(const string &key)
            {
                shared_ptr<Stock> p_Stock;
                MutexLockGuard lock(mutex_);
                weak_ptr<Stock> &wk_Stock = stocks_[key];
                p_Stock = wk_Stock.lock();

                if (!p_Stock)
                {
                    p_Stock.reset(new Stock(key),
                                  boost::bind(&StoryFactory::weakDeleteCallback,
                                              boost::weak_ptr<StoryFactory>(shared_from_this)), _1);

                    //上面必须强制将shared_from_this() 转型为weak_ptr，才不会延长生命期，因为boost::bind拷贝的是实参类型，不是形参类型
                    wk_Stock = p_Stock;
                }

                return p_Stock;
            }

        private:
            static void weakDeleteCallback(const boost::weak_ptr<StoryFactory> &wk_wk_Factory, Stock *stock)
            {
                shared_ptr<StockFactory> factory(wk_Factory.lock());

                if (factory)
                {
                    factory->removeStock(stock);
                }
                delete stock;
            }

            void removeStock(Stock *stock)
            {
                if (stock)
                {
                    MutexLockGuard lock(mutex_);
                    stocks_.erase(stock->key());
                }
            }

        private:
            mutable MutexLock mutex_;
            std::map<string, weak_ptr<Stock> > stock_;
        };
        ```

        这下，无论Stock和StockFactory谁先挂掉都不会硬性程序的正确运行。这里使用shared\_ptr和weak\_ptr完美解决了两个对象相互引用的问题。

4.  __替代方案__ 除了使用shared\_ptr/weak\_ptr, 要想在C++里做到线程安全的对象那个回调和析构，可能的方案有以下：
    1.  用一个全局的Facade来代理Foo类型对象访问，所有的Foo对象回调和析构都通过facade来做，也就是把指针替换为objId/handle，每次都要调用对象的成员函数的时候先check-out，用完之后再check-in。这样理论上能够避免竞态条件，但是代价太大。因为要想把这个facade做成线程安全的，就必然要用到互斥锁。这样一来，从两个线程访问两个不同的Foo对象也会用到同一个锁，让本来能够并行执行的函数编程了串行，没能发挥多核的有事。当然，可以向Java的ConcurrentHashMap那样用多个buckets，每个bucket分别加锁，以降低contention。  
    2.  自己编写引用计数的只能指针。   
    3.  将来在C++11里面有unique\_ptr，能避免引用计数的开销，或许能够在某些场合替换shared\_ptr。  

5.  线程同步的思想原则，按重要性排列：   
    1.  首要原则是尽量最低限度的共享对象，减少需要同步的场合。一个对象能不暴露给别的线程就不要暴露，如果要暴露，有限考虑immutable对象。实在不行才暴露可修改的对象，病用同步措施来充分保护它。   
    2.  其次是使用高级的并发编程够将，如TaskQueue、Producer-Consumer Queue，CountDownLatch等等。   
    3.  最后不得已必须使用底层同步原语时，只用非递归的互斥器和条件变量，慎用读写锁，不要用信号量。   
    4.  除了使用atomic整数外，不自己编写lock-free代码，也不要用内核级同步原语，不凭空猜测那种做法性能更好，比如spin lock vs mutex。   
6.  ___互斥器___ 它保护临界区，任何时刻最多只能有一个线程在此mutex划出的临界区活动。单独使用的mutex时，我们主要为了保护共享数据，张硕的原则是：
    1.  用RAII手法封装mutex的创建、销毁、加锁、解锁这四个操作。用RAII封装这几个操作是通行的做法，这几乎是C++标注你时间。即保证锁的生效期间等于一个作用域，不会因为一场忘记解锁。 
    2.  只用非递归的mutex(即不可重入的mutex)。   
    3.  布手工调用lock()和unlock()函数，一切交给栈上的Guard对象的构造和析构函数负责。Guard对象的生命期正好等于临界区这样我们保证始终在同一个函数同一个scope里对某个mutex加锁和解锁。避免在foo()里加锁，然后跑到bar()里解锁。也避免在不同的语句分之中分别加锁、解锁。这种做法叫做Scoped Locking。   
    4.  在每次过早Guard对象的时候，思考一路上(调用栈上)已经持有的锁，防止加锁顺序不同而导致死锁。有余Guard对象时栈上对象，看函数调用栈就能分析用锁的情况。   
    ___次要原则___    
    5.  不要跨进程使用mutex，进程通信只用TCP sockets。  
    6.  加锁、解锁在同一个线程，线程a不能去unlock线程b已经锁住的mutex(RAII自动保证)。   
    7.  别忘了解锁(RAII自动保证)。   
    8.  不重复解锁(RAII自动保证)。   
    9.  必要的时候可以考虑PTHREAD\_MUTEX\_ERRORCHECK来排错。   
    按照上面的原则，几乎应该不会出错。   
    ---
    1.  ___只是用非递归的mutex___    
        mutex分为递归和非递归两种，这是POSIX的叫法，另外的名字是可重入与费可重入。这两种mutex作为线程间的同步工具时没有区别，他们的唯一区别在于：同一个线程可以重复对可地柜mutex加锁，但是不能重复对不可递归mutex加锁。
    首选非递归mutex，不是为了性能，而是为了设计意图。非递归和递归的差别其实不大，因为少了一个计数器，前者略快一点而已。在同一个线程里多次对非递归mutex加锁会立刻导致死锁，这其实是有点，能帮助我们思考代码对锁的期求，帮助我们发现问题。  

        ```
        MutexLock mutex;
        std::vector<Foo> foos;

        void post(const Foo &f)
        {
            MutexLockGuard lock(mutex);
            foos.push_back(f);
        }

        void traverse()
        {
            MutexLockGuard lock(mutex);

            for (std::vector<Foo>::const_iterator it = foos.begin(); it!=foos.end(); ++it)
            {
                it->doit();
            }
        }
        ```  

        post()加锁，然后修改foos对象；traverse()加锁，然后便利foos向量，这些都是正确的。如果某一天，Foo::doit简介的调用了post()，那么会有这样的结果：  
            1.  mutex是非递归的，于是死锁了。   
            2.  mutex是递归的，有余push_back()可能(但不总是)导致vector迭代器失效，程序偶尔会crash。   
        这时候就能体现出非递归性mutex的优越性：把程序的逻辑错误暴露出来。死锁比较容易debug，把哥哥线程的调用栈打印出来，只要每个函数不是特别长，很容易看出来程序怎么死的。或者使用PTHREAD\_MUTEX\_ERROCHECK一下子就能找到错误。如果确实需要在便利的时候修改vector，有两种做法，意识把修改推后，基础循环中师徒添加或者删除那个元素，等循环结束了再依记录修改foos；二是使用copy-on-write，如果一个函数极可能在一家所的情况下调用，有可能在未加锁的情况下调用，那么久拆成两个函数：  
            1.  根原来的函数同名，函数加锁，转而调用第二个函数。  
            2.  给函数名加上WithLockHold，不加锁，把原来的函数体搬过来。   
        如下：  

        ```
        MutexLock mutex;
        std::vector<Foo> foos;

        void post(const Foo &f)
        {
            MutexLockGuard lock(mutex);
            postWitchLockHold(f);
        }

        void postWithLockHold(const Foo &f)
        {
            foos.push_back(f);
        }
        ```

        这也可能出现两个可能：  
            1.  误用了加锁版本，死锁了。   
            2.  误用了不加锁版本，数据损坏了。  
        对于上面第一条，可以这样子排错：  
        
        ```
        void postWithLockHold(const Foo &f)
        {
            assert(mutex.isLockedByThisThread());
        }
        ```

    2.  ___死锁___  

        ```
        class Request
        {
        public:
            void process() // __attribute__((noinline))
            {
                muduo::MutexLockGuard lock(mutex_);

                // ...

                print();
            }

            void print() const // __attribute__((noinline))
            {
                muduo::MutexLockGuard lock(mutex_);
                // ...
            }

        private:
            mutable mmuduo::MutexLockGuard mutex_;
        };

        int main()
        {
            Request req;
            req.process();
        }
        ```

        在上面的例子中，如果没有执行`print()`，程序还没有问题，如果执行了`print()`，程序立即出现了死锁。调试这个错误的话，只要把函数栈打印出来，我们会发现第6帧的Request::process()和第5帧Request::print()先后对同一个mutex上锁，引发了死锁：   
        ![core](./pictures/1.jpg "core")
        要修复这个错误也很容易，按照前面的办法，从Request::print()抽取出Request::printWithLockHold(), 病让Request::print()和Request::process()都调用它即可。   
        再来看两个线程死锁的例子：   
        有一个Inventory class记录当前Request对象那个。下面这个Inventory class的add()和remove()成员函数都是线程安全的，它使用了mutex来保护共享数据request\_。  

        ```
        class Inventory
        {
        public:
            void add(Request *req)
            {
                muduo::MutexLockGuard lock(mutex_);
                requests_.insert(req);
            }

            void remove(Request *req) // __attribute__ ((noinline))
            {
                muduo::MutexLockGuard lock(mutex_);
                requests_.erase(req);
            }

            void printAll() const;

        private:
            mutable muduo::MutexLock mutex_;
            std::set<request*> requests_;
        };

        Inventory g_inventory;
        ```

        Request class与Inventory class的交互逻辑很简单，在处理(process)请求的时候，往g_inventory中添加自己。在析构的时候，从g_inventory中移除自己。目前看来整个程序还是很安全的。   
        ```
        class Request
        {
        public:
            void process() // __attribute__((noinline))
            {
                muduo::MutexLockGuard lock(mutex_);
                g_inventory.add(this);
                // ...

                print();
            }

            ~Request() __attribute__ ((noinline))
            {
                muduo::MutexLockGuard lock(mutex_);
                sleep(1);
                g_inventory.remove(this);
            }

            void print() const // __attribute__((noinline))
            {
                muduo::MutexLockGuard lock(mutex_);
                // ...
            }

        private:
            mutable mmuduo::MutexLockGuard mutex_;
        };
        ``` 

        Inventory class 还有一个功能是打印全部一致的Request对象。Inventory::printAll()里的逻辑单独看是没有问题的，但是他有可能会引发死锁。  

        ```
        void Inventory::printAll() const
        {
            muduo::MutexLockGuard lock(mutex_);
            sleep(1);
        }

        for (std::set<Request*>::const_iterator it = requests_.begin(); 
             it != requests_.end(); ++it)
        {
            (*it)->print();
        }

        下面的程序运行起来会发生死锁：  
        void threadFunc()
        {
            Request *req = new Request;
            req->process();
            
            delete req;
        }

        int main()
        {
            muduo::Thread thread(threadFunc);
            thread.start();
            usleep(500*1000);  //为了让另一个线程等在前面的sleep上
            g_inventory.printAll();
            thread.join();
        }
        ```

        通过gdb查看两个线程的函数调用栈，我们发现两个线程都等在mutex上，估计是发生了死锁。如下图所示：   
        ![core](./pictures/2.jpg "core")  
        注意到main()线程是先调用Inventory::printAll()再调用Request::print()，而threadFunc()线程是先调用`Request::~Request()`再调用Inventory::remove()。这两个调用序列对两个mutex的加锁顺序正好相反，于是造成了经典的死锁。如下图，Inventory class的临界区由灰底表示，Request class的mutex的临界区由斜纹表示。一旦main()线程中的printAll()在另一个线程的~Request()和remove()之间开始执行，死锁已不可避免。如下：   
        ![死锁](./pictures/3.jpg "死锁")  
        这里也出现了对象析构的竞态条件，即一个线程正在析构对象，另一个线程却在调用它的成员函数。解决方法很简单，要么把print()溢出printAll()的临界区，要么把remove()溢出`~Request()`的临界区。当然这仍然没有解决对象析构的竞态条件。   
    3.  __条件变量__  
        互斥器是加锁原语，用来排他性的访问共享数据，它不是等待原语。在使用的时候，我们一般都期望加锁不要阻塞，总能够立刻拿到锁。然后尽快访问数据，用完之后尽快解锁，这样才能不影响并发性和性能。  如果需要等待某个条件成立，我们应该使用条件变量。条件变量是一个或者多个线程等待某个布尔表达式为真，即等待别的线程“唤醒”它。条件变量的学名叫做管程。条件变量只有一种正确的使用方式，几乎不可能出错，对于wait端：  
        1.  必须与mutex一起使用，该布尔表达式的读写需要受此mutex保护。   
        2.  在mutex已经上锁的时候才能调用wait()。  
        3.  把判断布尔条件和wait()放到while循环中。  
        写成代码是：   
        ```
        muduo::MutexLock mutex;
        muduo::Condition cond(mutex);
        std::deque<int> queue;

        int dequeue()
        {
            MutexLockGuard lock(mutex);

            while (queue.empty())
            {
                cond.wait();//这一步是会原子地unlock mutex并进入等待，不会与enqueue死锁，wait()执行完毕后会自动重新加锁
            }

            assert(!queue.empty());
            int top = queue.front();
            queue.pop_front();

            return top;
        }
        ```

        上面的代码必须用while循环来等待条件变量，而不能用if语句，原因是“虚假唤醒”。对于signal/broadcast端：  
        1.  不一定要在mutex已经上锁的情况下调用signal(理论上)。
        2.  在signal之前一般要修改布尔表达式。  
        3.  修改布尔表达式通常要用mutex保护(至少用作full memory barrier)。  
        4.  注意区分signal和broadcast: broadcast通常用于表明状态变化，singal通常用于表示资源可用。 
        写成代码是：   

        ```
        void enqueue(int x)
        {
            MutexLockGuard lock(mutex);
            queue.push_back(x);

            cond.notify(); // 可以移出临界区外
        }
        ```   

        上面的dequeue()/enqueue()实际上实现了一个简单的容量无限的BlockingQueue. 
        条件变狼是非常底层的同步原语，很少直接使用，一般都是用它来实现高层的同步措施，如BlockingQueue<T>或者CountDownLatch。  
        倒计时(CountDownLatch)是一种常用且易用的同步手段，主要有两种用途：  
        1.  主线程发起多个子线程，等这些子线程各自都完成了一定的任务之后，主线程彩继续执行，通常用于主线程等待多个子线程完成初始化。   
        2.  主线程发起多个子线程，子线程都等待主线程，主线程完成其他一些任务之后通知所有子线程开始执行。通常用于多个子线程等待主线程发起“起跑”命令。   
        当然我们可以直接用条件变量实现以上两步。不过如果使用了CountDownLatch的话，程序逻辑更加清晰。

        ```
        class CountDownLatch : boost::noncopyable
        {
        public:
            explicit CountDownLatch(int count); //倒数几次
            void wait(); //等待计数值变为0
            void countDown(); //计数值减一

        private:
            mutable MutexLock mutex_;
            Condition condition_;
            int count_;
        };

        CountDownLatch的实现同样简单
        void CountDownLatch::wait()
        {
            MutexLockGuard lock(mutex_);

            while (count_ > 0)
            {
                condition_.wait();
            }
        }

        void CountDownLatch::countDown()
        {
            MutexLockGuard lock(mutex_);
            --count_;

            if (count_ == 0)
            {
                condition_.notifyAll();
            }
        }
        ```

        注意到CountDowLatch::countDown()使用的是Condition::notifyAll()，而前面此处的enqueue()使用的是Condition::notify。互斥器和条件变量构成了多线程编程的全部必备同步原语，用他们即可完成任何多线程同步任务，二者不可相互替代。   
