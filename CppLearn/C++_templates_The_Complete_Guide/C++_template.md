___C++ Template, The Complete Guide___

#  第二章 函数模板   
1.  形如下面：   

  ```
  // basics/max.hpp
  template <typename T>
  inline T const& max(T const& a, T const& b) {
    return a < b ? b : a;
  }
  ```

  其中`T`代表模板参数/类型参数。模板参数必须使用如下形式的语法来声明：   

  `template <用逗号隔开的参数列表>`  

2.  在声明类型参数类型参数的时候不能用关键字struct代替typename。   

3.  下面代码中，展示了如何使用max函数模板：   

  ```
  // basics//max.cpp
  #include <iostream>
  #include <string>
  #include "max.hpp"

  int main()
  {
    int i = 42;
    std::cout << "max(7, i): "<< max(7,1) <<std::endl;

    double f1 = 3.4;
    double f2 = -6.7;
    std::cout << "max(f1, f2): " << ::max(f1, f2) << std::endl;

  std::string s1 = "mathematics";
  std::string s2 = "math";
  std::cout << "max(s1, s2): " << ::max(s1, s2) << std::endl;
  }
  ```

  输出结果为：  

  ```
  max(7,1): 42
  max(f1,f2):3.4
  max(s1,s2):mathematics
  ```

  故，通常而言，并不是把模板编译成一个可以处理任何类型的单一实体；而是对于实例化模板参数的美中类型，都从模板产生出一个不同的实体；而是对于实例化模板参数的每种类型，都从模板产生出一个不同的实体。这种用具体类型代替模板参数的过程叫做***实例化***。

4.  只要使用函数模板，（编译器）会自动地引发这样一个实例化过程，因此并不需要额外地请求模板实例化。   
5.  模板在使用的时候被编译了两次:
    1.  实例化之前，先检查模板代码本身，看看语法是否正确。在这里会发现错误的语法调用。如遗漏分号。
    2.  在实例化期间，检查模板代码，查看是否所有的调用都有效。在这里会发现无效的调用。如该实例化类型不支持某些函数调用等等。   

6.  模板参数可以由我们所传递的实参来决定。如：   

  ```
  template <typename T>
  inline T const& max(T const& a, T const& b);
  ···
  max(4,7); // OK两个实参类型都是int
  max(4,4.2); // Error，不支持自动类型转换，每个类型都必须正确匹配。
  ```

7.  模板参数不允许进行自动类型转换，每个T都必须正确地匹配。  

