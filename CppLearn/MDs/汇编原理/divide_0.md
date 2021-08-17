###除0溢出###      
1.  当CPU执行 `div bh` 后，发生了除法溢出错误，产生0号中断信息，引发中断过程。CPU执行我们编写的0号中断处理程序。在屏幕中间显示提示信息"overflow!"，返回到操作系统中。     
2.  编程：当发生除法溢出时，在屏幕中间显示"overflow!"，返回DOS。      
3.  分析：      
    1.  当发生除法溢出的时候，产生0号中断信息，从而引发中断过程。   
        此时，CPU将进行以下工作：   
        + 取得中断类型码0   
        + 标志寄存器入栈，TF、IF设置为0   
        + CS、IP入栈      
        + (IP)=(0*4)，(CS)=(0*4+2)      
    2.  可见当中断0发生时，CPU将转去执行中断处理程序。只要按照如下步骤编写中断处理程序，当中断0发生时，即可显示”overflow!“。    
        + 相关处理      
        + 向显示缓冲区送字符串”overfloat“   
        + 返回DOS     
        我们称这段程序为 `do0`。    
    3.  现在的问题是：`do0` 应存放在内存中，因为除法溢出随时可能发生，CPU随时都可能将CS:IP指向 `do0` 的入口，执行程序。     
    __那么 `do0` 应该放在哪里__?        
    由于我们是在操作系统之上是用计算机，所有的硬件资源都在操作系统的管理上，所以我们要想知道一块内存区存放 `do0`，应该向操作系统申请。    
    我们需要找到一块别的程序不会用到的内存区，将 `do0` 传送到其中即可。    
    前面讲到，内存 `0000:0000-0000:03E8`，大小约为1KB的空间是系统存放中断处理程序入口地址的中断向量表。8086支持256个中断。但是，系统中要处理的中断时间远远没有达到256个。所以在中断向量表中，有许多单元是空的。      
    中断向量表是PC系统中最重要的内存去，只用来存放中断处理程序的入口地址，DOS系统和其他应用程序都不会随便是用这段空间。我们可以利用中断向量表中的空间单元来存放我们的程序。一般情况下，从 `0000:0200-0000:0300` 的256个字节的空间所对应的中断向量表项都是空的，操作系统和其他程序都不占用。        
    根据以前的编程经验，我们可以估算出，`do0` 的长度不可能超过256个字节。      
    结论：我们可以将 `do0` 传送到内存 `0000:0200`处。     
    4.  我们将中断处理程序 `do0` 放到 `0000:0200` 后，若要使得除法溢出发生的时候，CPU转去执行 `do0`，则必须将 `do0` 的入口地址，即 `0000:0200` 登记在中断向量表的对应表项中。因为除法溢出对应的中断类型码为0，它的中断处理程序的入口地址应该从 `0*4` 地址单元开始存放，段地址存放在 `0*4+2` 字单元汇总，偏移地址存放在 `0*4` 字单元中，也就是说要将 `do0` 的段地址0存放在 `0000:0002` 子弹预案中，将偏移地址200H存放在 `0000:0000` 字单元中。        
    总结：    
        + 编写可以显示 ”overflow!“ 的中断处理程序： `do0`   
        + 将 `do0` 送入内存 `0000:0200` 处      
        + 将 `do0` 的入口地址 `0000:0200` 存储在中断向量表0号表项中。      
    程序框架：      
    ```
    assume cs:code
    code segment
    start: do0 安装程序
           设置中断向量表
           mov ax, 4c00H
           int 21h
      do0: 显示字符串"overflow!"
           mov ax, 4c00H
           int 21H
    code ends
    end start
    ```
    程序执行以上代码的时候 `do0` 代码是不执行的，它只是作为 `do0` 安装程序所要传送的数据。上述程序执行时，受限执行 `do0` 安装程序，将 `do0` 的代码拷贝到内存 `0:200` 处，然后设置中断向量表，将 `do0` 的入口地址，即编译地址200和段地址0，保存在0号表项中。这两步完成后程序就返回了。程序的目的就是再内存 `0:200` 处安装 `do0` 的代码，将0号中断处理程序的入口地址设置为 `0:200`。`do0` 的代码虽然在程序中，却不在程序执行的时候执行。它只是在除法溢出发生的时候才得以执行的中断处理程序。    从CPU的角度来看一下，什么是中断处理程序？   
    + 上述程序执行时，被加载到内存中，此时 `do0` 的代码在上述程序所在的内存空间中，它只是存放在程序的代码段中的一段要被送到其他单元中的数据，我们不能说它是0号中断的中断处理程序       
    + 上述程序中安装 `do0` 的代码执行完后，`do0` 的代码被从上述程序的代码段中拷贝到 `0:200` 处，此时，我们也不能说它是0号中断的中断处理程序，他只不是存放在 `0:200` 处的一些数据。     
    + 上述程序中设置中断向量表的代码执行万后，在0号表项中填入了 `do0` 的入口地址 `0:200`，此时 `0:200` 处的信息，即 `do0` 的代码，就变成了0号中断的中断处理程序。因为当除法溢出（即0号中断）发生时，CPU将执行 `0:200` 处的代码。      
    回忆：      
    + 我们如何让一个内存单元称为栈顶？将它的地址放入SS、SP中    
    + 我们如何让一个内存单元的信息被CPU当作执行来执行？将它的地址放入CS、IP中      
    那么，我们如何让一段程序成为N号中断处理程序？将它的入口地址放入中断向量表的N号表项中。     
