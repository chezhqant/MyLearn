___this file is for learning c language___    

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
    2.  [特定初始化，就是成员变量加了个"."](https://blog.csdn.net/comwise/article/details/9087279)   

###  #/##   
1.  #   
    在使用#define 定义宏中，可使用操作符#在字符串中输出实参，如下:    
    [#](../pictures/4.jpg "#")    
2.  ##  
    操作符## 也可以使用在带参数宏中替换部分内容，该操作符将宏中的两部分连接成一个内容， 比如：（咱不知道如何表示字符串，虽然连接起来是字符串，但是 C 语言中，表示字符串是用“”表示的，但是连接后没有双引号）   
    [##](../pictures/5.jpg "##")    
3.  [#define目前所知最全的](http://c.biancheng.net/view/446.html)     

5.  内建变量  
    1.  [\_\_func\_\_](https://blog.csdn.net/u011308691/article/details/45015613)     
        1.  在结构体的构造函数中，初始化成员列表使用`__func__`是可行的，其效果跟在函数中是用一样，不过将`__func__`标识符作为函数参数的默认值是不允许的：    
            ```
            void func_fail(std::string func_name = __func__) {} //无法通过编译
            ```
            这是因为在参数声明的时候，`__func`还没有被定义.   
    2.  [__VA_ARGS__， \_\_FILE\_\_， \_\_FUNCTION\_\_](https://blog.csdn.net/yiya1989/article/details/7849588)   
    3.  [\_\_COUNTER\_\_](https://zhuanlan.zhihu.com/p/64479211)    

###  奇技淫巧  
    1.  [do...while(false)](https://blog.csdn.net/this_capslock/article/details/41843371)   

