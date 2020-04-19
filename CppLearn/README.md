***this directory is just for learning C++ and its related knowledge.*** </br>

***<p align="center"> CONTENT </p>*** </br>



# C基本知识
###  1.  指针   
1.  [指针初级](https://zhuanlan.zhihu.com/p/93449463)   
2.  [指针高级](https://zhuanlan.zhihu.com/p/94518185)   
3.  [void指针](https://www.cnblogs.com/wuyudong/p/c-void-point.html)    
    <span id="jump1">~~jump there~~</span>
4.  [引用和指针](http://irootlee.com/juicer_pointer_reference/)   
5.  常量指针和指针常量    
6.  函数名即是函数首地址，可以是用&   

> 常量指针(const int\*): 该指针指向的那个变量是不可被修改的；但它本身的指向可以被修改。  
> 指针常量(int \*const 或者 int const\*): 该指针指向的变量是可以被修改的；但它本身的指向是不能被修改的。  

###   2.  浮点数表示方式   
1.  [float存储方式](http://blog.sina.com.cn/s/blog_973657a00102x2do.html) 
2.  [小数表示](https://blog.csdn.net/github_33873969/article/details/78040129)   

###  [3.  VLA](https://www.cnblogs.com/Suzzz/p/4117431.html)   

###  4.  结构体  
1.  [结构体初始化](https://www.cnblogs.com/clover-toeic/p/3737189.html)   
    1.  [结构体变量定义](https://www.runoob.com/cprogramming/c-structures.html)       
###  #/##   
1.  #   
    在使用#define 定义宏中，可使用操作符#在字符串中输出实参，如下:
    ![#](./pictures/4.jpg "#")      
2.  ##    
    操作符## 也可以使用在带参数宏中替换部分内容，该操作符将宏中的两部分连接成一个内容， 比如：（咱不知道如何表示字符串，虽然连接起来是字符串，但是 C 语言中，表示字符串是用“”表示的，但是连接后没有双引号）   
    ![##](./pictures/5.jpg "##")    
3.  [#define目前所知最全的](http://c.biancheng.net/view/446.html)     

4.  奇技淫巧  
    1.  [do...while(false)](https://blog.csdn.net/this_capslock/article/details/41843371)   
5.  内建变量  
    1.  [\_\_func\_\_](https://blog.csdn.net/u011308691/article/details/45015613)     
        1.  在结构体的构造函数中，初始化成员列表使用`__func__`是可行的，其效果跟在函数中是用一样，不过将`__func__`标识符作为函数参数的默认值是不允许的：    
            ```
            void func_fail(std::string func_name = __func__) {} //无法通过编译
            ```
            这是因为在参数声明的时候，`__func`还没有被定义.   


# [ C++基础知识](https://www.runoob.com/cplusplus/cpp-tutorial.html)  
+  [參考這個](https://github.com/huihut/interview#-cc)   
+  [protected](https://www.bookstack.cn/read/open-c-book/zh-cha)   
+  [explicit](http://ttshun.com/2018/05/09/C++%E5%AD%A6%E4%B9%A0%E4%B9%8Bexplicit%E5%85%B3%E9%94%AE%E5%AD%97%E8%AF%A6%E8%A7%A3/)    
+  [:/::的用法](http://www.360doc.com/content/13/0605/11/3373961_290615318.shtml)   

###  1.  python/C++交互(pybind11)待完成    

###  [2.  LeetCode刷题](../LeetcodeLearn)   

###  [3.  C++内存对齐](https://www.cnblogs.com/zhao-zongsheng/p/9099603.html)   
###  [4.  RVO和NRVO](https://www.cnblogs.com/xkfz007/articles/2506022.html)   

###  5.  引用(待规整)   
1.  [指针和引用](#jump1)    
1. [ 弱引用的理解](https://www.cnblogs.com/fengc5/p/5316670.html)    
2. [ 强引用与弱引用的比较](https://blog.csdn.net/Sun960705/article/details/79099533)   
3. [ 左值引用和右值引用](https://www.cnblogs.com/KaiMing-Prince/p/9741393.html)   
4.  [移动语义和完美转发](https://codinfox.github.io/dev/2014/06/03/move-semantic-perfect-forward/)      
```
    int& x = 666;       // Error
    const int& x = 666; // OK
    第一个操作是错误的，它是一个使用int类型的右值来初始化non-const的int&类型的非法操作。第二个操作正确，当然，x是一个常量，你不能改变他。（译者按：注意，常量引用只是规定无法通过该引用改变引用的对象，如果该对象有其他非常量引用或者指针，通过这些改变该对象仍然是合法的）
```
###  6.  [内联函数(不一定非得跟类有关系)](https://www.cnblogs.com/zsq1993/p/5978743.html)    
1.  [内联函数追根究底](https://zhuanlan.zhihu.com/p/50812510)        
###  7.  [使用Valgrind检测C++内存泄露](http://senlinzhan.github.io/page/3/)    
###  8.  [RTTI](https://www.jianshu.com/p/3b4a80adffa7)     
###  9.  智能指针     
1.  [shared_ptr/unique_ptr的deleter初解](https://blog.csdn.net/caroline_wendy/article/details/16938707)       

## 类   
1.  [this指针](https://www.cnblogs.com/Star-Lit/p/8623050.html)    
2.  [重载、覆盖、隐藏](https://www.jianshu.com/p/c5c81ad2e1ce)    
    1.  [重载操作符](https://www.cnblogs.com/ZY-Dream/p/10068993.html)    
3.  [const成员函数](https://blog.csdn.net/u011197534/article/details/78385550)    
4.  [类成员变量初始化顺序](https://blog.csdn.net/shimadear/article/details/82527442)   
5.  [public/private/protected继承](https://www.cnblogs.com/likebeta/archive/2011/10/12/2209044.html)      
6.  [转换构造函数](http://blog.guorongfei.com/2016/03/09/cppx-list-initilization/)       
7.  [类型转换函数](http://c.biancheng.net/cpp/biancheng/view/222.html)   
###  8. 关键字   
1.  [decltype](https://www.cnblogs.com/QG-whz/p/4952980.html)    
2.  [override](https://blog.csdn.net/jolin678/article/details/63695023)    
3.  constexptr
    1. [理解一]( https://www.cnblogs.com/fushi/p/7792257.html)    
    2. [理解二](https://blog.csdn.net/u012453032/article/details/79485251)    
    3. [理解三](https://www.jianshu.com/p/a809eae05ad8)    
4.  [final关键字](https://blog.csdn.net/u012333003/article/details/28696521)   
5.  [=delete和noncopyble](https://blog.csdn.net/tm8426/article/details/73472496)    
6.  [#if defined](https://blog.csdn.net/wangkeyen/article/details/50971469)   
7.  [\_\_declspec](https://blog.csdn.net/zhaoyin214/article/details/83541613)    
8.  [\_\_attribute\_\_](https://www.jianshu.com/p/e2dfccc32c80)     
9.  [\_\_attribute\_\_(visibility)](https://www.jianshu.com/p/e2dfccc32c80)    
10.  [\_\_builtin\_expect — 分支预测优化](https://www.cnblogs.com/LubinLew/p/GCC-__builtin_expect.html)    
11.  [#pragma once](https://blog.csdn.net/cv_jason/article/details/81842710)    
12.  [=default和=deleted](https://www.ibm.com/developerworks/cn/aix/library/1212_lufang_c11new/index.html)    
13.  [typename](http://feihu.me/blog/2014/the-origin-and-usage-of-typename/)    
14.  [使用using代替typedef]( https://blog.csdn.net/big_yellow_duck/article/details/52224068)   
15.  [mutable](https://blog.csdn.net/aaa123524457/article/details/80967330)    
     1. [另一个mutable](https://liam.page/2017/05/25/the-mutable-keyword-in-Cxx/)    
###  9.  boost
1.  [boost::noncopyable](https://fzheng.me/2016/11/20/cpp_noncopyable_class/)     

###  10.  stl    
1.  [仿函数和适配器](https://blog.csdn.net/coolwriter/article/details/81533226)   
2.  [匿名函数](https://www.cnblogs.com/findumars/p/8062299.html；https://blog.csdn.net/alex1997222/article/details/81154026)   
    1.  [再解](https://www.jianshu.com/p/923d11151027)      
3.  std::function
    1. [理解一](https://www.cnblogs.com/diegodu/p/6180350.html)    
    2. [理解二](https://www.cnblogs.com/ph829/p/5162179.html)    
    3. [std::bind](https://www.jianshu.com/p/621fc81a1dc1)   
    4. [可变模板参数](https://www.cnblogs.com/5iedu/p/7787302.html)   
4.  [std::array初步理解](https://blog.csdn.net/thinkerleo1997/article/details/80415059)       


# C++网络编程    
1. OSI七层模型    
    1.1. [解析一](https://blog.csdn.net/qq\_16093323/article/details/79582554)   
    1.2. [解析二](https://blog.csdn.net/taotongning/article/details/81352985)    
2. [计算机网络编程](https://www.cnblogs.com/5iedu/category/937714.html)     
3. [计算机网络原理](https://www.cnblogs.com/5iedu/category/994985.html)    


#  数据库(待完善)

#  C++多线程\_多进程    
1. [初步了解](https://segmentfault.com/u/zhuyuqing)    
2. [死锁简单理解](https://www.cnblogs.com/eilearn/p/9414962.html)   
3. [临界区](https://www.cnblogs.com/xiaochi/p/8029087.html)    
  1.  临界区的解释   
      临界区是指多使用者可能同时共同操作的那部分代码，比如自加自减操作，多个线程处理时就需要对自加自减进行保护，这段代码就是临界区，我的理解，所谓上锁，是锁的那段代码。   
  2.  互斥锁   
      互斥锁底层的实现其实是基于计算机系统中原子操作（即在同一个时间段内，只有一个CPU能够执行某个操作，如访问某个内存位置）来完成的。不同的CPU架构中，会有不同的指令来完成对应的原子操作。如对于x86而言，有一个xchg指令，它的作用就是将一个CPU寄存器的内容和一个指定位置的物理内存的内容互换。当CPU执行次操作的时候，内存控制器会将该内存位置锁定，其他CPU无法在这个时间段内访问该内存，即使是在这个时候其他CPU发出访问该内存的指令，内存控制器也会先将该访问请求在硬件上缓存到请求队列中，等到前面的xchg指令完成后，再执行该命令。一个简单的例子，比如物理内存为1，则表示该锁锁住，如果为0，则表示该锁处于解锁状态。这时候CPU如果想获取该锁，则先在一个寄存器中填如1，然后将寄存器的值和该内存通过xchg指令互换（原子操作），如果互换完后，寄存器的值为0，则表示CPU获取该锁，并防止其他CPU获取该锁了。如果互换完后，寄存器的值为1，则表示该锁已经被其他CPU获取。   
4.  [各种锁](https://www.dazhuanlan.com/2019/10/11/5d9f5a7b0f5bd/)    
5.  [可重入和不可重入函数](https://murphypei.github.io/blog/2019/07/thread-safe-reentrant-function)   
###  1.  [linux多线程服务端编程](./linux多线程服务端编程.md)   
1.  [伪共享](https://www.cnblogs.com/cyfonly/p/5800758.html)   
2.  [虚假唤醒](https://www.zhihu.com/question/271521213)   

#  [Makefile](./cmake/readme.md)    


#  Shell  
1.  [shell中的符号](https://www.jb51.net/article/120595.htm)   
2.  [批量修改文本的内容](https://blog.csdn.net/qq_21101587/article/details/81203767)


#  设计模式    
1.  [设计模式](https://www.cnblogs.com/5iedu/category/825371.html)    
2.  [另一个版本的设计模式](https://www.cnblogs.com/WindSun/p/10223126.html)   


#  异常   
1.  [noexcept](https://www.cnblogs.com/sword03/p/10020344.html)    


#  预处理、编译、汇编、链接    
###  1.  [内存映射]   
1.  [理解一](https://www.bookstack.cn/read/think-os-zh/ch3.md)   
2.  [理解二](https://blog.csdn.net/williamgavin/article/details/83240402)    
3.  [C++新特性：预处理](https://www.cnblogs.com/sjjg/p/10556015.html)     
###  2.  [C语言编程透视](https://www.bookstack.cn/read/open-c-book/zh-chapters-02-chapter2.markdown#toc\_27212\_14734\_2)
###  3.  [预处理](./程序怎么运行的/README.md)    
###  4.  [ELF文件格式](https://luomuxiaoxiao.com/?p=139)   
###  5.  [ELF格式解析](https://paper.seebug.org/papers/Archive/refs/elf/Understanding_ELF.pdf)    
###  6.  [可重定位文件](http://liujunming.top/2016/07/19/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%B3%BB%E7%BB%9F%E4%B8%AD%E7%9A%84%E9%93%BE%E6%8E%A5%EF%BC%88%E4%B8%80%EF%BC%89/)   
###  7.  [fPIC](https://www.cnblogs.com/cswuyg/p/3830703.html)    
###  8.  [通过GDB调试理解GOT/PLT](http://rickgray.me/2015/08/07/use-gdb-to-study-got-and-plt/)    
###  9.  [某些section的作用](https://www.cnblogs.com/arnoldlu/p/7136701.html)  
###  10.   [动态库](./Linux下的动态连接库及其实现机制修订版.rtf)    
###  11.  动态链接   
1.  [理解一](https://www.jianshu.com/p/5deed1bf82b4)   
2.  [理解二](https://github.com/tinyclub/open-c-book/blob/master/zh/chapters/02-chapter4.markdown)     
###  12.  [C++编译器优化](https://www.agner.org/optimize/#manuals)   


#  gdb    
###  1.  [一个程序的整体流程](https://www.nosuchfield.com/2018/11/23/Program-compilation-linking-loading-and-running/)   
###  2.  [gdb调试基础](https://wiki.ubuntu.org.cn/%E7%94%A8GDB%E8%B0%83%E8%AF%95%E7%A8%8B%E5%BA%8F)   
###  3.  [100个gdb技巧](https://www.kancloud.cn/itfanr/i-100-gdb-tips/81888)   
###  4.  [gprof](https://www.cnblogs.com/feisky/archive/2010/03/09/1681997.html)   
###  5.  [打印函数栈](https://ivanzz1001.github.io/records/post/cplusplus/2018/11/08/cpluscplus-gdbusage_part4)
###  6.  [gdb python调用C/C++](https://meteorix.github.io/2019/04/30/pytorch-coredump/)     


#  汇编   
###  1.  [两种汇编格式](https://www.ibm.com/developerworks/cn/linux/l-assembly/index.html)   
###  2.  [rsp和rbp](https://zhuanlan.zhihu.com/p/27339191)   
###  3.  [寄存器](https://www.jianshu.com/p/57128e477efb)   
###  4.  [寻址方式](https://www.hadoop1024.com/2018/12/16/assembly-language-chapter03/)   


#  优化
###  1.  [simd](https://zhuanlan.zhihu.com/p/55327037)   
###  2.  [open mp](https://blog.csdn.net/ArrowYL/article/details/81094837)  
1.  [open mp英文版](https://bisqwit.iki.fi/story/howto/openmp/)   
2.  [openmp博客版本](http://www.uml.org.cn/c%2B%2B/201810291.asp) 


#  C++11
###  1.  [深入理解C++11](./深入理解C++11/README.md)            
###  2.  [Effective Modern C++(部分翻译)](https://github.com/kelthuzadx/EffectiveModernCppChinese)     
###　3.  [另一个完整版本的Effective Modern C++的翻译](https://blog.csdn.net/zhangyifei216/article/details/72868345)    
###  4.  [Effective Modern C++(英文书)](./)


#  泛型编程和元编程
###  1.  C++ Templates: The Complete Guide (2nd Edition)   
###  2.  C++ Template Metaprogramming: Concepts, Tools, and Techniques from Boost and Beyond    
###  3.  C++ Concurrency in Action: Practical Multithreading   

#  内核      
###  1.  [CPU解释](https://www.cnblogs.com/kimsimple/p/7787018.html)      
###  2.  [CPU执行指令](https://www.cnblogs.com/dream-to-pku/p/11601264.html)   
###  3.  [操作系统的重点](https://www.ahaknow.com/pkucs-operating-system-overview/#jin_cheng_xian_cheng_mo_xing)  
###  4.  [PCB的解释](https://zhuanlan.zhihu.com/p/32341542)  

#  cuda编程
+  [cuda C++ best practices guide](https://s0docs0nvidia0com.icopy.site/cuda/cuda-c-best-practices-guide/index.html#what-is-this-document)   
+  [threadIdx/blockIdx/blockDim/gridDim](https://www.cnblogs.com/rainbow70626/p/6498738.html)    
