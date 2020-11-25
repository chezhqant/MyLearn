___注： 我觉得我有可能理解不对的，就带上英文___     

1.  附录C     

    1.  函数指针， 已经成员函数的指针不能够重载，因为在运行期间函数的调用就取决于指针。(不太明白这句话的意思，也没有demo); calls through function pointers and calls through pointers to member functions are not subject to overload resolution because the function to call is entirely determined(at runtime) by the pointers.   
    2.  宏函数不能够重载      
    3.  调用一个具名函数大致的过程：    
        1.  所有的同名函数组成一个集合。    
        2.  必要的话，这个集合可以随时被各种方式调整。    
        3.  从集合中将一点都不能匹配上的候选者干掉。这个过程之后剩下的集合被称为viable function candicates.     
        4.  重载选用最合适的候选者。如果有的话，当然就选择它喽，没有的话，那就是ambiguous.      
        5.  被选中的候选者需要被check一下。例如，如果他是`=delete`函数或者是类的私有函数同样需要报告错误。      
    4.  简单的重载      
        1.  一个最合适的候选者，它的所有参数都应该比其他候选者合适。    
            ```
            void combine(int, double);
            void combine(double, int);

            int main()
            {
              combine(1, 2); // ambiguous
            }
            ```
            像这种情况就很无奈。按照这条规则，我们就可以总结出一些从最匹配到最不匹配的规律：    
            1.  完美匹配。就是参数具有表达式的类型。当然，参数在这时候可能有引用呀，或者cv操作符呀，都无所谓的。    
            2.  次一点的匹配(minor adjustments)。包含，例如，数组decay到指针，或者像int** 匹配到 const* int const*.    
            3.  再次一点(type promotion)，比如说bool char, short 或者某些情况下的enum转换成int；unsigned int, long, unsigned long 转换成float或者double。    
            4.  再次一点(match with standard conversion only)，像int转换成double, 或者float; 或者子类转换成public、unambiguous基类（不明白 unambiguous基类是什么），当然这种转换不是通过转换操作符或者转换构造函数的隐式调用来完成的。就是说这种情况下的子类转换成父类，不是通过调用转换操作符或者转换构造函数来完成的。    
            5.  再次一点（使用用户自定义的转换，比如转换操作符或者转换构造函数, users-defined conversion），可以有一些隐式转换。    
            6.  任意匹配类型。    
                ```
            // 针对第5条：
            class X {
            public:
              X(int);
            };

            void f(X);
            f(7); // 此时会发生隐式转换
                ```
        2.  重要的一点是，重载发生在模版推导之后，我记得模版推导是在编译期间。所以不知道是发生在编译期间还是运行期间。      
            ```
            template <typename T>
            void strange(T&&, T&&);

            template <typename T>
            void bizarre(T&&, double&&);

            int main()
            {
              double val = 1.2;
              srange(val, 3.4);
            }
            // 因为val推导出来的T的类型时double&, 而3.4是右值，推导出来的T是double.这当然要出错。对于通用引用的推导，可以看一下effective modern c++
            ```
    5.  非静态类型的成员函数包含有this指针      
        一般情况隐藏的*this是引用类型的。或者是const&类型的。这段话还是打上来吧。   
        Calls to nonstatic member functions have a hidden parameter that is accessible in the definition of the member function as *this. For amember function of a class MyClass, the hidden parameter is usually of type MyClass&(for non-const member functions) or MyClass const&(for const member functions). This is somewhat surprising given that this has a pointer type. It would have been nice to make equivalent to what is now *this. Howeve, this was part of an early versioin of C++ before reference types were part of the language, and by the time refernce types were added, too much code already depended on this being a pointer.      
        大致意思就是现代C++可以将this看成`*this`, 但是以前的代码都把this看成指针的。      
        就是说*this也会像explicit parameters参与重载。    
        大部分情况是OK的，分析起来不会反直觉，但是有些情况会特殊一些：      
        ```
        class BadString {
        public:
          BadString(const char*);

          // ...

          // characteraaccess through subscripting
          const char& operator[] (std::size_t);                    // #1
          
          // implicit conversion to null-terminated bytes string
          operator char* ();                                 // #2
          operator const char* ();
        }; 

        int main()
        {
          BadString("correct");
          str[5] = 'c'; // possibly an overload resolution ambiguously
        }
        ```
        这问题就是在于：    
        1.  第一种匹配： `const char& operator[] (std::size_t);`，这种因为`std::size_t`不够匹配。     
        2.  第二种匹配： 先匹配`operator const char* ();`, 然后就获取的时指针喽，指针可以用`[]`访问元素。因为指针是用`[]`来访问，接受的参数是`ptrdiff_t`，一般情况下就是int。因此能够完美匹配`5`，但是又因为通过内建类型匹配（就是指针操作`[]`）是用户自定义匹配，等级不够高？       
            the built-in subscript operator. Indeed if we apply the implicit conversion operator to str(which  is the implicit member function argument), we obtain a pointer type, and now the built-in subscript operator applies. This built-in operator takes an argument of type ptrdiff_t, which on many platforms is equivalent to int and therefore is a perfect match for the argument 5. So even though the build-in subscript operator is a poor match(by user-defined conversion) for the implied argument, it is a better match than the operator defined at #1 for the actual subscript!        

# 未完待续      
