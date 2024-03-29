## 第五章 [bx] 和 loop 指令     
1.  [0] 表示内存单元，它的偏移地址是0. `mov ax, [0]` 将一个内存单元的内容送入 `ax`，这个内存单元的长度为 __2字节__，存放一个字，偏移地址为0，段地址在 `ds` 中。   
2. `mov al, [0]` 将一个内存单元的内容送入 `al`，这个内存单元的长度为 __1字节__，存放一个字节，偏移地址为0，段地址在 `ds`中。    
3.  我们要完整的描述一个内存单元，需要两种信息：      
    + 内存单元的地址      
    + 内存单元的长度      
    我们用 `[0]` 表示一个内存单元时，0表示单元的偏移地址，段地址默认在 `ds` 中，单元长度可以有具体指令中的其他操作对象（比如说寄存器）指出。      
4.  `[bx]` 也同样表示一个内存单元，它的偏移地址在 `bx`中，比如下面指令：   
    + `mov ax, [bx]` 将一个内存单元的内容送入 `ax`，这个内存单元的长度为2字节，存放一个字，偏移地址在 `bx` 中，段地址在 `ds`中。   
    + `mov al, [bx]` 将一个内存单元的内容送入 `al`，这个内存单元的长度为1字节，存放一个字节，偏移地址在 `bx` 中，段地址在 `ds`中。   
5.  在这里，定义描述性符号“()”，`()` 表示一个寄存器或者一个内存单元中的内容。比如 `(ax)` 表示 `ax` 中的内容，`(al)` 表示 `al` 中的内容。`(20000H)` 表示内存 `20000H` 单元的内容       
6.  “()”中的元素可以有三种类型：      
    + 寄存器名      
    + 段寄存器名      
    + 内存单元的物理地址      
    比如： (ax), (ds), (cs), (20000H), ((ds)*16+(bx))等是正确的用法。(2000H), (2000:0), ((ds):1000H)等是不正确的用法。    
7.  本书约定符号idata表示常量     
8.  看一下以下功能：      
    `mov ax, [bx]` 功能：`bx` 中存放的数据作为一个偏移地址EA，段地址SA默认在 `ds` 中，将SA:EA处的数据送入 `ax` 中，即：(ax)=((ds)*16+(bx))。       
    `mov [bx], ax` 功能：`bx` 中存放的数据作为一个偏移地址EA，段地址SA默认放在 `ds` 中，将 `ax` 中的数据送入内存SA:EA处，即：((ds)*16+(bx))=(ax)       
9.  loop指令的格式：      
    `loop 标号`，CPU执行 loop 指令的时候要进行两步操作：    
    + (cx)=(cx)-1   
    + 判断 cx 中的值，不为零转至标号处执行程序，如果为零则向下执行。      
                                                                  `cx` 中的值影响着loop指令的执行结果。   
10.  `loop s`     
     CPU 执行 `loop s` 的时候，要进行两步操作：   
     + (cx)=(cx)-1      
     + 判断 `cx` 中的值，不为0则转至标号 `s` 所标识的地址处执行（这里的指令时 `add ax, ax`），如果为零则执行吓一跳指令。   
     `cx` 和 `loop` 指令相配合实现循环功能的三个要点：    
     + 在 `cx` 中存放循环次数。   
     + `loop` 指令中的标号所标识地址要在前面。    
     + 要循环执行的程序段，要写在标号和loop指令的中间。   
     用 `cx` 和 `loop` 指令相配合实现循环功能的程序框架如下：    
     ```
     mov cx, 循环次数
     s:
         循环执行的程序段
         loop s
     ```
11.  在访问内存单元的指令中显式地给出内存单元的段地址所在的段寄存器，比如：      
     + `mov ax, ds:[bx]`    
     将一个内存单元的内容送入 `ax`，这个内存单元的长度为2个字节，偏移地址在 `bx` 中，段地址在 `ds` 中。      
     其他 `cs`, `ss`, `es`, `ss`是一样的操作。这些出现在访问内存单元的指令中，用于显式地指明内存单元的段地址的"ds:", "cs:",  "ss:", 或者"es:"，在汇编语言中称为 __段前缀__。      
