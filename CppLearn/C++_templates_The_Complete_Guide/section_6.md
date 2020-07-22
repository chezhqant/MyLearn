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
