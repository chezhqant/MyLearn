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
