#  第九章 模板中的名称    
1.  名称的分类    
    1.  如果一个名称是用域解析运算符(::)， 或者成员访问运算符(.或者->)来显示指定他所属的作用域，我们就该名称伟受限名称。例如`this->count`就是一个受限名称，而count则不是(即使前面没有符号，count实际上引用的也是一个类成员)。   
    2.  如果一个名称依赖于模板参数，我们称他为依赖型参数。例如，如果T是一个模板参数，`std::vector<T>::iterator`就是一个依赖型名称，但是如果T是一个已知的typedef（类型定义，例如int）那么，`std::vector<T>::iterator`就不是一个依赖型名称。以下是名称的分类：      

        |分类|说明和要点|     
        |:--:|:--------:|     
        |标识符|一个只由字母、下划线、数字组成的不间断字符序列，它不能以数字开始，而且某些标识符也为实现所保留：你不能在你程序中引用它们。|     
        |运算符id|在关键字 `operator` 后面紧跟一个运算符符号。例如 `operator new` 和 `operator []`，许多运算符都由其他表示方法，例如， `operator&` 可以写为 `operator bitand`|         
        |类型转换函数id|用来表示用户定义的隐式类型转换运算符。例如 `operator int&`，也可以写为 `operator int bitand`。      
        |模板id|是一个模板名称，在他后面紧跟着一对尖括号内部的模板实参列表。例如 `List<T, int, 0>`|     
        |非受限id|广义化的标识符，他可以是前面任何一种，或者析构函数的名称|     
        |受限id|用一个类名或者命名空间名称对一个非受限id进行限定，也可以只使用全局作用域解析符（如 `::f`）对它限定。显然，这种名称本身也可以是多次受限的|       
        |受限名称|标准中没有定义这个概念，当需要引用基于查找的名称时，使用了这个概念，它是一个受限id或者在前面显式是用成员访问符（ `.` 和 `->`）的非受限id。然而在某些上下文中，`class_member_data` 隐式等价于 `this->class_member_data`，但是只要不加前面的限制它就不是受限名称。也就是说，受限名称的成员访问运算符必须是显示给出的|     
        |非受限名称|除受限名称以外|       
        |依赖型名称|一个以某种方式依赖于模板参数的名称，显然，显示包含模板参数的受限名称或者非受限名称都是依赖型名称，对于一个用成员访问运算符（ `.` 或者 `->`）限定的受限名称，如果访问运算符左边的表达式类型依赖于模板参数，该受限名称也是依赖型名称。另外对于 `this->b` 中的 `b`，如果时在模板中出现的，那么b也是一个依赖型名称。最后，对于形如 `ident(x, y, z)` 如果某个参数（表达式）所属的类型时一个依赖于模板参数的类型，那么标识符 `ident` 也是一个依赖型名称, 另外，在下面中，依赖型名称不是在定义的时候查找的。|       
        |非依赖型名称|除依赖型名称之外|     

