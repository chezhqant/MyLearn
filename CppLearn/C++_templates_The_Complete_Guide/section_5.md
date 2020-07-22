#  第五章 技巧性知识  
1.  关键字typename  
    在C++标准化过程中，引入关键字typename是为了说明：模板内部的标识符可以是一个类型。譬如如下例子：    

    ```
    template <typename T>
    class MyClass {
      typename T::SubType* ptr;
    };
    ```

    第2个typename被用来说明：SubType是定义域类T内部的一种类型。因此ptr是一个指向T::SubType类型的指针。如果不适用typename，SubType就会被认为是一个竞态成员，那么他应该是一个具体的变量或者对象于是下面表达式：`T::SubType* ptr`会被看做是类T的竞态成员SubType和ptr的乘积。   
    通常而言，当某个依赖于模板参数的名称是一个类型时，就应该使用typename。 

2.  使用this->  
    对于具有基类的类模板，自身使用名称x并不一定等同于this->x。即便是该x是基类集成获得的，也是如此，例如：    

    ```
    template <typename T>
    class Base {
    public:
      void exit();
    };

    template <typename T>
    class Derived : Base<T> {
    public:
      void foo() {
        exit(); 
      }
    };
    ``` 
    
    在这个例子中，在foo()内部决定要调用哪个exit()时，并不会考虑基类Base中定义的exit()，因此，你如果不是获得一个错误，就是调用了另一个exit()。    
    一个规则：对于那些在基类中声明，并且依赖于模板参数的符号（函数或者变量等），你应该使用它们前面使用this->或者Base<T>::。如果希望完全避免不确定性，你可以(使用诸如this->和Base<T>::等)限定(模板中)所有的成员访问。   

3.  类成员也可以是模板，嵌套类和成员函数都可以作为模板，比如下面：    

    ```
    Stack<int> int_stack1, int_stack2; // int栈
    Stack<float> float_stack; // float 栈
    ···
    int_stack1 = int_stack2; // OK 具有相同类型的栈
    float_stack = int_stack1; // ERROR, 两边栈的类型不同
    ```

    对于元素类型不同的栈，不能对它们进行相互赋值，即使这两种（元素的）类型之间存在隐式类型转换。    
    缺省赋值运算符要求两边具有相同的类型，当元素类型不同时，两个站的类型显然不同不能符合缺省赋值运算符的要求。    
    不过可以增加一个赋值运算符。  

3.  新赋值运算符实现大致如下：    

    ```
    template <typename T>
    class Stack {
    private:
      std::deque<T> elems;

    public:
      void push(T const&);
      void pop();
      T top() const;
      bool empty() const {
        return elems.empty();
      }

      template <typename T2>
      Stack<T>& operator=(Stack<T2> const&);
    };

    template <typename T>
     template <typename T2>
    Stack<T>& Stack<T>::operator=(Stack<T2> const& op2) 
    {
      if ((void*)this == (void*)&op2) {
        return *this;
      }

      Stack<T2> tmp(op2);

      elems.clear();
      while (!tmp.empty()) {
        elems.push_front(tmp.top());
        tmp.pop();
      }

      return *this;
    }
    ```
    
    当然，这个赋值并没有改变原栈的类型和它所含元素的类型。在赋值以后float_stack的元素仍然是float类型，因此他的top()依然返回一个浮点类型。   
    还可以把内部的容器类型实现为一个模板参数。这样就有机会改变内部容器类型：    
    ```
    template<typename T, typename CONT = std::deque<T>>
    class Stack {
    private:
      CONT elems;

    public:
      void push(T const&);
      void pop();
      T top() const;
      bool empty() const {
        return elems.empty();
      };

      template <typename T2, typename CONT2>
      Stack<T, CONT>& operator=(Stack<T2, CONT> const&);
    };
    ```

    此模板赋值运算符的实现如下：    

    ```
    template <typename T, typename CONT>
     template <typename T2, typename CONT2>
    Stack<T, CONT>& Stack<T, CONT>::operator=(Stack<T, CONT2> const& op2)
    {
      if ((void*)this == (void*)op2) {
        return *this;
      }

      Stack<T2, CONT2> tmp(op2);

      elems.clear();

      while (!tmp.empty()) {
        elems.push_front(tmp.top());
        tmp.pop();
      }

      return *this;
    }
    ```

    对于类模板而言，只有那些被调用的成员函数才会被实例化。因此，如果在元素类型不同的栈之间没有进行相互赋值，你就可以使用vector来作为内部容器：    
    
    ```
    Stack<int, std::vector<int>> v_stack;
    ···

    v_stack.push(42);
    v_stack.push(7);
    std::cout << v_stack.top() << std::endl;
    ```

