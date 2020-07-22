#  第四章 非类型模板参数    
1.  对于函数模板和类模板，模板参数并不局限于类型，普通纸也可以作为模板参数。    
2.  当使用基于值得模板时，必须显示地指定这些值，才能够对模板进行实例化，并获得最终的代码。    
3.  可以这么使用：  

    ```
    // basics/stack4.hpp
    #include <stdexcept>

    template <typename T, int MAXSIZE>
    class Stack {
    private:
      T elems[MAXSIZE];
      int numElems;

    public:
      Stack();
      ···
    };

    template<typename T, int MAXSIZE>
    Stack<T, MAXSIZE>::Stack() : numElems(0) {}
    ``` 

4.  可以为函数模板定义非类型参数。  

    ```
    // basics/addval.hpp
    template<typename T, int VAL>
    T addValue(T const& x) {
      return x + VAL;
    }
    ```

5.  一个例子，借助于STL，你可以传递这个函数模板([4](#4))的实例化给集合中的每个元素，让他们都增加一个整数值:   

    ```
    std::transform(source.begin(), source.end(), dest.begin(), addValue<int, 5>);
    ``` 

    上面的调用中，最后一个实参实例化了函数模板addValue()，元集合source中的每个元素都会调用实例化后的addValue()函数，并把调用后的结果放入目标集合dest中。    
    但是这样有***一个问题***，addValue<int, 5>是一个函数模板实例，而函数模板实例通常被看做是用来命名一组重载函数的集合(即使该组只有一个函数)。然而，根据现在的标准，重载函数的集合并不能被用于模板参数的编译。于是，你必须将这个函数模板的实参强制转换为具体的类型：    

    ```
    std::transfor (source.begin(), source.end(), dest.begin(), (int(*)(int const&))addValue<int, 5>);
    ```

6.  非类型模板参数的限制为：必须是长整数或者指向外部链接对象的指针。浮点数和类对象是不允许作为非类型模板参数的。全局指针作为模板参数也不被允许。如下：    

    ```
    template<char const* name>
    class MyClass {};

    MyClass<"hello"> x; // ERROR: 不允许使用字符串文字

    template<char const* name>
    class MyClass {};
    char const* s = "hello";
    MyClass<s> x; // 这样是不对的

    然而可以这么用：
    template<char const* name>
    class MyClass {};

    extern char const s[] = "hello";
    MyClass<s> = x; // OK, 全局字符数组s是由“hello”初始化，是一个外部链接对象。
    ```

