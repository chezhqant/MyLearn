___this file is for learning to going depp!___    


##  预处理、编译、汇编、链接    
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
###  12.  [静态链接、动态链接重定位表](https://www.cnblogs.com/gradyblog/p/8964073.html)      
1.  [理解一](https://www.jianshu.com/p/5deed1bf82b4)   
2.  [理解二](https://github.com/tinyclub/open-c-book/blob/master/zh/chapters/02-chapter4.markdown)     
###  12.  [C++编译器优化](https://www.agner.org/optimize/#manuals)   
1.  [vs编译器选项](https://www.cnblogs.com/csdreamer/articles/3094029.html)   
###  13.  [linux命令大全（写在这里是为了readelf/objdump/ldd/ar）](https://man.linuxde.net/)     
###  14.  [rpath以及$ORIGIN](https://www.jianshu.com/p/505a32ccdc91)    
1.  [rpath/runpath有可能这博客是错的](https://blog.csdn.net/dbzhang800/article/details/6918413)   
    RUNPATH 指定的路径可以被 LD_LIBRARY_PATH 覆盖， 但是 RPATH 指定的路径是优先级最高的。在 RUNPATH 字段存在的情况下， RPATH 字段会被忽略。
    貌似 RPATH 的 历史 比 RUNPATH 要久远，所以支持 RPATH 的工具比较多。 但是 RUNPATH 比 RPATH 灵活，因为可以被环境变量覆盖。
    GNU linker 在只指定 --rpath 选项的情况下默认只设置 RPATH 字段，要设置 RUNPATH 字段的话，还需要指定 --enable-new-dtag选项。   
2.  [再解](http://blog.airobot.org/2017/05/04/linux%E5%8A%A8%E6%80%81%E9%93%BE%E6%8E%A5%E5%BA%93%E6%90%9C%E7%B4%A2%E7%9B%AE%E5%BD%95%E8%A7%84%E5%88%99/)    
3.  公司CMakeLists.txt看到的$ORIGIN   
    这是一个大坑，在可执行文件和动态库中$ORIGIN指的是本身的绝对路径，但是在CMakeLists.txt这个变量没有意义。  
    eg: libhello.so是一个动态库，它本身在./Release中，它所依赖的其他文件是在../Dependency中。直接写进去就是$ORIGIN:   
    set_target_properties(hello PROPERTIES INSTALL_RPATH "$ORIGIN/Dependency")   
    对于上面一个命令，在CMake中将RPATH设置为“$ORIGIN/Dependency”，但是在elf文件中，会解析它的绝对路径，我是这么猜的。   
###  15.  C++中头文件、源文件之间的区别与联系        
1.  [理解一](:https://my.oschina.net/fergus/blog/123484)    
2.  [理解二](https://cloud.tencent.com/developer/article/1177251)     

###  16. ...    
1.  [.bss段不占磁盘空间](https://www.maixj.net/ict/bss-23766)     

##  gdb    
###  1.  [一个程序的整体流程](https://www.nosuchfield.com/2018/11/23/Program-compilation-linking-loading-and-running/)   
###  2.  [gdb调试基础](https://wiki.ubuntu.org.cn/%E7%94%A8GDB%E8%B0%83%E8%AF%95%E7%A8%8B%E5%BA%8F)   
###  3.  [100个gdb技巧](https://www.kancloud.cn/itfanr/i-100-gdb-tips/81888)   
###  4.  [gprof](https://www.cnblogs.com/feisky/archive/2010/03/09/1681997.html)   
###  5.  [打印函数栈](https://ivanzz1001.github.io/records/post/cplusplus/2018/11/08/cpluscplus-gdbusage_part4)
###  6.  [gdb python调用C/C++](https://meteorix.github.io/2019/04/30/pytorch-coredump/)     
###  7.  [gdb的一些命令](https://deepzz.com/post/gdb-debug.html)        

##  汇编   
###  1.  [两种汇编格式](https://www.ibm.com/developerworks/cn/linux/l-assembly/index.html)   
###  2.  [rsp和rbp](https://zhuanlan.zhihu.com/p/27339191)   
###  3.  [寄存器](https://www.jianshu.com/p/57128e477efb)   
###  4.  [寻址方式](https://www.hadoop1024.com/2018/12/16/assembly-language-chapter03/)   

##  优化
###  1.  [simd](https://zhuanlan.zhihu.com/p/55327037)   
###  2.  [open mp](https://blog.csdn.net/ArrowYL/article/details/81094837)  
1.  [open mp英文版](https://bisqwit.iki.fi/story/howto/openmp/)   
2.  [openmp博客版本](http://www.uml.org.cn/c%2B%2B/201810291.asp) 
3.  [open编程指南csdn版本](https://blog.csdn.net/drzhouweiming/article/details/4093624)   
4.  [每个程序员都应该了解的内存知识](https://www.cnblogs.com/blockcipher/p/3251117.html)    


##  内核      
###  1.  [CPU解释](https://www.cnblogs.com/kimsimple/p/7787018.html)      
###  2.  [CPU执行指令](https://www.cnblogs.com/dream-to-pku/p/11601264.html)   
###  3.  [操作系统的重点](https://www.ahaknow.com/pkucs-operating-system-overview/#jin_cheng_xian_cheng_mo_xing)  
###  4.  [PCB的解释](https://zhuanlan.zhihu.com/p/32341542)  
###  5.  [ComputerSystems_深入理解计算机系统](./MDs/ComputerSystems_深入理解计算机系统.md)   
###  6.  [蜗窝科技](http://www.wowotech.net/)   
###  7.  details   
###  8.  [奔跑吧linux内核](./奔跑吧linux内核.md)    
1.  namespace   
    据说跟docker有关系，先放一放，回头再看。    
2.  [process credentials](http://www.wowotech.net/process_management/19.html)   
3.  [process identification](http://www.wowotech.net/process_management/process_identification.html)  
4.  process id    
    1.  [解释1](http://www.wowotech.net/process_management/pid.html)    
    2.  [解释2](https://www.cnblogs.com/hazir/p/linux_kernel_pid.html)    
    3.  [解释3](https://vvl.me/2018/09/linux-task-relationship/)    
    4.  [container_of](https://lp007819.wordpress.com/2010/09/19/container_of-%E5%AE%8F%E5%88%86%E6%9E%90/)   
    5.  [详细版](https://www.shuzhiduo.com/A/E35pnPrEzv/)   
5.  [TLB](https://blog.csdn.net/hnwyllmm/article/details/77051135)    
    1.  [TLB](https://www.cnblogs.com/bhlsheji/p/5042606.html)        
6.  [__user](https://blog.csdn.net/q345852047/article/details/7710818)    
7. [Linux的公平调度（CFS）原理](https://www.jianshu.com/p/673c9e4817a8)   
  1.  [另一个理解](https://blog.csdn.net/XD_hebuters/article/details/79623130)    
  2.  [再一个理解](https://chasinglulu.github.io/categories/task-management-and-process-scheduling/)    
8.  [这个人的关于进程的可以看](https://www.cnblogs.com/linhaostudy/category/1073650.html)   
9.  [进程控制块的存放和当前进程的确定](https://www.cnblogs.com/ancient/p/3210658.html)    
10.  [虚拟地址空间分布图](https://blog.csdn.net/qq_21842557/article/details/50777199)     
11.  [cache基本原理](https://zhuanlan.zhihu.com/p/102293437?utm_source=wechat_session&utm_medium=social&utm_oi=1139653771880796160)     
12. [VMA](http://abcdxyzk.github.io/blog/2015/09/09/kernel-mm-vm_area/)     