2.  名称查找    
    C++中的名称查找会设计到很多小细节，只有在涉及到下面两种情况的时候才会给出名称查找的相关细节：    
    1.  如果以直观的态度来对待会犯错的普通例子。    
    2.  C++标准（以某种方式）给出的哪些错误的例子。   
    受限名称的名称查找是在一个受限作用域内部进行的，该受限作用域由一个限定的构造所决定，如果该作用域是一个类，那么查找范围可以达到它的基类。但不会考虑到的外围作用域。下面的例子说明了这个基本原则：    
    ```
    int x;
    class B {
    public:
      int i;
    };

    class D: public B {};

    void f(D* pd)
    {
      pd->i = 3; //找到B::i
      D::x = 2; //错误，不能找到外围作用域中的::x
    }
    ```
    非受限名称的查找则相反，他可以（由内到外）在所有外围类中逐层地查找（但是在某个类内部定义的成员函数定义中，它会先查找该类和基类的作用域，然后才查找外围类的作用域），这种查找方式也被称为普通查找。下面的例子说明普通概念：    
    ```
    extern int count; // 
    int lookup_example(int count) // 
    {
      if (count < 0) {
        int count  = 1; // (3) 
        lookup_example(count);  // 非受限的count将会引用(3)
      }

      return count + ::count;  // 第一个非受限的count引用(2), 第二个受限的count引用(1)
    }
    ```
    对于非受限名称的查找，最近增加了一项新的查找机制--除了前面的普通查找，就是说非受限名称有时可以是用依赖于参数的查找（argument-dependent lookup, ADL）。我们可以通过max模版来说明这种机制：    
    ```
    template <typename T>
    inline T const& max(T const& a, T const& b)
    {
      return a < b ? b : a;
    }
    ```
    假设我们现在要让“在另一个名字空间中定义的类型“是用这个模板函数:   
    ```
    namespace big_math {
      class BigNumber {
        // ...
      };

      bool operator<(BigNumber const&, BigNumber const&);
      // ...
    }

    using big_math::BigNumber;
    void g(BigNumber const& a, BigNumber const& b)
    {
      BigNumber x = max(a, b);
      // ...
    }
    ```
    问题是max()模板并不知道big_math命名空间，因此普通查找也找不到应用于BigNumber类型值的`operator<` 。如果没有特殊规则的话，这种限制将会大大减少C++命名空间中模板的应用。   
    __ADL__:    
    ADL只能应用与非受限名称。在函数调用中，这些名称看起来像是非成员函数。对于成员函数名称或者类型名称，如果普通查找能够找到该名称，那么将不会应用ADL。如果把被调用的函数的名称(如max)用圆括号括起来，也不会是用ADL。否则，如果名称后面的括号里面有（一个或者多个）实参表达式，那么ADL将会查找这些实参的associated class(关联类)和associated namespace(关联命名空间)。   
    对于给定类型，对于由associated class和associated namespace所组成的集合的准确定义，我们可以通过下列规则来确定：     
    1.  对于基本类型，该集合为空集。    
    2.  对于指针和数组类型，该集合是所引用类型（譬如对于指针而言，它所引用的类型是”指针所指向对象“的类型）的associated class和associated namespace。    
    3.  对于枚举类型，associated namespace指的时枚举声明所在的namespace。对于类成员，associated class指的是她所在的类。   
    4.  对于class类型（包含联合类型），associated class集合包含：该class类型本身、他的外围类性、直接基类和间接基类。associated namespace集合是每个associated class所在的namespace。如果这个类是一个类模板实例化体，那么还包含：模板类型实参本身的类型、声明模板的模板实参所在的class和namespace。    
    5.  对于函数类型，该集合包含所有参数类型和返回类型associated class和associated namespace。    对于类X的成员指针类型，除了包含成员相关的associated namespace和associated class，该集合还包含与X相关的associated namespace和associated class。   
    至此，ADL会在所有的associated class和associated namespace中依次查找，就好像依次地直接是用这些命名空间进行限定一样。唯一的例外情况是：它会忽略using-directives（using指示符）。下面的例子说明这点：      
    ```
    #include <iostream>

    namespace X {
      template<typename T> void f(T);
    }

    namespace N {
      using namespace X;
      enum E { e1 };

      void f(E) {
        std::cout << "N::f(N::E)\n";
      }
    }

    void f(int)
    {
      std::cout << "::f(int) called\n";
    }

    int main()
    {
      ::f(N::e1); // 受限函数名称：不会使用ADL
      f(N::e1); //普通查找将找到f(); ADL将找到N::f(); 将会调用后者
    }
    ```
    我们可以看出：在这里例子中，当执行ADL的时候，命名空间N中的using-directive被忽略了，是肯定不会调用X::f()的。     
2.  友元名称插入      
    在类中的友元函数声明可以是该友元函数的首次声明。在此前提下，对于包含这个友元函数的类，假设它所属的最近命名空间作用域（可能是全局作用域）为作用域A，我们就可以认为该友元函数是在作用域A中声明的。在插入友元声明的（类）作用域中，该友元声明是否应该是可见的呢？实际上，多数情况下只有在模板中才会出现这个问题，考虑下面的例子：     
    ```
    template <typename T>
    class C {
      // ...
      friend void f();
      friend void f(C<T> const&);
      // ...
    };

    void g(C<int>* p)
    {
      f(); // f() 在此处可见嘛？
      f(*p); // f(C<int> const&)在此处可见嘛？
    }
    ```
    这里的问题是：如果友元声明在外围类汇总是可见的，那么实例化一个类模板可能会使一些普通函数（如f()）的声明也成为可见的。因此，C++标准规定：通常而言，友元声明在外围（类）作用域中是不可见的。    
    然而，存在一个有趣的编程技术，它依赖于只在友元声明中声明（或者定义）某个函数。因此C++标准还规定：如果友元函数所在的类属于ADL的关联类集合，那么我们在这个外围类是可以找到该友元声明的。    
    再次考虑上面的例子。调用f()并没有关联类或者命名空间，因为他没有任何参数，不能利用ADL，因此是个无效的调用。然而，f(*p)具有关联类C<int>（因为*p的类型是C<int>）；因此，只要我们在调用之前完全实例化了类C<int>，就可以找到第二个友元函数(即f)的声明。为了确保这一点，我们可以假设：对于设计在关联类中友元查找的调用，实际上会导致该（关联类）被实例化（如果没有实例化的话）。     
