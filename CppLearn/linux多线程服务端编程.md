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

10.  上面Observer模式的竞态条件用下面的代码解决:   

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

11.  share\_ptr本身不是100%线程安全的。它的引用计数本身是安全且无锁的，但是对象的读写不是，因为shared\_ptr又两个数据成员，读写操作不能原子化。shared\_ptr的线程安全级别和内建类型、标准库容器、std::string一样，即： 
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
12.  __shared\_ptr 意外延长了对象那个的生命周期__, 只要指向x对象的shared\_ptr存在，那么该对象就不会析构掉。另外一个出错的地方可能是boost::bind， 因为boost::bind会把实参拷贝一份，如果参数是一个shared\_ptr，那么对象那个的生命周期就不会短于boost::function对象：

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

13.  对象池  
