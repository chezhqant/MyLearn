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
