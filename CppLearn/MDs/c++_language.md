___this file is for learning c++ language___    

# [ C++基础知识](https://www.runoob.com/cplusplus/cpp-tutorial.html)  
+  [參考這個](https://github.com/huihut/interview#-cc)   
+  [protected](https://www.bookstack.cn/read/open-c-book/zh-cha)   
   +  [protected成员](https://blog.csdn.net/feiyinzilgd/article/details/6226348)   
+  [explicit](http://ttshun.com/2018/05/09/C++%E5%AD%A6%E4%B9%A0%E4%B9%8Bexplicit%E5%85%B3%E9%94%AE%E5%AD%97%E8%AF%A6%E8%A7%A3/)    
+  private  
   +  [父类中的私有成员可以通过地址访问吗？](https://blog.csdn.net/shanghx_123/article/details/89758003?utm_medium=distribute.pc_relevant.none-task-blog-baidujs-7)   
   +  [C++ 只在堆上或者只在栈上创建对象](https://segmentfault.com/a/1190000009023942)    
   +  [详解C++中如何将构造函数或析构函数的访问权限定为private](https://www.ctolib.com/topics-55958.html)   
+  [:/::的用法](http://www.360doc.com/content/13/0605/11/3373961_290615318.shtml)   
+  [cv-qualified and cv-unqualified](https://blog.csdn.net/asongnic/article/details/4571418)      
+  [聚合类和POD类型](../books/聚合类和POD类型.xmind)    

###  1.  python/C++交互(pybind11)待完成    
1.  [pybind11中文翻译，翻译的不好的](https://s0pybind110readthedocs0io.icopy.site/en/master/compiling.html#building-manually)   
2.  [Visual Studiopython/C++调试](https://docs.microsoft.com/zh-cn/visualstudio/python/debugging-mixed-mode-c-cpp-python-in-visual-studio?view=vs-2019)   

###  [2.  LeetCode刷题](../../LeetcodeLearn)    

###  [3.  C++内存对齐](https://www.cnblogs.com/zhao-zongsheng/p/9099603.html)   
1.  [C++对象内存布局](https://blog.twofei.com/496/)   
2.  [再谈C++对象内存布局](https://www.cnblogs.com/findumars/p/5353535.html)   
3.  [虚拟继承的内存布局，针对这个链接，其中内容可能有错误，可能需要添加：菱形继承的D的内存布局中的B和C的内存布局，可能要加上D::foo()函数](https://zhougy0717.github.io/2018/03/06/C++%E8%8F%B1%E5%BD%A2%E7%BB%A7%E6%89%BF/)      
###  [4.  RVO和NRVO](https://www.cnblogs.com/xkfz007/articles/2506022.html)   

###  5.  引用(待规整)   

1.  [指针和引用](#jump1)    
2. [ 弱引用的理解](https://www.cnblogs.com/fengc5/p/5316670.html)    
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
1.  [再解](https://phenix3443.github.io/notebook/software-engineering/debug/valgrind-practices.html)    
2.  [三解](http://sunny90.com/a/server/2014/0905/108.html)      
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
    1.  [再解](http://c.bianceng.net/cpp/biancheng/view/2984.html)     
    2.  [基类与派生类的纠缠](http://c.biancheng.net/view/2284.html)     
    3.  [基类与派生类的纠缠补充](https://blog.twofei.com/496/#comment-577)      
6.  [转换构造函数](http://blog.guorongfei.com/2016/03/09/cppx-list-initilization/)       
7.  [类型转换函数](http://c.biancheng.net/cpp/biancheng/view/222.html)   
8.  [嵌套类和外围类](https://blog.csdn.net/u013476464/article/details/42738789)   
9.  [不要显式调用析构函数](http://www.cppblog.com/lf426/archive/2008/04/12/46909.html)    
    1.  [私有析构函数](https://www.cnblogs.com/wkfvawl/p/10620639.html)   
10.  [c++ 什么时候会生成默认构造函数](https://www.jianshu.com/p/c6e6baec5c4f)      
11.  [Why does default initialization of static data member not occur?](https://stackoverflow.com/questions/24682349/initialization-of-static-data-member)      
12.  [拷贝构造函数,为什么必须是当前类的引用？为什么是const引用？](./c++_files/拷贝构造函数.md)       
    [补充解释](https://en.cppreference.com/w/cpp/language/static)    
13.  [继承构造函数](https://blog.csdn.net/SwordArcher/article/details/88717442)     

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
1.  [using在继承构造函数中的用法](https://blog.csdn.net/SwordArcher/article/details/88717442)    
15.  [mutable](https://blog.csdn.net/aaa123524457/article/details/80967330)    
     1. [另一个mutable](https://liam.page/2017/05/25/the-mutable-keyword-in-Cxx/)    
###  9.  boost
1.  [boost::noncopyable](https://fzheng.me/2016/11/20/cpp_noncopyable_class/)     

###  10.  stl    
1.  [仿函数和适配器](https://blog.csdn.net/coolwriter/article/details/81533226)   
2.  [匿名函数](https://www.cnblogs.com/findumars/p/8062299.html；https://blog.csdn.net/alex1997222/article/details/81154026)   
3.  [std::accumulate()](https://www.cnblogs.com/heyonggang/p/3241878.html)    
    1.  [再解](https://www.jianshu.com/p/923d11151027)      
3.  std::function
    1. [理解一](https://www.cnblogs.com/diegodu/p/6180350.html)    
    2. [理解二](https://www.cnblogs.com/ph829/p/5162179.html)    
    3. [std::bind](https://www.jianshu.com/p/621fc81a1dc1)   
    4. [可变模板参数](https://www.cnblogs.com/5iedu/p/7787302.html)   
4.  [std::array初步理解](https://blog.csdn.net/thinkerleo1997/article/details/80415059)       
5.  [常用算法总结](https://www.cnblogs.com/linuxAndMcu/p/10264339.html)   

###  11.  C++11
1.  [深入理解C++11](./深入理解C++11/README.md)            
2.  [Effective Modern C++(部分翻译)](https://github.com/kelthuzadx/EffectiveModernCppChinese)     
3.  [另一个完整版本的Effective Modern C++的翻译](https://blog.csdn.net/zhangyifei216/article/details/72868345)    
4.  [Effective Modern C++(英文书)](./)
    1.  [my summary](./effective_modern_c++_summary.md)      

###  12.  [带你玩转VS2010](https://wiki.jikexueyuan.com/project/visual-studio/)   
1.  [VS2010对c++的支持程度](https://blog.csdn.net/shenwanjiang111/article/details/54949276)     

###  13. [C++/C宏观](../c++_files/c_cpp_macro.md)           
