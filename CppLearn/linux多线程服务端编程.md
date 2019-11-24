___this file is my knowledge about <linux多线程服务端编程___


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
即使构造函数的最后一行也不要泄露this，因为Foo有可能是个鸡肋，基类先于派生类构造，执行完Foo::Foo()的最后一行代码还会继续执行派生类的构造函数，这时候most-derived class的对象还处于构造中，仍然不安全。    
总的来说，构造函数做到线程安全容易，析构函数做到线程安全麻烦。    
2. 之所以