4.  使用 `movsb` 指令，将 `do0` 的代码送入 `0:200` 处：     
    ```
    assume cs:code
    code segment
    start: 设置 es:di 指向目的地址
           设置 ds:si 指向源地址
           设置 cx 为传输长度
           设置传输方向为正
           rep movsb
           设置中断向量表
           mov ax, 4c00H
           int 21H
      do0: 显示字符串“overflow!”
           mov ax, 4c00H
           int 21H
    code ends
    end start
    ```
    用 `rep movsb` 指令的时候要确定的信息：     
    + 传送的原始位置，段地址：code，偏移地址：offset do0    
    + 传送的目的位置：0:200     
    + 传送的长度：do0 部分代码的长度      
    + 传送的方向：正向      
    更明确的程序：      
    ```
    assume cs:code
    code segment
    start: mov ax, cs
           mov ds, ax
           mov si, offset do0         ; 设置ds:si指向源地址
           mov ax, 0
           mov es, ax
           mov di, 200H               ; 设置es:di指向目的地址
           mov cx, do0部分代码的长度  ; 设置cx为传入长度
           cld                        ; 设置传入方向为正
           rep movsb
           设置中断向量表
           mov ax, 4c00H
           int 21H
       do0: 显示字符串“overflow!”
            movAX， 4c00H
            int 21H
      code ends
      end start
    ```
5.  如何知道 `do0` 代码的长度？计算一下 `do0` 中所有指令码的字节数。但是这样太麻烦了，而且只要 `do0` 的内容发生了改变，我们都要重新计算它的长度。我们可以利用编译器来计算 `do0` 的长度：     
    ```
    assume cs:code
    code segment
    start: mov ax, cs
           mov ds, ax
           mov si, offset do0                  ; 设置ds:si指向源地址
           mov ax, 0
           mov es, ax
           mov di, 200H                        ; 设置es:di指向目的地址
           mov cx, offset do0end - offset do0  ; 设置cx为传入长度
           cld                                 ; 设置传入方向为正
           rep movsb
           设置中断向量表
           mov ax, 4c00H
           int 21H
      do0: 显示字符串“overflow!”
           movAX， 4c00H
           int 21H
   do0end: nop

      code ends
      end start
    ```
    `-` 是编译器识别的运算符号，编译器可以用它来进行两个常数的减法。比如： `mov ax, 8-4`，被编译器处理为指令 `mov ax, 4`。      
    汇编编译器可以处理表达式：      
    指令：`mov ax, (5+3)*5/10`，被编译器处理为指令：`mov ax, 4`   
