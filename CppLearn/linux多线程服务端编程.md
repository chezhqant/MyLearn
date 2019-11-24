___this file is my knowledge about <linux多线程服务端编程>___


1. 对象要做到线程安全，唯一的要求就是在构造期间不要泄露this指针，即   
    1. 不要在构造函数中注册任何回调   
    2. 也不要在构造函数中把this传给跨线程的对象   
    3. 即使在构造函数的最后一行也不能泄露this指针    
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
2. 对象析构，单线程不是问题，最多需要避免空悬指针和野指针。对一般成员函数而言，做到线程安全的办法是让他们顺序执行，而不要并发执行(关键是不要同时读写共享状态)，也就是让每个成员函数的临界区不重叠。   
3. 成员函数用来保护临界区的互斥器本身必须是有效的。而析构函数破坏了这一假设，他会把mutex成员变量销毁掉。      
4. mutex并不是多线程的办法。mutex只能保证函数一个接一个的执行。考虑以下代码：   

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

此时A/B两个线程都能看到Foo对象x，线程A即将销毁x，而线程B正准备调用`x->update()`。   

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

尽管线程A在销毁独享之后把指针置为NULL，尽管线程B在调用x的成员函数之前检查了指针x的值，但是还是无法避免一种竞态条件：    
    2.1. 线程A执行到了析构函数的(1)处，已经持有了互斥锁，即将向下执行。   
    2.2. 线程B通过了if(x)检测，阻塞在(2)处。    
接下来发生什么就不知道了。   
5. 如果要同时读写一个class的两个对象，有潜在的死锁的可能。比如有一个swap():   

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
6. 对象的关系主要有三种：composition(组合)/aggregation(聚合)/association(关联)。组合关系在多线程里面不会遇到什么麻烦，因为对象x的生命周期由其唯一的拥有者owner控制(我猜测就是一个class A内定义另一个class B，class B不是指针和引用，仅仅是class B的一个实例)。关联表示一个对象a用到了另一个对象b，调用了后者的成员函数。从代码形式看，a持有b的指针(或引用)，但是b的生命周期不由a单独控制。聚合关系从形式上看雨关联相同，除了a和b有逻辑上的整体与部分的关系。如果b是动态创建的并在整个程序结束前有可能被释放，就会出现竞态条件。  
一个简单的解决办法是：只创建不销毁。程序使用一个对象池来暂存用过的对象，下次申请新的对象时，如果对象池里有存货，就重复利用现有的对象，否则就新建立一个。对象用完了，不是直接放掉，而是放回池子里。这个方法有缺点，但是至少能避免访问失效对象的情况发生。    
这种山寨的方法是：   
    1. 对象池的线程安全，如果安全的、完整的把对象放回池子里，防止出现“部分放回”的竞态？(线程A认为对象x已经放回，线程B认为对象x还活着)。   
    2. 全局共享数据引发的锁竞争，这个集中化的对象池会不会把多线程并发的操作串行化？   
    3. 如果共享对象的类型不止一种，那么是重复实现对象池还是使用类模板？   
    4. 会不会造成内存泄露与分片？因为对象池占用的内存只增不减，而且多个对象池不能共享内存。    
如果对象x注册了任何非静态成员函数回调，那么必然会在某处持有了指向x的指针，这就暴露在竞态条件之下。    
