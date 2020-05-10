___this file is for learning multiprocessing && multithreading___   

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
6.  [虚假唤醒](https://www.zhihu.com/question/271521213)   
