___when coding, i find to understand basic computer knowledge vaguelly, so i read this book, 深入理解计算机系统. now i make a note about what i learned.___


<p align="center"> Catalog </p>




<p align="center"> Content </p> </br>

## 第二章 信息的表示和处理

1. 字   

> 每台计算机都有一个字长，致命整数和指针数据的标称大小，因为虚拟地址是以这样的一个字来编码的，所以字长决定的最重要的系统参数就是虚拟地址空间的最大大小。也就是说，对于一个字长为$\omega$位的机器而言，虚拟地址的范围为$0{\sim}{2^{\omega-1}}$，程序最多访问$2^{\omega}$个字节。   

2. C语言中数字数据类型的字节数   

\begin{array}{c|cc}
\text{haha} & 1 & 2
\end{array}

\begin{array}{|c|c|c|}
\text{C声明}    & \text{32位机器} & \text{64位机器} \\
\hline
\end{array}
