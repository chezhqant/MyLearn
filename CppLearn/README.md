***this directory is just for learning C++ and its related knowledge.*** </br>

***<p align="center"> CONTENT </p>*** </br>

# C基本知识
## [二维数组指针](https://blog.csdn.net/nice__xixi/article/details/82081595) </br>


# [C++基础知识](https://www.runoob.com/cplusplus/cpp-tutorial.html) </br>
## [參考這個](https://github.com/huihut/interview#-cc) </br>
## C++/C和Python相互调用</br>
1.1.1 [资料一](https://cloud.tencent.com/developer/article/1174629)</br>
1.1.2 [LeetCode刷题](../LeetcodeLearn)</br>
## [C++内存对齐](https://www.cnblogs.com/zhao-zongsheng/p/9099603.html)</br>
## 常量指针和指针常量
> 常量指针(const int\*): 该指针指向的那个变量是不可被修改的；但它本身的指向可以被修改。</br>
> 指针常量(int \*const 或者 int const\*): 该指针指向的变量是可以被修改的；但它本身的指向是不能被修改的。</br>
## [弱引用的理解](https://www.cnblogs.com/fengc5/p/5316670.html)</br>
## [强引用与弱引用的比较](https://blog.csdn.net/Sun960705/article/details/79099533)</br>
## 类</br>
### [this指针](https://www.cnblogs.com/Star-Lit/p/8623050.html)</br>

# C++网络编程</br>
1. OSI七层模型</br>
    1.1. [解析一](https://blog.csdn.net/qq\_16093323/article/details/79582554)</br>
    1.2. [解析二](https://blog.csdn.net/taotongning/article/details/81352985)</br>

# 数据库</br>


# C++多线程\_多进程</br>


# Makefile</br>


# Shell </br>
1. [shell中的符号](https://www.jb51.net/article/120595.htm)</br>


# 设计模式 </br>
1. [观察者模式](https://www.jianshu.com/p/4b0aee15cdb8)</br>
2. [代理模式](https://blog.csdn.net/a369189453/article/details/81275740)</br>


# 异常</br>
## [noexcept](https://www.cnblogs.com/sword03/p/10020344.html)</br>


# 预处理、编译、汇编、链接</br>
## 预处理</br>
#### 预处理器</br>
预处理器是指令，在实际编译开始之前，预处理器会给编译器指令来预处理需要编译的信息。

所有的预处理指令以＃开头，可能在预处理指令行之前出现的只有空白字符。预处理指令是不是 C++ 语句，所以它们不会以分号(;)结束。

你已经在所有的例子中都看到了 #include 指令。这个宏用于将头文件包含到源文件。

还有许多 C++ 支持的预处理指令，如#include，#define， #if， #else， #line 等等。下面我们来看一些重要的指令：

##### define 处理器
#define 处理指令用来创建符号常量。这个符号常量被称为宏。指令的一般形式是：

```
    #define macro-name replacement-text 
```
当这一行出现在一个文件中时，在程序被编译之前，该文件中的所有后续出现的 macro-name 将会被 replacement-text 替换掉。 例如：
```
    #include <iostream>
    using namespace std;

    #define PI 3.14159

    int main ()
    {

    cout << "Value of PI :" << PI << endl; 

    return 0;
    }
```
现在，让我们对这个代码进行预处理来看一看结果。假设我们有源代码文件，那么我们用 -E 选项编译它并重定向结果到 test.p。现在，如果你查看 test.p，会发现里面有大量的信息，并且你会在底部发现值已经被替换了，如下所示：
```
    $gcc -E test.cpp > test.p

    ...
    int main ()
    {

    cout << "Value of PI :" << 3.14159 << endl; 

    return 0;
    }
```
##### 函数宏
你可以用#define定义一个带有如下参数的宏：
```
    #include <iostream>
    using namespace std;

    #define MIN(a,b) (((a)<(b)) ? a : b)

    int main ()
    {
       int i, j;
       i = 100;
       j = 30;
       cout <<"The minimum is " << MIN(i, j) << endl;

    return 0;
    }
```
如果我们编译并运行上述代码，将会产生以下结果：
```
    The minimum is 30
```
##### 条件编译
有几种不同的指令，其可用于有选择的编译程序源代码的一部分。这个过程被称为条件编译。

条件预处理器结构很像 if 选择结构。思考下面的预处理代码：
```
    #ifndef NULL
       #define NULL 0
    #endif
```
你可以编译一个用于调试的程序，并且可以用单个宏打开或关闭调试开关，如下所示：
```
    #ifdef DEBUG
       cerr <<"Variable x = " << x << endl;
    #endif
```
如果符号常量 DEBUG 定义在#ifdef DEBUG指令之前，那么程序中的 cerr 语句会被编译。你可以使用＃if 0语句注释掉程序的一部分，如下所示：
```
    #if 0
       code prevented from compiling
    #endif
```
我们来用下面的例子试一下：
```
    #include <iostream>
    using namespace std;
    #define DEBUG

    #define MIN(a,b) (((a)<(b)) ? a : b)

    int main ()
    {
       int i, j;
       i = 100;
       j = 30;
    #ifdef DEBUG
       cerr <<"Trace: Inside main function" << endl;
    #endif

    #if 0
       /* This is commented part */
       cout << MKSTR(HELLO C++) << endl;
    #endif

       cout <<"The minimum is " << MIN(i, j) << endl;

    #ifdef DEBUG
       cerr <<"Trace: Coming out of main function" << endl;
    #endif
    return 0;
    }
```
如果我们编译并运行上述代码，将会产生以下结果：
```
    Trace: Inside main function
    The minimum is 30
    Trace: Coming out of main function
```
##### #和 ##操作符
在 C++ 和 ANSI/ISO C 中#和##预处理器操作符是可用的。

＃操作符会将要替代的文本符号转换成用双引号引起来的字符串。

思考下面的宏定义：
``` 
    #include <iostream>
    using namespace std;

    #define MKSTR( x ) #x

    int main ()
    {
    cout << MKSTR(HELLO C++) << endl;

    return 0;
    }
```
如果我们编译并运行上述代码，将会产生以下结果：
```
    HELLO C++
```
让我们来看看它是如何工作的。

这很容易理解，C++ 预处理器将下面一行代码：
```
    cout << MKSTR(HELLO C++) << endl;
```
转变成了下面这一行的代码：
```
    cout << "HELLO C++" << endl;
```
##操作符是用来连接两个符号的。

例子如下所示：
```
    #define CONCAT( x, y )  x ## y
```
当 CONCAT 出现在程序中时，它的参数会被连接起来，并用其来取代宏。例如，CONCAT(HELLO，C++)，在程序中会 “HELLO C++” 替代。例子如下所示。
```
    #include <iostream>
    using namespace std;

    #define concat(a, b) a ## b
    int main()
    {
       int xy = 100;

       cout << concat(x, y);
       return 0;
    }
```
如果我们编译并运行上述代码，将会产生以下结果：
```
    100
```
让我们来看看它是如何工作的。

这很容易理解，C++ 预处理器将下面一行代码：
```
    cout << concat(x, y);
```
转换成了下面这一行的代码：
```
     cout << xy;
```
##### C++ 预定义的宏

C++ 提供了许多预定义的宏，如下所示：
\begin{array}{|c|c|}
\hline
\text{宏}               & \text{宏描述}
\hline
\text{\_\_LINE\_\_}     & \text{编译过后，其包含了当前程序行在程序内的行号}
\hline
\text{\_\_FILE\_\_}     & \text{编译过后，其包含了当前程序的程序名}
\hline
\text{\_\_DATE\_\_}     & \text{其包含了由源文件转换为目标代码的日期，该日期是格式为 月/日/年 的字符串文本}
\hline
\text{\_\_TIME\_\_}     & \text{其包含了源文件编译的时间，该时间是 时:分:秒 形式的字符串文本}
\hline
\end{array}

我们来看一个展示上面宏的例子：

```
    #include <iostream>
    using namespace std;

    int main ()
    {
    cout << "Value of __LINE__ : " << __LINE__ << endl;
    cout << "Value of __FILE__ : " << __FILE__ << endl;
    cout << "Value of __DATE__ : " << __DATE__ << endl;
    cout << "Value of __TIME__ : " << __TIME__ << endl;

    return 0;
    }
```
如果我们编译并运行上述代码，将会产生以下结果：

```
    Value of __LINE__ : 6
    Value of __FILE__ : test.cpp
    Value of __DATE__ : Feb 28 2011
    Value of __TIME__ : 18:52:48
```
##### include会替换哪些文件</br>
[源文件](./预处理/test.cpp)
[预处理后的文件](./预处理/test.i)
[stdio.h](./预处理/stdio.h)