3.  插入式类名称      
    如果在类本身的作用域中插入该类的名称，我们就称该名称为插入式类名称。他可以被看作是位于 __该类作用域中的一个非受限名称__。而且是可访问的受限名称（因为如果作为受限名称，该名称是不可访问的，因为我们在此并不是是用该名称来标识构造函数:       
    ```
    int C;
    class C
    {
    private:
      int i[2];
    public:
      static int f()
      {
        return sizeof(C);
      }
    };

    int f()
    {
      return sizeof(C);
    }
    ```
    以上代码中，成员函数C::f返回类型C的大小，而函数::f()返回变量C的大小，即int对象的大小。   
    类模板也可以有插入式类名称。但是它和普通插入式类名称有些区别：他们后面可以紧跟模板实参（在这种情况下，他们也被称为插入式类模板名称）。但是如果后面没有紧跟模板实参，那么他们代表的就是用参数来标识实参的类（例如，对于局部特化，还可以用特化实参代表对应模板实参）：      
    ```
    template <template<typename> class TT>
    class X {};

    template <typename T>
    class C
    {
      C* a; // 正确，等价与C<X>* a;
      C<void> b; // 正确
      X<C> c; // 错误，后面没有模板实参列表的C不被看作模板
      X<::C> e; // 正确
    };
    ```
    从上面我们可以看到，如何是用非受限名称来引入插入式名称（即Ｃ），如果这些非受限名称后面没有紧跟模板实参列表，那么是不会被看作模板名称的。为了避免这种情况，我们可以在模板民成前面加上作用域限定符（::），这样就可以顺利通过编译        
4.  有关模板名称的问题主要是：这些名称不能有效地确定，尤其是模板中不能引用其他模板的名称。以为内其他模板的内容可能会由于显式特化，而是原来的名称失效：      
    ```
    template <typename T>
    class Trap
    {
    public:
      enum { x }; // (1) 这里的x不是一个类型
    };

    template <typename T>
    class Vectim
    {
    public:
      void poof()
      {
        Trap<T>::x*y; // (2) 这里究竟是声明还是乘积
      }
    };

    template <>
    class Trap<void> // 会给后面带来麻烦的特化
    {
    public:
      typedef int x; // (3) 这里的x是一个类型
    };

    void boom(Victim<void>& bomb)
    {
      bomb.poof();
    }
    ```
    当编译器解析(2)时，他必须确定它所看到的时一个声明还是一个乘积，而这个结果取决于依赖受限名称 `Trap<T>::x` 是否是一个类型名称。编译器这时会查找模板 `Trap`，并且在上面找到这个模板：根据行(1)，`Trap<T>::x` 并不是一个类型，从而让我们相信行(2)是一个乘积。然而，在后面T为void的特化中，我们改写了泛型的 `Trap X<T>::x`，让它变为一个类型，这完全违背了前面的源代码，因为这种情况下，类 `Victim` 中的 `Trap<T>::x` 实际上是一个int类型。   
    C++ 的语言定义通过下面的规定来解决这个问题：通常而言，依赖型受限名称并不会代表一个类型，除非在该名称的前面有关键字 `typename` 前缀。对于类型名称，如果不加上 `typename` 前缀，那么在替换模板实参之后，就不会被看成类型名称，从而程序也是无效的。另外， `typename` 这种用法和前面用于表示模板类型参数的用法是不一样的：这里不能是用关键字 `class` 来等价替换 `typename` 。总之，当类型名称有以下性质，就应该在该名称前面添加 `typename` 前缀：    
    1.  名称出现在一个模板中      
    2.  名称受限的      
    3.  名称不是用于指定基类继承的列表中，也不是位于引入构造函数后的成员初始化列表中      
    4.  名称依赖于模板参数      
    只有当前面三个条件同事满足的情况下，才能使用 `typename` 前缀：      
    ```
    template <typename T> // 1
    struct S: typename X<T>::Base // 2
    {
      S(): typename, X<T>::Base(typename X<T>::Base(0)) // 3, 4
      {
        typename X<T> f() // 5
        {
          typename X<T>::C *p; // 指针 p 的声明，6
          X<T>::D* q; // 乘积
        }
        
      }

      typename X<int>::C * s; // 7
    };

    struct U
    {
      typename X<int>::C * pc; // 8
    };
    ```
    在上面的代码中，第一个 `typename` 用来引入一个模板参数，因此并不适用前面的规则。第2个和第三个typename的使用属于前面规则3所禁止的用法：在这种情况下，基类名称都不能添加typename前缀，然而，第4个typename是必不可少的，因为这里的积累名称不是位于初始化列表中，也不是位于派生类的继承约定：而是为了给予实参0构造一个临时X<T>::Base表达式。第5个typename同样也是禁止的，因为他后面的名称X<T>并不是一个受限名称。对于第6个typename，如果是期望声明成一个指针，那么这个typename就是必须的。第7个typename是可选的，因为它符合前面的3跳规则，但是不符合第4条规则，第8个typename是禁止的，因为他不是在模板中使用。      