8.  在 [6](#6)中，可以使用以下三种方法处理上面的错误：   
    1.  对实参进行强制类型转换，使他们可以互相匹配。   

        ```
        max(static_cast<double>(4), 4.2);
        ```

    2.  显式指定(或者限定)T的类型：   

        ```
        max<double>(4,4.2);
        ```

    3.  指定两个参数可以具有不同的类型。    

9.  函数模板有两种类型的参数：    
    1.  模板参数：位于函数模板名称的前面，在一堆尖括号内部进行声明：  

        `template <typename T> //T式模板参数`   

    2.  调用参数：位于函数模板名称，在一对圆括号内部进行声明：  

        `max(T const& a, T const& b) //a和b都是调用参数`    

10. 与类模板不同，不能指定缺省的模板实参。    

11. 可以定义两个调用参数的类型可以不同的max模板：   

    ```
    template <typename T1, typename T2>
    inline T1 max(T1 const& a, T2 const& b) {
      return a < b ? b : a;
    }
    ···
    max(4, 4.2); //OK，但第一个模板实参的类型定义了返回类型
    ```

    这么做有两个问题:
    1.  必须声明返回的类型。但由于a和b的类型不同，没有办法声明返回的类型。    
    2.  该函数中，如果返回a还好，如果返回b还要有一个临时对象的生成。    

12. 可以引入第3个模板实参类型，来定义函数的模板返回类型：   

    ```
    template <typename T1, typename T2, typename RT>
    inline RT max(T1 const& a, T2 const& b);
    ```

    ***但是模板实参演绎并不适合返回类型，必须显示地指定模板实参列表***。

    ```
    max<int, double, double>(4,4.2) //OK, 但是很麻烦。
    ```

13. 我们可以只显式指定第一个实参，而让演绎过程推到出其余实参。通常而言，你必须指定“***最后一个不能被隐式演绎的模板实参之前的***”所有类型。因此上式中可以这么表示：      

    ```
    max<double>(4, 4.2); // 最后一个不能被隐式演绎的是RT，前面的分别是4，4.2
    ```

14. 当模板参数和调用参数没有发生关联，或者不能由调用参数来决定模板参数的时候，你在调用的时候必须显式指定模板实参。


15. 一个非模板函数可以和一个同名函数模板可以同时存在。如果其他条件都是相同的话，那么在调用的时候，重载解析通常会调用非模板函数，而不会从模板产生一个实例。    

16. 在下面的代码中：    

    ```
    #include <iostream>
    #include <cstring>
    #include <string>

    template <typename T>
    inline T const& max(T const& a, T const& b) {
      return a < b ? b : a;
    }

    inline char const* max(char const* a, char const* b) {
      return std::strcmp(a,b) < 0 ? b : a;
    }

    template <typename T>
    inline T const& max(T const& a, T const& b, T const& c) {
      return max(max(a, b), c); //如果max(a, b)使用传值调用将会发生错误
    }

    int main()
    {
      const char* s1 = "frederic";
      const char* s2 = "anica";
      const char* s3 = "lucas";
      ::max(s1, s2, s3); // 错误
    }
    ```

    问题就在于`return max(max(a, b), c)`，将会产生一个错误，这里的max(a, b)，产生了一个新的临时对象值，改制有可能会被外面的max函数以传引用的方式返回，而这将导致传回无效的引用。      

#  第三章 类模板   
1.  在类模板的内部，模板参数T可以像其他任何类型一样，用于声明成员变量和成员函数。

2.  比如我们定义：    

    ```
    template <typename T>
    class Stack {
      private:
        std::vector<T> elems;

      public:
        Stack();
        void push(T const&);
        void pop();
        T top() const;
    };
    ```

    这个类的类型是Stack<T>，因此，当在声明中需要使用该类的类型时，你必须使用Stack<T>。然而，当使用类名不是类的类型时，就应该只是用Stack，譬如，当你指定类的名称、类的构造函数、析构函数时，就应该使用Stack。     

3.  为了在类定义体外定义一个成员函数，必须使用这个类模板的完整类型限定符：  

    ```
    template <typename T>
    void Stack<T>::push (T const& elem) {
      elems.push_back(elem);
    }
    ```

4.  为了使用类模板对象，你必须显式地指定模板实参。    

5.  只有那些被调用的成员函数，才会产生这些函数的实例化代码。两个好处：    
    1.  可以节省空间和时间。    
    2.  对于那些“未能提供所有成员函数中所有操作的”类型，也可以使用该类型来实例化类模板，只要对那些“未能提供某些操作的”成员函数，模板内部不使用就可以。      

6.  如果类模板中含有静态成员，那么用来实例化的美中类型，都会实例化这些竞态成员。

7.  可以使用模板实参来特化类模板。也可以只特化某个成员函数。    

8.  为了特化一个类模板，每个你必须在起始处声明一个`template<>`，接下来声明用来特化模板的类型，这个类型被用作模板实参，且必须在类名后面直接指定：    

    ```
    template <>
    class Stack<std::string> {};
    ```

9.  进行类模板特化的时候，每个成员函数都必须重新定义为普通函数，原来模板函数中的每个T也相应地被进行特化的类型取代：   

    ```
    void Stack<std::string>::push(std::string const& elem) {
      elems.push_back(elem);
    }
    ```

10.  类模板可以被局部特化：    

     ```
     template <typename T1, typename T2>
     class Myclass {};

     有以下几种局部特化：    
     template <typename T>
     class Myclass<T, T> {};

     template <typename T>
     class Myclass<T, int> {};

     template<typename T1, typename T2>
     class Myclass<T1*, T2*>{};
     ```

11.  对于类模板，你可以为模板参数定义缺省值：这些值就被成为缺省模板实参，而且他们还可以引用之前的模板参数：    

     ```
     template <typename T, typename CONT = std::vector<T>>
     class Stack {
     private:
       CONT elems;
     public:
       void push(T const&);
       void pop();
       T top() const;
       bool empty() const {
         return elems.empty();
       }
     };

     template <typename T, typename CONT>
     void Stack<T, CONT>::push(T const& elem) {
       elems.push_back(elem);
     }
     ```

     从上面我们可以看出：类模板含有两个模板参数，因此每个成员函数的定义都必须有两个参数 `template <typename T, typename CONT>`.   

12.  根据[11](#11)可以定义为：   
     1.  `Stack<int> int_stack;`   
     2.  `Stack<double, std::deque<double>> dbl_stack; // 可以指定容器类型`        

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

#  第六章 模板实战    
1.  ___包含模型___    
    1.  链接错误    
        大多数C或者C++程序员这么写非模板代码：  
        +  类和其他类型都被放在一个头文件中。   
        +  对于全局变量和函数，只有声明放在头文件中，定义则位于“.c”文件中。   
        这样所需的类型定义在整个程序都是可见的，链接器也不会给出重复定义的错误。  
        但这种方式并不适用于模板，比如：  

        ```
        //basics/my_first.hpp
        #ifndef MY_FIRST_HPP
        #define MY_FIRST_HPP

        //模板声明
        template <typename T>
        void print_typeof(T const&);

        #endif

        //basics/my_first.cpp
        #include <iostream>
        #include <typeinfo>

        #include "my_first.hpp"

        //模板的实现与定义
        template <typename T>
        void print_typeof(T const& x)
        {
          std::cout << typeid(x).name() << std::endl;
        }


        //最后在另一个“.c”文件中使用这个模板，并且把模板声明包含在这个文件中
        ///basics/my_first_main.cpp
        #include "my_first.hpp"

        int main()
        {
          double ice = 3.0;
          print_typeof(ice);//调用参数类型为double 的函数模板

          return 0;
        }
        ```
        
        大多数C++编译器会通过这个程序，但是链接器可能会报错，提示找不到函数`print_typeof()`的定义。  

        错误原因：函数模板`print_typeof()`的定义还没有实例化。为了使模板真正得到实例化，编译器必须知道：应该实例化那个定义以及要基于哪个模板实参来进行实例化。    
        遗憾的是：在上面你的例子中，这两部分信息位于飞来编译的不同文件里面，因此，当编译器看到`print_typeof()`调用，但还没有看到基于double实例化的函数定义的时候，它只是嘉定在别处提供了这个定义，并产生一个指向该定义的引用(让链接器利用该引用来解决这个问题)。另一方面，当编译器处理文件`my_first.cpp`的时候，它并没有指出：编译器必须基于特定实参对所包含的模板定义进行实例化。    
                
    2.  头文件中的模板    
        对于上面的问题，解决办法一是：将模板的定义也包含在声明模板的头文件中。

        将`#include "my_first.cpp"`添加到`my_first.hpp`的末尾，或者在每个使用模板".c"文件都包含`my_first.cpp`。或者就是不使用`my_first.cpp`，直接在头文件中声明加定义模板：    

        ```
        //basics/my_first2.hpp
        #ifndef MYFIRST_HPP
        #define MYFIRST_HPP

        //模板声明
        template <typename T>
        void print_typeof(T const&);

        //模板的实现/定义
        template <typename T>
        void print_typeof(T const& x)
        {
          std::cout << typeid(x).name() << std::endl;
        }

        #endif //MYFIRST_HPP
        ```

        这种模板组织方式成为包含模型。    
        结论一：包含模型虽然能够使编译、链接运行顺利进行，但是包含模型明显增加了头文件的开销，这正是包含模型的最大不足之处。在例子中，主要的开销并不是取决于模板定义本身的大小，而是在于模板定义中所包含的那些头文件。    
        结论二：“非内联函数模板”与“内联函数和宏”有个很重要的区别，那就是非内联函数模板在调用的位置并不会被扩展，而是当他们基于某种类型进行实例化之后，才会产生一份新的(基于该类型的)函数拷贝。这是一个自动化的过程，在编译结束的时候，编译器可能会在不同文件里产生两份拷贝，于是，当链接器发现同一个函数具有两种不同的定义时，就会报告错误。理论上讲，这不是我们关心的问题，这应该由C++编译系统来解决。      

2.  ___显式实例化___      
    包含模型之所以能够确保所有需要的模板都已经实例化是因为当需要进行实例化的时候，C++编译系统会自动产生所对应的实例化体。C++还提供了另外一种手工实例化模板的机制：显式实例化指示符。    
    在前面出现链接错误的例子中，我们为了避免这个链接期的错误，我们可以这么做：    

    ```
    //basics/my_first_inst.cpp
    #include "my_first.cpp"
    //基于类型double显式实例化print_typeof()
    template void print_typeof<double>(double const&);
    ``` 

    显式实例化指示符由关键字`template`和紧接其后的所需要实例化的实体(可以是类、函数、成员函数等等)的生命组成，而且，该声明是一个已经用实参完全替换参数之后的声明，该指示符也适用于成员函数和静态数据成员：    

    ```
    //基于int显式实例化MyClass<>的构造函数
    template MYClass<int>::MyClass();
    //基于int显式实例化函数模板max()
    template int const& max(int const&, int const&);
    ```

    还可以显式实例化类模板，这样就可以同时实例化它的所有类成员，但是有一点要注意，对于这些在前面已经实例化过的成员，就不能再次对它们实例化：    

    ```
    //基于int显式实例化类Stack<>
    template Stack<int>
    //基于string显式实例化Stack<>的某些成员函数
    template Stack<std::string>::Stack();
    template void Stack<std::string>::push(std::string const&);
    template std::string Stack<std::string>::top() const;

    //错误：对于前面已经显式实例化过的成员函数，不能再次对他们进行显式实例化
    template Stack<int>::Stack();

    ```

    对于每个不同的实体，在一个程序中最多只能有一个显式实例化体，换句话说，你可以同时显式实例化`print_typeof<int>`和`print_typeof<double>`, 但在同一个程序中每个指示符都只能够出现一次。  
    +  缺点：必须仔细跟踪每个需要实例化的实体，对于大项目而言，这种跟踪具有很大的负担。   
    +  优点：实例化在需要的时候才进行，这样避免了庞大头文件的开销。   

3.  ___采用包含模型还是显式实例化？___    
    为了能够自由选择包含模型或者显式实例化，我们可以把模板的定义和模板的生命放在两个不同的文件中，这两个文件都以头文件的形式存在。举个例子：    

    ```
    //stack.hpp
    #ifndef STACK_HPP
    #define STACK_HPP

    #include <vector>

    template <typename T>
    class Stack {
    private:
      std::vector<T> elems;

    public:
      Stack();
      void push(T const&);
      void pop();
      T top() const;
    };

    #endif //STACK_HPP


    //stackdef.hpp
    #ifndef STACKDEF_HPP
    #define STACKDEF_HPP

    #include "stack.hpp"

    template <typename T>
    void Stack<T>::push (T const& elem) {
      elems.push_back(elem);
    }

    ...

    #endif //STACKDEF_HPP
    ```

    现在如果我们希望使用包含模型，那么只要使用`#include "stackdef.hpp"`就可以了；如果想要显式实例化模板，就只是用`#include "stack.hpp"`,然后再提供一个含有所需要显式实例化指示符的“.c”文件：    

    ```
    //stacktest1.cpp
    #include "stack.hpp"
    #include <iostream>
    #include <string>

    int main() 
    {
      Stack<int> int_stack;
      std::cout << int_stack.top() << std::endl;
      int_stack.pop();

      Stack<std::string> string_stack;
      string_stack.push("hello");
      std::cout << string_stack.top() << std::endl;
    }

    //stack_inst.cpp
    #include "stackdef.hpp" //此处不应该是stack.hpp?
    #include <string>

    //instantiate class Stack<> for int
    template Stack<int>;

    //instantiate some member functions of Stack<> for strings
    template Stack<std::string>::Stack();
    template void Stack<std::string>::push(std::string const&);
    template std::string Stack<std::string>::top();
    ```

4.  ___模板和内联___      
    函数模板缺省情况下是内联的，___这句话是错误的___。 如果想要编写需要被实现为内联函数的函数模板，牛仍然应该使用inline修饰符(除非这个函数有余在类定义的内部进行实现的，这种情况是默认内联的)。   
