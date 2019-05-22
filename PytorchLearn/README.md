***a file for learning pytorch, and is a addtion to my knowledge***

# 1. [自动求导机制](https://blog.csdn.net/chezhai/article/details/90317222)

# 2. [锁页内存](https://blog.csdn.net/chezhai/article/details/90317699)

# 3. `zero_grad()`

> 这个函数好像很重要，当网络参量进行反馈时，梯度是被积累的而不是被替换掉；但是在每一个batch时毫无疑问并不需要将两个batch的梯度混合起来累积，因此这里就需要每个batch设置一遍`zero_grad`了

> 但是我的理解:

$$
\begin{cases}
\omega\_{11}& = \omega\_{11} - \eta*\frac{\partial e\_{o1}}{\partial\omega\_{11}}\\\\
b\_{1}&= b\_1 - \eta*\frac{\partial e\_{o1}}{\partial b\_1}
\end{cases}
$$

> 根据前面公式的理解,当参数更新完之后，是要将学习到的梯度清零的
