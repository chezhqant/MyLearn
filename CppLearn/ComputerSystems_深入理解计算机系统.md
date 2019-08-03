___when coding, i find to understand basic computer knowledge vaguelly, so i read this book, 深入理解计算机系统. now i make a note about what i learned.___


<p align="center"> Catalog </p>




<p align="center"> Content </p> </br>

## 第二章 信息的表示和处理


1. 字   
> 每台计算机都有一个字长，致命整数和指针数据的标称大小，因为虚拟地址是以这样的一个字来编码的，所以字长决定的最重要的系统参数就是虚拟地址空间的最大大小。也就是说，对于一个字长为$\omega$位的机器而言，虚拟地址的范围为$0{\sim}{2^{\omega-1}}$，程序最多访问$2^{\omega}$个字节。   

2. C语言中数字数据类型的字节数   
\begin{array}{|c|c|c|}
\hline
\text{C声明}            & \text{32位机器} & \text{64位机器} \\\\
\hline
\text{char}             & 1               & 2               \\\\
\hline
\text{short int}        & 2               & 2               \\\\
\hline
\text{int}              & 4               & 4               \\\\ 
\hline
\text{long int}         & 4               & 4               \\\\
\hline
\text{long long int}    & 8               & 8               \\\\
\hline
\text{char$^{\ast}$}    & 4               & 8               \\\\
\hline
\text{float}            & 4               & 4               \\\\
\hline
\text{double}           & 8               & 8               \\\\
\hline
\end{array}

3. swap函数
> 对于任一个维向量$\vec{a}$, 有$\vec{a} \cdot \vec{a}=0$。应用这一属性，使用这一性质完成swap函数。
```
void InplaceSwap(int *x, int *y)
{
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}
```
4. 逻辑运算和位级运算的区别   
> 逻辑运算符&&和||与他们对应的位级运算&和|之间第二个重要的区别是，如果对第一个参数求职就能确定表达式的结果，那么逻辑运算符就不会对第二个参数求值。  
5. 计算机支持两种形式的右移：逻辑右移和算术右移。
> 逻辑右移在左端补k个0，得到的结果是$[0, \cdots, 0, x\_{n-1}, x\_{n-1}, \cdots, x\_{k}]$。算术右移是在左端补k个最高有效位的值，得到的结果是$[x\_{n-1}, \cdots, x\_{n-1}, x\_{n-1}, x\_{n-2}, \cdots, x\_{k}]$。   
\begin{array}{|c|c|}
\hline
\text{操作}             & \text{值} \\\\
\hline
\text{参数x}            & \text{[00110000] [01010000]} \\\\
\hline
\text{x >> 4(逻辑右移)} & \text{[00000110] [00001001]} \\\\
\hline
\text{x << 4(算术右移)} & \text{[00000110] [11111001]} \\\\
\hline
\end{array}
