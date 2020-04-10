___深入理解C++11___

### C++引入新的关键字   
1.  [alignas]
2.  [alignof]
3.  [decltype]
4.  [auto重新定义]
5.  [static_assert]
6.  [using重新定义]
7.  [noexcept]
8.  [export]
9.  [nullptr]
10.  [constexpt]
11.  [thread_local]

###

1. \_Pragma操作符   
    在c/c++标准中，`#pragma`是一条预处理指令。简单的说，`#pragma`是用来想编译器传达语言标准以外的信息。例如：
    ```
    #pragma once
    ```
    那么该指令会指示编译器(如果编译器支持)，该头文件应该只被编译一次。这与使用如下代码定义头文件的效果是一样的：
    ```
    #ifndef THIS_HEADER
    #define THIS_HEADER

    #endif
    ```
    在C++11中，标准定义了与预处理指令`#pragma`功能相同的操作符`_Pragma`。格式如下：
    ```
    _Pragma(字符串字面量)
    ```
    其使用方法跟`sizeof`等操作符一样，将字符串字面量作为参数写在括号中即可。那么要达到与上例`#pragma`类似的效果，如下：
    ```
    _Pragma("once");
    ```
    相比预处理指令`#pragma`，由于`_Pragma`是一个操作符，因此可以用在宏中：
    ```
    #define CONCAT(x) PRAGMA(concat on#x)
    #define PRAGMA(x) _Pragma(#x)
    CONCAT(..\concat.dir)
    ```
    这里`CONCAT(..\concat.dir)最终会产生_Pragma(concat on "..\concat.dir")`，而`#pragma`则不能在宏中展开，灵活性没有`_Pragma`强。     

2.  变长参数的宏定义以及\_\_VA_ARGS\_\_     
    在c99标准中，程序员可以使用变长参数的宏定义。变长参数的宏定义是指在宏定义中参数列表的最后一个参数为省略号，而预定义宏`__VA_ARGS__`则可以在宏定义的实现部分替换掉省略号所代表的字符串。    
3.  宽窄字符串的连接      
    在之前的C++标准中，将窄字符串(char)转换成宽字符串(wchar_t)是未定义的行为。而在C++11标准中，在将窄字符串和宽字符串进行连接时，支持C++11标准的编译器会将窄字符串转换为款字符串，然后再域宽字符串连接。    
4.  long long整型   
    long long类型进入了C99标准， 后面也进入了C++11标准。有两种long long: long long 和 unsigned long long，在C++11中，标准要求long long整型可以在不同平台上有不同的长度，但至少也有64位。在写常数字面量时，可以是用LL后缀、ll后缀；或者使用ULL、ull、Ull、uLL表示一个unsigned long long类型的字面量。
    与long long等价的类型：long long、signed long long、long long int、signed long long int; unsigned long long等价的 unsigned long long int。    
    同其他整型一样，要了解平台上long long 大小的方法就是查看<climits> 或者<limits.h>，与long long相关的有三个：LLONG_MIN、LLONG_MAX、ULLONG_MIN，分别代表 最大值，最小值，最大unsigned long long值。        
5.  C++11一共定义了5中标准的有符号整型：signed char、short int、int、long int、 long long int。   
    C++规定，扩展的整型必须与标准类型一样，有符号和无符号类型占用同样大小的内存空间。
    隐式转换规则：    
    1.  长度相同的情况下，标准整型的等级高于扩展类型，比如long long int和_int64如果都是64位长度，则long long int类型的等级高。  
    2.  长度越大的整型等级越高，比如long long int等级高于int.   
    3.  相同大小的有符号和无符号类型等级相同，比如int, unsigned int等级相同。   
    4.  在进行隐式整型转换的时候，一般都是按照低等级整型转换为高等级整型，有符号转换为无符号。    
5.  宏\_\_cplusplus   
   ```
   #ifdef __cplusplus
   extern "C" {
   #endif

   #ifdef __cplusplus
   }
   #endif
   ```
   这种类型的头文件可以被#include到C文件进行编译，也可以被#include到C++文件中进行编译。由于extern "C"可以抑制C++对函数名、变量名等符号进行重整，因此编译出的C目标文件和C++目标文件中的变量、函数名称等符号都是相同的，链接器可以可靠地对两种类型的目标文件进行连接。    
   程序员可能认为`__cpluscplus`这个宏只有被定义了和未定义两种状态。事实上并非如此`__cplusplus`这个宏通常被定义为一个整型值。而且随着标准变化，`__cplusplus`宏一般会是一个比以往标准更大的值。在C++03它的值为199711L, 在C++11标准中，它的值为201103L。这点变化可以为代码所用，比如程序员想要确定代码是是用C++11编译器进行编译时：
   ```
   #if __cplusplus < 201103L
   #error "should use C++11 implementation"
   #endif
   ```
   这里是用预处理指令，使得不支持C++11的立即终止。    
6.  静态断言    
    1.  运行时与预处理时    
        在C++中，标准在<cassert>或者<assert.h>头文件定义了assert宏，用于在__运行时__进行断言：    
        在C++中，程序员也可以定义宏NDEBUG来禁用assert宏。这对于发布程序来说是必要的，因为用户对程序退出是敏感的。assert宏在<cassert>中的实现方式类似于下面：   
        ```
        #ifdef NDEBUG
        #define assert(expr) (static_cast<void>(0)
        #else
        ...
        #endif
        ```
        一旦定义了NDEBUG宏，assert宏将被展开为一条无意义的C语句（通常会被编译器优化掉）    
        \#if 和 #error通常也可以在预处理阶段进行断言。
    2.  静态断言与static_assert     
        相交于上面两个运行的阶段来说，有时候我们希望在编译时能够做断言：
        ```
        #include <casert>
        #include <cstring>

        using namespace std;

        template<typename T, typename U>
        int bit_copy(T& a, U& b) {
          assert(sizeof(b) == sizeof(a));
          memcpy(&a, &b, sizeof(b));
        }

        int main()
        {
          a = 0x2468;
          double b;
          bit_copy(a, b);
        }
        ```
        上面，如果bit_copy不被调用，我们将无法触发断言，实际上，正确产生断言的时机应该在模板 实例化上，即编译期间。   
        实现编译期间断言的方法：
        1.  Boost内置的BOUST_STATIC_ASSERT断言机制(利用sizeof)。    
        2.  利用除“0”导致编译器报错这个特性来实现静态断言。       
        ```
        #define assert_static(e)          \
        do {                              \
          enum{assert_static_ = 1 / (e)}  \
        } while(false)
        ```

        真正起作用的是`1/(e)`这个表达式，
