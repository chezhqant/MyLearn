# 第八章 深入模板基础   
1.  参数化声明    
    1.  eg，它给出了函数模板和类模板，分别作为类成员的声明和普通命名空间的声明：    
        ```
        template <typename T>
        class List { // 作为命名空间作用于的类模板
        public:
          template <typename T2> // 成员函数的模板
          List(List<T2> const&); // 构造函数
        };

        template <typename T>
        template <typename T2>
        List<T>::List(List<T2> const& b) //位于类外部的成员函数模板定义
        {}

        template <typename T>
        int length(List<T> const&); //位于外部命名空间作用域的函数模板

        class Collection {
          template <typename T> // 位于类内部的成员类模板
          class Node {}; // 该类模板的定义

          template <typename T> // 另一个作为成员(位于外围累的内部)的类模板
          class Handle; // 该类模板在此处没有定义

          template <typename T> // 位于类内部的成员函数模板的定义
          T* alloc() {} // 显式内联函数
        };

        template <typename T> // 一个在累的外部定义的成员类模板
        class Collection::Handle { // 该类模板的定义

        };
        ```

        从上面可以看出，在所属外围类的外部进行定义的成圆模板可以具有多个模板参数子句`template<...>`。子句的顺序是从最外围的类模板开始，依次到达每部模板。
    2.  联合模板也是被允许的：    

        ```
        template <typename T>
        union AllocChunk {
          T object;
          unsigned char bytes[sizeof(T)];
        };
        ```

    3.  函数模板生命也可以具有缺省调用实参：    

        ```
        template <typename T>
        void report_top(Stack<T> const&, int number = 10);
        template <typename T>
        void fill (Array<T>*, T const& = T()) // 对于基本类型 T() = 0
        ```

        后面一个声明说明了，缺省调用实参可以依赖于模板参数。当调用fill()函数时，如果提供了第二个函数调用参数的话，就不会实例化这个缺省实参。这同时说明了。即使不能基于特定类型T来实例化缺省调用实参，也可能不会出现错误：   

        ```
        class Value {
        public:
          Value(int); // 不存在缺省构造函数
        };

        void init (Array<Value>* array) {
          Value zero(0);
          fill(array, zero); // 正确，没有使用 = T()
          fill (array); // 错误：使用了= T()， 但当T=Value时，缺省构造函数无效。
        }
        ```

        除了两种基本类型的模板之外，还可以使用相似符号来参数化其他的3种声明。这3种生命分别都有与之对应的类模板成员的定义：     
        +  类模板的成员函数的定义   
        +  类模板的嵌套类成员的定义     
        +  类模板的静态数据成员的定义   
        尽管也可以对这三者进行参数化，但是他们的定义使用的都不是自身(即第一次使用)的模板，而是外围类模板。他们的参数也double是由外围类模板来决定的：   

        ```
        template <int I>
        class CupBoard {
          void open();
          class Shelf;
          static double total_weight;
        };

        template <int I>
        void CupBoard<I>::open() {}

        template <int I>
         class CupBoard<I>::Shelf {};

        template <int I>
        double CupBoard<I>::total_weight = 0.0;
        ```

        尽管这种参数化定义通常也被称为模板，但是存在不适用这个概念的情况。    
    4.  虚成员函数：成员函数模板不能被声明为虚函数。因为虚函数调用机制的普遍实现double使用了一个大小固定的表。每个虚函数double对应表的一个入口，然而成员函数模板的实例化个数，要等到整个程序都翻译完成之后才能够确定，这就和表的大小(固定的)发生了冲突。
    5.  相反的，类模板的普通成员可以是虚函数，因为当类被实例化后，他们的个数是固定的：   

        ```
        template <tyepname T>
        class Dynamic {
        public:
          virtual ~Dynamic(); // OK, 每个Dynamic只对应一个析构函数
          
          template <typenmae T2>
          virtual void copy(T2 const&); // 错误，在确定Dynamic<T>实例的时候，并不知道copy()的个数
        }
        ```

2.  模板参数    
    1.  现今存在3种模板参数：   
        +  类型参数   
        +  非类型参数     
        +  模板的模板参数   
        模板声明要引入参数化自居，模板参数就是砸该子句中声明的。这类生命可以把模板参数的名称省略不写：   

        ```
        template <typename, int> // 可以不写
        class X;
        ```

        如果在模板生命后面需要引用参数名称，那么这些参数名称要写上的，在同一对尖括号的内部，位于后面的模板参数声明可以引用前面的模板实参名称，但前面的不能引用后面的：    
        
        ```
        template <typename T, \\ 在第2个参数和第3个参数中double使用了第1个参数T
                  T* root,
                  template<T*> class Buf>
        class Structure;
        ```

    2.  类型参数，类型参数是通过关键字typename和class引入的，关键字后面跟一个简单的标识符，后面用逗号来隔开下一个参数生命，等号代表接下来的是缺省模板实参，一个封闭的尖括号(>)表示参数化子句结束。   

    3.  非类型参数：在编译期或者链接期可以确定的常值：    
        +  整型或者枚举类型   
        +  指针类型（包含普通对象的指针类型、函数指针类型、指向成员的指针类型）   
        +  引用类型（只想对象或者只想函数的引用都是允许的）   
        +  非模板参数的声明也可以使用关键字typename：   
           
          ```
          tempalte <typename T, // 类型参数
                    typename T::Allocator* Allocator> // 非类型参数
          class List;
          ``` 
          区分很容易，第一个typename的后面是简单的标识符T，而第2个typename的后面是一个受限的名称。
          函数和数组类型也可以被指定为非模板参数，但是要把他们先引用地转换为指针类型，这种转型也成为decay：
          
          ```
          template <int buf[5]> class Lexer; // buf 实际上是一个int*类型
          template <int* buf> class Lexer; // 正确，这是上面的重新声明
          ```
          
          非类型模板参数的声明和变量的声明很相似，但是他们不能具有static、mutable等修饰符，只能具有const和volatile限定符。    
          非类型模板参数只能是右值：他们不能被取值，也不能被赋值。    
    4.  模板的模板参数：模板的模板参数是代表类模板的占位符，他的声明和类模板的声明很相似，但是不能使用关键字struct和union：    

        ```
        template <
                  template<typename X> class C>; // 正确
        void f(C<int>* p);

        template <
                  template<typename X> struct C>; // 错误
        void f (C<int>* p);

        template <
                  template<typename X> union C>; // 错误
        void f(C<int>* p);
        ```

        模板的模板参数的参数可以具有缺省模板实参，只要在调用时没有指定该参数的情况下，才会应用缺省模板实参：   

        ```
        template <template<typename T, 
                           typename A = MyAllocator> class Container>
        class Adaptation {
          Container<int> storage; // 隐式等同于Container<int, MyAllocator>
        };
        ```

        对于模板的模板参数而言，它的参数名称只能被自身其他参数的声明使用：      
        
        ```
        template <template<typename T, T*> class Buf>
        class Lexer {
          static char storage[5];
          Buf<char, &Lexer<Buf>::storage[0]> buf;
        };
        
        template <template<typename T> class List>
        class Node {
          static T* storage; // 错误：模板的模板参数的参数不能在这里使用
        };
        ```

        通常而言，模板的模板参数的参数的名称并不会在后面被使用到，因此改参数也经常被省略不写，即没有命名：     
        
        ```
        template <template<typename, typename = MyAllocator> class Container>
        class Adaptation {
          Container<int> storage; // 隐式等价于Container<int, MyAllocator>
        };
        ```
