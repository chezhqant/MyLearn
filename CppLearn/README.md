***this directory is just for learning C++ and its related knowledge.*** </br>

***<p align="center"> CONTENT </p>*** </br>

# C基本知识
## [二维数组指针](https://blog.csdn.net/nice__xixi/article/details/82081595) </br>
## [float存储方式](http://blog.sina.com.cn/s/blog_973657a00102x2do.html) <br>
## [小数表示](https://blog.csdn.net/github_33873969/article/details/78040129) <br>


# [C++基础知识](https://www.runoob.com/cplusplus/cpp-tutorial.html) </br>
## [參考這個](https://github.com/huihut/interview#-cc) </br>
## C++/C和Python相互调用</br>
1.1.1 [资料一](https://cloud.tencent.com/developer/article/1174629)</br>
1.1.2 [LeetCode刷题](../LeetcodeLearn)</br>

## [C++内存对齐](https://www.cnblogs.com/zhao-zongsheng/p/9099603.html)</br>
## [RVO和NRVO](https://www.cnblogs.com/xkfz007/articles/2506022.html) </br>
## 常量指针和指针常量
> 常量指针(const int\*): 该指针指向的那个变量是不可被修改的；但它本身的指向可以被修改。</br>
> 指针常量(int \*const 或者 int const\*): 该指针指向的变量是可以被修改的；但它本身的指向是不能被修改的。</br>

## [弱引用的理解](https://www.cnblogs.com/fengc5/p/5316670.html)</br>
## [强引用与弱引用的比较](https://blog.csdn.net/Sun960705/article/details/79099533)</br>
## [左值引用和右值引用](https://www.cnblogs.com/KaiMing-Prince/p/9741393.html) </br>
```
int& x = 666;       // Error
const int& x = 666; // OK
第一个操作是错误的，它是一个使用int类型的右值来初始化non-const的int&类型的非法操作。第二个操作正确，当然，x是一个常量，你不能改变他。（译者按：注意，常量引用只是规定无法通过该引用改变引用的对象，如果该对象有其他非常量引用或者指针，通过这些改变该对象仍然是合法的）
```

## 类</br>
### [this指针](https://www.cnblogs.com/Star-Lit/p/8623050.html)</br>
### [重载、覆盖、隐藏](https://www.cnblogs.com/ZY-Dream/p/10068993.html) </br>
## 关键字 </br>
### [override](https://blog.csdn.net/jolin678/article/details/63695023) </br>
### constexptr
#### [理解一]( https://www.cnblogs.com/fushi/p/7792257.html)</br>
#### [理解二](https://blog.csdn.net/u012453032/article/details/79485251)</br>
#### [理解三](https://www.jianshu.com/p/a809eae05ad8)</br>
#### [final关键字](https://blog.csdn.net/u012333003/article/details/28696521) </br>



## stl<br>
### [仿函数和适配器](https://blog.csdn.net/coolwriter/article/details/81533226)</br>
### [匿名函数](https://www.cnblogs.com/findumars/p/8062299.html；https://blog.csdn.net/alex1997222/article/details/81154026)</br>
### std::function
#### [理解一](https://www.cnblogs.com/diegodu/p/6180350.html) </br>
#### [理解二](https://www.cnblogs.com/ph829/p/5162179.html)</br>
#### [std::bind](https://www.jianshu.com/p/621fc81a1dc1)</br>
### [可变模板参数](https://www.cnblogs.com/5iedu/p/7787302.html)</br>


# C++网络编程</br>
1. OSI七层模型</br>
    1.1. [解析一](https://blog.csdn.net/qq\_16093323/article/details/79582554)</br>
    1.2. [解析二](https://blog.csdn.net/taotongning/article/details/81352985)</br>


# 数据库</br>


# C++多线程\_多进程</br>
## [初步了解](https://segmentfault.com/u/zhuyuqing)</br>
## [死锁简单理解](https://www.cnblogs.com/eilearn/p/9414962.html)</br>


# Makefile</br>


# Shell </br>
1. [shell中的符号](https://www.jb51.net/article/120595.htm)</br>


# 设计模式 </br>
1. [观察者模式](https://www.jianshu.com/p/4b0aee15cdb8)</br>
2. [代理模式](https://blog.csdn.net/a369189453/article/details/81275740)</br>


# 异常</br>
## [noexcept](https://www.cnblogs.com/sword03/p/10020344.html)</br>


# 预处理、编译、汇编、链接</br>
## [内存映射]   
### [理解一](https://www.bookstack.cn/read/think-os-zh/ch3.md)   
### [理解二](https://blog.csdn.net/williamgavin/article/details/83240402)    
## [C语言编程透视](https://www.bookstack.cn/read/open-c-book/zh-chapters-02-chapter2.markdown#toc\_27212\_14734\_2)
## [预处理](./程序怎么运行的/README.md)</br>


# gdb<br>
## [100个gdb技巧](https://www.kancloud.cn/itfanr/i-100-gdb-tips/81888)</br>


# 汇编   
## [两种汇编格式](https://www.ibm.com/developerworks/cn/linux/l-assembly/index.html)   
## [rsp和rbp](https://zhuanlan.zhihu.com/p/27339191)   
## [寄存器](https://www.jianshu.com/p/57128e477efb)   
## [寻址方式](https://www.hadoop1024.com/2018/12/16/assembly-language-chapter03/)   
