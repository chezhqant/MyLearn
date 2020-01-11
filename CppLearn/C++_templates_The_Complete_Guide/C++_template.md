___C++ Template, The Complete Guide___

# 第二章 函数模板   
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
5.  模板在使用的时候被编译了两次：   
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

# 第三章 类模板   
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

10. 类模板可以被局部特化：    

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

11. 对于类模板，你可以为模板参数定义缺省值：这些值就被成为缺省模板实参，而且他们还可以引用之前的模板参数：    

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

  从上面我们可以看出：类模板含有两个模板参数，因此每个成员函数的定义都必须有两个参数`template <typename T, typename CONT>`.   

12.   根据[11](#11)可以定义为：   
  1.  `Stack<int> int_stack;`   
  2.  `Stack<double, std::deque<double>> dbl_stack; // 可以指定容器类型`        
