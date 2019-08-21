***this directory is just for learning C++ and its related knowledge.*** </br>

***<p align="center"> CONTENT </p>*** </br>


<!-- vim-markdown-toc GFM -->

* [C基本知识](#c基本知识)
    * [二维数组指针](#二维数组指针)
    * [float存储方式](#float存储方式)
    * [小数表示](#小数表示)
    * [VLA](#vla)
* [C++基础知识](#c基础知识)
    * [參考這個](#參考這個)
    * [C++/C和Python相互调用](#cc和python相互调用)
    * [C++内存对齐](#c内存对齐)
    * [RVO和NRVO](#rvo和nrvo)
    * [常量指针和指针常量](#常量指针和指针常量)
    * [弱引用的理解](#弱引用的理解)
    * [强引用与弱引用的比较](#强引用与弱引用的比较)
    * [左值引用和右值引用](#左值引用和右值引用)
    * [内联函数(不一定非得跟类有关系)](#内联函数不一定非得跟类有关系)
    * [使用Valgrind检测C++内存泄露](#使用valgrind检测c内存泄露)
    * [类](#类)
        * [this指针](#this指针)
        * [重载、覆盖、隐藏](#重载覆盖隐藏)
        * [const成员函数](#const成员函数)
    * [关键字](#关键字)
        * [decltype](#decltype)
        * [override](#override)
        * [constexptr](#constexptr)
            * [理解一](#理解一)
            * [理解二](#理解二)
            * [理解三](#理解三)
        * [final关键字](#final关键字)
        * [=delete和noncopyble](#delete和noncopyble)
        * [#if defined](#if-defined)
        * [[\_\_declspec](https://blog.csdn.net/zhaoyin214/article/details/83541613)](#__declspechttpsblogcsdnnetzhaoyin214articledetails83541613)
        * [[\_\_attribute\_\_](https://www.jianshu.com/p/e2dfccc32c80)](#__attribute__httpswwwjianshucompe2dfccc32c80)
        * [[\_\_attribute\_\_(visibility)](https://www.jianshu.com/p/e2dfccc32c80)](#__attribute__visibilityhttpswwwjianshucompe2dfccc32c80)
        * [[\_\_builtin\_expect — 分支预测优化](https://www.cnblogs.com/LubinLew/p/GCC-__builtin_expect.html)](#__builtin_expect--分支预测优化httpswwwcnblogscomlubinlewpgcc-__builtin_expecthtml)
        * [#pragma once](#pragma-once)
        * [=default和=deleted](#default和deleted)
        * [typename](#typename)
        * [使用using代替typedef](#使用using代替typedef)
    * [stl](#stl)
        * [仿函数和适配器](#仿函数和适配器)
        * [匿名函数](#匿名函数)
        * [std::function](#stdfunction)
            * [理解一](#理解一-1)
            * [理解二](#理解二-1)
            * [std::bind](#stdbind)
        * [可变模板参数](#可变模板参数)
* [C++网络编程](#c网络编程)
* [数据库](#数据库)
* [C++多线程\_多进程](#c多线程_多进程)
    * [初步了解](#初步了解)
    * [死锁简单理解](#死锁简单理解)
* [Makefile](#makefile)
* [Shell](#shell)
* [设计模式](#设计模式)
* [异常](#异常)
    * [noexcept](#noexcept)
* [预处理、编译、汇编、链接](#预处理编译汇编链接)
    * [[内存映射]](#内存映射)
        * [理解一](#理解一-2)
        * [理解二](#理解二-2)
    * [C语言编程透视](#c语言编程透视)
    * [预处理](#预处理)
    * [ELF文件格式](#elf文件格式)
    * [ELF格式解析](#elf格式解析)
    * [可从定位文件](#可从定位文件)
    * [动态库](#动态库)
    * [[动态链接]](#动态链接)
        * [理解一](#理解一-3)
        * [理解二](#理解二-3)
* [gdb](#gdb)
    * [100个gdb技巧](#100个gdb技巧)
* [汇编](#汇编)
    * [两种汇编格式](#两种汇编格式)
    * [rsp和rbp](#rsp和rbp)
    * [寄存器](#寄存器)
    * [寻址方式](#寻址方式)
* [优化](#优化)
    * [simd](#simd)

<!-- vim-markdown-toc -->

# C基本知识
## [二维数组指针](https://blog.csdn.net/nice__xixi/article/details/82081595)   
## [float存储方式](http://blog.sina.com.cn/s/blog_973657a00102x2do.html)    
## [小数表示](https://blog.csdn.net/github_33873969/article/details/78040129)   
## [VLA](https://www.cnblogs.com/Suzzz/p/4117431.html)   


# [C++基础知识](https://www.runoob.com/cplusplus/cpp-tutorial.html)  
## [參考這個](https://github.com/huihut/interview#-cc)   
## C++/C和Python相互调用  
1.1.1 [资料一](https://cloud.tencent.com/developer/article/1174629)   
1.1.2 [LeetCode刷题](../LeetcodeLearn)   

## [C++内存对齐](https://www.cnblogs.com/zhao-zongsheng/p/9099603.html)   
## [RVO和NRVO](https://www.cnblogs.com/xkfz007/articles/2506022.html)   
## 常量指针和指针常量
> 常量指针(const int\*): 该指针指向的那个变量是不可被修改的；但它本身的指向可以被修改。  
> 指针常量(int \*const 或者 int const\*): 该指针指向的变量是可以被修改的；但它本身的指向是不能被修改的。  

## [弱引用的理解](https://www.cnblogs.com/fengc5/p/5316670.html)    
## [强引用与弱引用的比较](https://blog.csdn.net/Sun960705/article/details/79099533)   
## [左值引用和右值引用](https://www.cnblogs.com/KaiMing-Prince/p/9741393.html)   
```
int& x = 666;       // Error
const int& x = 666; // OK
第一个操作是错误的，它是一个使用int类型的右值来初始化non-const的int&类型的非法操作。第二个操作正确，当然，x是一个常量，你不能改变他。（译者按：注意，常量引用只是规定无法通过该引用改变引用的对象，如果该对象有其他非常量引用或者指针，通过这些改变该对象仍然是合法的）
```
## [内联函数(不一定非得跟类有关系)](https://www.cnblogs.com/zsq1993/p/5978743.html)   
## [使用Valgrind检测C++内存泄露](http://senlinzhan.github.io/page/3/)    

## 类   
### [this指针](https://www.cnblogs.com/Star-Lit/p/8623050.html)    
### [重载、覆盖、隐藏](https://www.cnblogs.com/ZY-Dream/p/10068993.html)    
### [const成员函数](https://blog.csdn.net/u011197534/article/details/78385550)    
## 关键字   
### [decltype](https://www.cnblogs.com/QG-whz/p/4952980.html)    
### [override](https://blog.csdn.net/jolin678/article/details/63695023)    
### constexptr
#### [理解一]( https://www.cnblogs.com/fushi/p/7792257.html)    
#### [理解二](https://blog.csdn.net/u012453032/article/details/79485251)    
#### [理解三](https://www.jianshu.com/p/a809eae05ad8)    
### [final关键字](https://blog.csdn.net/u012333003/article/details/28696521)   
### [=delete和noncopyble](https://blog.csdn.net/tm8426/article/details/73472496)    
### [#if defined](https://blog.csdn.net/wangkeyen/article/details/50971469)   
### [\_\_declspec](https://blog.csdn.net/zhaoyin214/article/details/83541613)    
### [\_\_attribute\_\_](https://www.jianshu.com/p/e2dfccc32c80)     
### [\_\_attribute\_\_(visibility)](https://www.jianshu.com/p/e2dfccc32c80)    
### [\_\_builtin\_expect — 分支预测优化](https://www.cnblogs.com/LubinLew/p/GCC-__builtin_expect.html)    
### [#pragma once](https://blog.csdn.net/cv_jason/article/details/81842710)    
### [=default和=deleted](https://www.ibm.com/developerworks/cn/aix/library/1212_lufang_c11new/index.html)    
### [typename](http://feihu.me/blog/2014/the-origin-and-usage-of-typename/)    
### [使用using代替typedef]( https://blog.csdn.net/big_yellow_duck/article/details/52224068)   



## stl    
### [仿函数和适配器](https://blog.csdn.net/coolwriter/article/details/81533226)   
### [匿名函数](https://www.cnblogs.com/findumars/p/8062299.html；https://blog.csdn.net/alex1997222/article/details/81154026)   
### std::function
#### [理解一](https://www.cnblogs.com/diegodu/p/6180350.html)    
#### [理解二](https://www.cnblogs.com/ph829/p/5162179.html)    
#### [std::bind](https://www.jianshu.com/p/621fc81a1dc1)   
### [可变模板参数](https://www.cnblogs.com/5iedu/p/7787302.html)   


# C++网络编程    
1. OSI七层模型    
    1.1. [解析一](https://blog.csdn.net/qq\_16093323/article/details/79582554)   
    1.2. [解析二](https://blog.csdn.net/taotongning/article/details/81352985)    
2. [计算机网络编程](https://www.cnblogs.com/5iedu/category/937714.html)     
3. [计算机网络原理](https://www.cnblogs.com/5iedu/category/994985.html)    


# 数据库    


# C++多线程\_多进程    
## [初步了解](https://segmentfault.com/u/zhuyuqing)    
## [死锁简单理解](https://www.cnblogs.com/eilearn/p/9414962.html)   


# Makefile    


# Shell   
1. [shell中的符号](https://www.jb51.net/article/120595.htm)   


# 设计模式    
1. [观察者模式](https://www.jianshu.com/p/4b0aee15cdb8)   
2. [代理模式](https://blog.csdn.net/a369189453/article/details/81275740)    
3. [设计模式](https://www.cnblogs.com/5iedu/category/825371.html)    


# 异常   
## [noexcept](https://www.cnblogs.com/sword03/p/10020344.html)    


# 预处理、编译、汇编、链接    
## [内存映射]   
### [理解一](https://www.bookstack.cn/read/think-os-zh/ch3.md)   
### [理解二](https://blog.csdn.net/williamgavin/article/details/83240402)    
## [C语言编程透视](https://www.bookstack.cn/read/open-c-book/zh-chapters-02-chapter2.markdown#toc\_27212\_14734\_2)
## [预处理](./程序怎么运行的/README.md)    
## [ELF文件格式](https://luomuxiaoxiao.com/?p=139)   
## [ELF格式解析](https://paper.seebug.org/papers/Archive/refs/elf/Understanding_ELF.pdf)    
## [可从定位文件](http://liujunming.top/2016/07/19/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%B3%BB%E7%BB%9F%E4%B8%AD%E7%9A%84%E9%93%BE%E6%8E%A5%EF%BC%88%E4%B8%80%EF%BC%89/)   
## [动态库](./Linux下的动态连接库及其实现机制修订版.rtf)    
## [动态链接]
### [理解一](https://www.jianshu.com/p/5deed1bf82b4)   
### [理解二](https://github.com/tinyclub/open-c-book/blob/master/zh/chapters/02-chapter4.markdown)     


# gdb    
## [100个gdb技巧](https://www.kancloud.cn/itfanr/i-100-gdb-tips/81888)   


# 汇编   
## [两种汇编格式](https://www.ibm.com/developerworks/cn/linux/l-assembly/index.html)   
## [rsp和rbp](https://zhuanlan.zhihu.com/p/27339191)   
## [寄存器](https://www.jianshu.com/p/57128e477efb)   
## [寻址方式](https://www.hadoop1024.com/2018/12/16/assembly-language-chapter03/)   


# 优化
## [simd](https://zhuanlan.zhihu.com/p/55327037)   