4.  为了指定内部容器的类型，你需要同时传递容器的类型和它所含元素的类型，如下：`Stack<int, std::vector<int>> v_stack;`，借助于***模板的模板参数***，你可以只指定容器的类型而不需要指定所含元素的类型，就可以声明这个Stack类模板： `Stack<int, std::vector> v_stack;`。为了获得这个特性，你必须把第二个模板参数指定为***模板的模板参数***。那么，Stack的声明应该如下：   

    ```
    template <typename T, template <typename ELEM> class CONT = std::deque>
    class Stack {
    private:
      CONT<T> elems;

    public:
      void push(T const&);
      void pop();
      T top() const;
      bool empty() const {
        return elems.empty();
      }
    };
    ```

    不同之处在于，第2个模板参数现在被声明为一个类模板: `template <typename ELEM> class CONT` 。缺省值也从std::deque<T>变成了std::deque。在使用时，第2各参数必须是一个类模板，并且由第一个模板参数传递进来的类型传递进来的类型进行进行实例化：  `CONT<T> elems;`。使用第1个模板参数作为第2个模板参数的实例化类型。一般地，你可以使用类模板内部的任何类型来实例化***模板参数***。通常可以使用typename来替换关键字class。然而，上面的CONT是为了定义一个雷，因此只能使用关键字class。

    ```
    template <typename T, template <class ELEM> class CONT = std::deque> // 这样是正确的
    class Stack {};

    template <typename T, template <typename ELEM> typename CONT = std::deque> // 这样是错误的
    class Stack {};
    ```

    这里不会用到***模板的模板参数***，所以你可以把该名称省略不写。

    ```
    template <typename T, template <typename> class CONT = std::deque>
    class Stack {};
    // 另外，还必须对成员函数的声明进行相应的修改。你必须把第2个模板参数指定为***模板的模板参数***；这同样适用于成员函数的实现，例如：  
    template <typename T, template <typename> class CONT>
    void Stack<T, CONT>::push (T const& elem) {
      elems.push_back(elem);
    }
    ```

5.  函数模板并不支持***模板的模板参数***。  
6.  如果你尝试使用新版本Stack，你会获得一个错误信息：缺省值std:deque和模板的模板参数CONT并不匹配。问题在于：模板的模板实参是一个具有参数A的模板，它将替换模板的模板参数，而模板的模板参数是一个具有参数B的模板：匹配过程要求参数A和参数B必须完全匹配，然而，我们并没有考虑模板的模板实参的缺省模板参数，从而也就使B中缺少了这些缺省参数值，当然就不能获得精确的匹配。这个例子中，问题在于标准库中的std::deque模板还具有另外一个参数：即第2个参数（也就是所谓的内存分配器allocator，他有一个缺省值，但在匹配std::deque的参数和CONT的参数时，我们并没有考虑这个缺省值。解决办法：重新写类的声明，让CONT的参数期待的是具有两个模板参数的容器：  
    
    ```
    template <typename T, template <typename ELEM, typename ALLOC = std::allocator<ELEM>> class CONT = std::deque>
    class Stack {
    private:
      CONT<T> elems;
    }; // 可以省略ALLOC不写，实现中不会用到它
    ```