6.  `do0` 程序的主要任务是显示字符串：      
    ```
    do0: 设置ds:si指向字符串
         mov ax, 0b800H
         mov es, ax
         mov di, 12*160+36*2          ; 设置es:di指向显存空间的中间位置
         mov cx, 9                    ; 设置cx为字符串长度
      s: mov al, [si]
      mov es:[di], al
      inc si
      add di, 2
      loop s

      mov ax, 4c00H
      int 21H

    do0end: nop
    ```
    程序写好了，但是要显示的字符串放在哪里呢？      
    ```
    assume cs:code
    data segment
    db "overflow!"
    data ends

    code segment
    start: mov ax, cs
           mov ds, ax
           mov si, offset do0       ; 设置ds:si指向源地址
           mov ax, 0
           mov es, ax
           mov di, 200H             ; 设置es:di指向目的地址
           mov cx, offset do0end - offset do0 ; 设置 cx 为传输长度
           cld                      ; 设置传输方向为正
           rep movsb
           设置中断向量表
           mov ax, 4c00H
           int 21H
      do0: mov ax, data
           mov ds, ax
           mov si, 0                     ; 设置ds:si指向字符串

           mov ax, 0b800H
           mov es, ax
           mov di, 12*160+36*2           ; 设置es:di指向显存空间的中间位置
           mov cx, 9                     ; 设置cx为字符串长度
        s: mov al, [si]
           mov es:[di], al
           inc si
           add di, 2
           loop s

           mov ax, 4c00H
           int 21H
   do0end: nop
    code ends
    end start
    ```
    上面的程序，看似合理，实际上却是大错特错，“overflow”在程序段 `data` 中。上述程序执行完成后返回，它所占用的内存空间被系统释放，而在其中存放的“overflow!“，也将很可能被别的信息覆盖。而 `do0` 程序被放到了 `0:200` 处，随时都会因发生了除法溢出而被CPU执行，很难保证 `do0` 程序从原来程序所处的空间中取得的是要显示的字符串 ”overflow!“。      
    因为 `do0` 程序随时可能被执行，而它要用到字符串”overflow!“，所以该字符串也该存放在一段不会被覆盖的空间中，正确程序：      
    ```
    assume cs:code
    code segment
    start: mov ax, cs
           mov ds, ax
           mov si, offset do0            ; 设置ds:si指向源地址
           mov ax, 0
           mov es, ax
           mov di, 200H                  ; 设置es:di指向目的地址
           mov cx, offset do0end - offset do0 ; 设置cx为传输长度
           cld                           ; 设置传输方向为正
           rep movsb
           设置中断向量表

           mov ax, 4c00H
           int 21H

      do0: jmp short do0start
           db "overflow!"

      do0start: mov ax, cs
                mov ds, ax
                mov si, 202H            ; 设置ds:si指向字符串

                mov ax, 0b800H
                mov es, ax
                mov di, 12*160+36*2     ; 设置es:di指向显存空间的中间位置
                mov cx, 9

             s: mov al, [si]
                mov es:[di], al
                inc si
                add di, 2
                loop s

                mov ax, 4c00H
                int 21H

        do0end: nop
        code ends
        end start
    ```
    在上述程序中，我们将”overflow!“放到 `do0` 程序中，程序执行时，将标号 `do0` 到标号 `do0end` 之间的内容送到 `0000:0200` 处。     
    注意，因为在 `do0` 程序开始处的 ”overflow!" 不是可以执行的代码，所以在“overflow!”之前加上一条 `jmp` 指令，转移到正式的 `do0` 程序。当除法溢出发生时，CPU执行 `0:200` 处的 `jmp` 指令，跳过后面的字符串，转到正式的 `do0` 程序执行。      
    `do0` 程序执行过程中必须要找到“overflow!”，那么它在哪里呢？首先来看段地址，“overflow!”和 `do0` 的代码处于同一段中，而除法溢出发生时，CS中必然存放 `do0` 的段地址，也就是 “overflow!” 的段地址；再来看偏移地址， `0:200` 处的指令为 `jmp short do0start` 这条指令占用两个字节，所以“overflow!”的便宜地址为：202h。      
