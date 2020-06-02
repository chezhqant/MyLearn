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
2.  快速范围判断  
    ```
    // 经常要批量判断某些值在不在范围内，如果int检测是[0, N)的话： 
    if (x >= 0 && x < N) ... // 原来是这样的
    if (((unsigned int)x) < N) ... //现在是这样的

    // 如果int检测的范围是[minx, maxx]的话：    
    if (x >= minx && x <= maxx) ... // 原来是这样的
    if (((x - minx) | (maxx - x)) >=0 ) ... // 现在是这样的
    上述中，第一个(x - minx)如果x < minx的话，得到的结果，是<0，高位是1，第二个判断同理，如果超过范围，高位也是1，两个条件进行比特或运算以后，只有两个高位都为0，最终才为真，同理：   
    if (((x - minx) | (maxx - x) | (y - miny) | (maxy - y)) >= 0) ... // 这样本来需要对[x, y]进行四次判断，这样完全可以并为一次判断，减少分支
    ```
3.  对于循环展开：    
    ```
    #define CPU_LOOP_UNROLL_4X(actionx1, actionx2, actionx4, width) do { \
      unsigned long __width = (unsigned long)(width); \
      unsigned long __increment = __width >> 2; \
      for (; __increment > 0; --__increment) { actionx4; } \
      if (__width & 2) { actionx2; } \
      if (__width & 1) { actionx1; } \
    } while(0);
    ```
4.  快速除以255   
    整数快速除以255很常见，例如图像绘制、合成、音频处理、混音计算：   
    ```
    #define div_255_fast(x) (((x) + (((x) + 257) >> 8)) >> 8)
    ```
    当x属于[0, 65536]范围内，该方法的误差为0.   
    进一步的可以是用SIMD：    
    ```
    // (x + ((x + 257) >> 8)) >> 8
    static inline __m128i _mm_fast_div_255_epu16(__m128i x) {
      return __m_srli_epi16(_mm_adds_epu16(x,
             __mm_srli_epi16(_mm_adds_epu16(x, _mm_set1_epi16(0x0101)), 8)), 8);
    }
    ```
    这样可以同时对8，对16bit的整数进行/255运算，照葫芦画瓢，还可以改出一个/65536，或者/32767版本。  
    对于任意大于0的整数，下面的方法x86一般，x64位还行：   
    ```
    static inline int32_t fast_div_255_any (int32_t n) {
      int32_t M = -2139062143;
      int64_t t = (int64_t)M * (int64_t)n;
      int32_t q = ((t >> 32) + n) >> 7;
      
      return q + (n >> 31);
    }
    ```
    因此如果整数范围属于[0,65536]推荐是用第一个版本，而任意大于0 的整数，推荐是用第二个版本。   

5.  常数范围裁剪    
    ```
    // 有时候你计算一个整数数值需要控制在0-255范围内，如果小于0，那么等于0， 如果大于255，那么等于255，做一个裁剪工作，可以是用如下位运算：   
    static inline int32_t clamp_to_o(int32_t x) {
      reutnr ((-x) >> 31) & x;
    }
    static inline int32_t clamp_to_255(int32_t x) {
      return (((255 - x) >> 31) | x) & 255;
    }
    // 这种方法可以裁剪任何2^n-1的常数，比如裁剪65535：   
    static inline int32_t clamp_to_65535 (int32_t x) {
      return (((655535 - x) >> 31) | x) & 65535;
    }
    ```
6.  [C语言一些常见的错误](http://www.gowrikumar.com/c/index.php)    
7.  [bit位构成的一些trick](http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel)    