7.  对于int、double或者指针等基本类型，并不存在“用一个有用的缺省值来对它们进行初始化”的缺省构造函数；相反，任何未被初始化的局部变量都具有一个不确定值： 

    ```
    void foo() {
      int x; // x具有一个不确定值
      int *ptr; // ptr指向某块内存
    }

    //假设你再编写模板，并且希望模板类型的变量都已经用缺省值初始化完毕，那么内建类型并不能满足你的要求：
    template <typename T>
    void foo() {
      T x; // 如果T是内建类型，那么x本身是一个不确定值
    }

    // 解决办法：
    template <typename T>
    void foo() [
      T x = T(); // 如果T是内建类型类型，x是0，或者是false

    // 对于类模板，在用某种类型实例化该模板后，为了确认它所有的成员都已经初始化完毕，你需要定义一个缺省构造函数，通过一个初始化列表来初始化类模板的成员：
    template <typename T>
    class MyClass {
    private:
      T x;
    public:
      MyClass() : x() //确认x已被初始化，内建类型对象也是如此
    };
    ```

8.  把字符串传递给函数模板的引用参数会导致意外结果：

    ```
    #include <string>

    template <typename T>
    inline T const& max(T const& a, T const& b) {
      return a > b ? b : a;
    }

    int main()
    {
      std::string s;
      
      ::max("apple", "peach"); // OK 相同的类型的实参
      ::max("apple", "tomato"); // ERROR 不同类型的实参
      ::max("apple", s); // ERROR 不同类型的实参
    }
    ```

    问题在于：有余长度的区别，这些字符串属于不同的数组类型。也就是说，“apple”和“peach”具有相同的类型`char const[6]`。然而“tomato”的类型则是：`char const[7]`。因此只有第一个调用是合法的。如果生命的是非引用参数：

    ```
    #include <string>

    template <typename T>
    inline T max(T a, T b) {
      return a < b ? b : a;
    }

    int main()
    {
      std::string s;
      
      ::max("apple", "peach"); // OK 相同的类型的实参
      ::max("apple", "tomato"); // ERROR 不同类型的实参
      ::max("apple", s); // ERROR 不同类型的实参
    }
    ```

    产生这种调用结果的原因是：对于非引用类型的参数，在实参演绎的过程中，会出现数组到指针的类型转换:   
    
    ```
    #include <typeinfo>
    #include <iostream>

    template <typename T>
    void ref (T const& x) {
      std::cout << "x in ref(T const&): " << typeid(x).name() << `\n`;
    }

    template <typename T>
    void ref (T x) {
      std::cout << "x in nonref(T const&): " << typeid(x).name() << `\n`;
    }

    int main()
    {
      ref("hello");
      nonref("hello");
    }
    ``` 

    在main函数中，分别传递一个字符串给具有引用参数的函数模板和具有非引用参数的函数模板。两个函数模板都使用了typeid运算符来输出被实例化参数的类型。typeid运算符的会返回std::type_info类型的左值，其中std::type_iunfo封装了传递给typeid运算符的表达式的类型表示：调用std::type_info的成员函数name()是为了返回类型的可读文本表示。例如上面程序可能会有如下输出：  
    ```
    x in ref(T const&): char[6]
    x in nonref(T): const char*
    ```

9.  如果你遇到一个关于字符数组和字符串指针不匹配的问题，对这个问题并没有通用的解决方法，你可以：
    1.  使用非引用参数，取代引用参数（这可能会导致无用的拷贝）
    2.  进行重载，编写接受引用参数和非引用参数的两个重载函数(然而，这可能会导致二义性)
    3.  对具体类型进行重载(譬如对std::string进行重载)
    4.  重载数组类型，譬如：
        ```
        template <typename T, int N, int M>
        T const* max(T const (&a)N, T const (&b)[M]) {
          return a < b ? b : a;
        }
        ```
    5.  强制要求应用程序程序员使用显式类型转换。
