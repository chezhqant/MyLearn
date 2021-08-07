## call 和 ret 指令     
1.  call 和 ret指令都是转移指令，他们都修改IP，或者同事修改CS和IP。      
2.  ret 指令用栈中的数据，修改IP的内容，从而实现近转移；retf指令用栈中的数据，修改CS和IP的内容，从而实现远转移。    
3.  CPU 执行 ret 指令时，进行下面的操作：   
    + (IP)=((ss)*16+(sp))     
    + (sp)=(sp)+2      
4.  CPU 执行retf指令时，进行下面四步操作：      
    + (IP)=((ss)*16+(sp))     
    + (sp)=(sp)+2     
    + (CS)=((ss)*16+(sp))     
    + (sp)=(sp)+2     
5.  用汇编语法解释 ret 和 ref 指令    
    + CPU执行ret指令时，相当于 `pop IP`   
    + CPU执行retf指令时，相当于进行     
      ```
      pop IP
      pop CS
      ```      
6.  CPU执行call指令时，进行两步操作：     
    + 将当前的IP或者CP和IP压入栈中      
    + 转移      
    call指令不能实现短转移，初次之外，call指令实现转移的方法和jmp指令的原理相同。       
7.  一句位移进行转移。`call 标号（将当前的IP压栈后，转到标号处执行指令）`   
    CPU执行此种格式的call指令时，进行如下操作：   
    + (sp)=(sp)-2     
    + ((ss)*16+(sp))=(IP)     
    + (IP)=(IP)+16位位移      
    16位位移=“标号”处的地址-call指令后的第一个字节的地址   
    16位位移的范围为-32768-32767，用补码表示    
    16位位移由编译程序在编译时算出      
    从上面的描述中，可以看出，如果我们用汇编语法来解释此种格式的call指令，则CPU执行指令“call 标号”时，相当于进行：    
    ```
    push IP
    jmp near ptr 标号
    ```
    这种call指令对应的机器指令中并没有转移的目的地址，而是相对于当前IP的转移位移。    
8.  转移的目的地址在指令中。`call far ptr 标号` 实现的是段间转移位移。      
    CPU执行此种格式的call指令时，进行如下操作：   
    + (sp)=(sp)-2     
    + ((sp)*16+(sp))=(CS)       
    + (sp)=(sp)-2
    + ((ss)*16+(sp))=(IP)     
    + (CS)=标号所在段的段地址     
    + (IP)=标号在段中的偏移地址       
    从上面的描述中可以看出，我们用汇编语法来解释此种格式的call指令，则：CPU执行指令“call far ptr 标号”时，相当于进行：      
    ```
    push CS
    push IP
    jmp far ptr 标号
    ```
9.  转移地址在寄存器中。`call 16为寄存器`，功能：     
    ```
    (sp)=(sp)-2
    ((ss)*16+(sp))=(IP)
    (IP)=(16位寄存器)
    ```
    用汇编语法来解释此种格式的call指令，CPU执行call 16位reg时，相当于进行：   
    ```
    push IP
    jmp 16位寄存器
    ```
10.  转移地址在内存中。转移地址在内存中的call指令有两种格式：      
    + `call word ptr 内存单元地址`，用汇编语法来解释此种格式的call指令，则：CPU执行call word ptr 内存单元地址时，相当于进行：    
      ```
      push IP
      jmp word ptr 内存单元地址
      ```
      比如，下面的指令：      
      ```
      mov sp, 10H
      mov ax, 0123H
      mov ds:[0], ax
      call word ptr ds:[0]
      ```
      执行之后，(IP)=0123H，(sp)=0EH。      
    + `call dword ptr 内存单元地址`，用汇编语法来解释此种格式的call指令，则：CPU执行call dword ptr 内存单元地址 时，相当于进行:     
      ```
      push CS
      push IP
      ```
      比如下面的指令：      
      ```
      mov sp, 10H
      mov ax, 0123H
      mov ds:[0], ax
      mov word ptr ds:[2], 0
      call dword ptr ds:[0]
      ```
      执行后，(CS)=0，(IP)=0123H，(sp)=0CH。      
11.  例子(__很重要__)：   
     下面的程序执行后，ax中的数值时多少？   
     ```
     assume cs:code
     code segment
       start：mov ax, 1
       mov cx, 3
       call s
       mov bx, ax         ; (bx)=?
       mov ax, 4C00H
       int 21H
     s: add ax, ax
        loop s
        ret
     code ends
     end start
     ```
     分析：     
     + CPU 将 `call s` 指令的机器码读入，IP指向了 `call s`       的指令 `mov bx, ax`，然后CPU执行 `call s` 指令，将当前的IP值（指令 `mov bx, ax` 的偏移地址）压栈，并将IP的值改变为标号为标号 `s` 处的偏移地址。     
     + CPU 从标号 `s` 处开始执行指令，loop 循环完毕后，(ax)=8。     
     + CPU将 `ret` 指令的机器码读入，IP指向了 `ret` 指令后的内存单元，然后CPU执行 `ret` 指令，从栈中弹出一个值（即 `call s` 先前压入的 `mov bx, ax` 指令的偏移地址）送入IP中，则CS:IP指向指令 `mov bx, ax`。      
     + CPU 从 `mov bx, ax` 开始执行指令，直至完成。     
12.  例子(__更重要__):    
     ```
     源程序                         内存中的情况（假设程序从内存1000:0处装入）
     assume cs:code
     stack segment
       db 8 dup (0)                 1000:1000 00 00 00 00 00 00 00 00 
       db 8 dup (0)                 1000:1008 00 00 00 00 00 00 00 00
     stack ends

     code segment
     start: mov ax, stack             1001:0000    B8 00 10
       mov ss, ax                     1001:0003    8E D0
       mov sp, 16                     1001:0005    BC 10 00
       mov ax, 1000                   1001:0008    B8 E8 03
       call s                         1001:000B    E8 05 00
       mov ax, 4C00H                  1001:000E    B8 00  4C
       int 21H                        1001:0011    CD 21
     s: add ax, ax                    1001:0013    03 C0
        ret                           1001:0015    C3
     code ends
     end start
     ```
     + 前三条指令执行后，栈的是用情况：     
       ```
       1000:0000      00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 <- ss:sp
       ```
     + call 指令读入后，(IP)=000E，CPU指令缓冲器中的代码为：E8 05 00；CPU执行 E8 05 00，首先，栈中的情况变为：    
       ```
       1000:0000      00 00 00 00 00 00 00 00 00 00 00  00 00 00 0E(<-ss:sp) 00
       ```
       然后，(IP)=(IP)+0005=0013H     
     + CPU 从cs:0013H处（即标号s处）开始执行      
     + ret指令读入后：    
       (IP)=0016H，CPU指令缓冲器中的代码为：C3    
       CPU执行C3，相当于进行 `pop IP`，执行后，栈中的情况为：   
       ```
       1000:000       00 00 00 00 00 00 00 00 00 00 00  00 00 00 0E 00 <-ss:sp
       ```
       (IP)=000EH     
     + CPU 回到cs:00EH处（即call指令后面的指令处）继续执行         
13.  我们可以配合使用 `call` 和 `ret`，写子程序，子程序框架：       
     ```
     标号：
        指令
        ret
     ```
     具体子程序的源程序框架如下：   
     ```
     assume cs:code
     code segment
     main:
       ...
       ...
       call sub1        ; 调用子程序sub1
       ...
       ...
       mov ax, 4C00H
       int 21H
     sub1:
       ...
       ...
       call sub2        ; 调用子程序sub2
       ...
       ...
       ret              ; 子程序返回
     sub2:
       ...
       ...
       ret              ; 子程序返回
     code ends
     end main
     ```
14.  `mul` 指令   
     + 两个相乘的数，严么都是8位，要么都是16位，如果是8位，一个默认放在AH中，另一个放在8位寄存器或者内存字节单元中；如果时16位，一个默认在AX中，另一个放在16为寄存器或者内存字单元中     
     + 结果：如果时8位乘法，结果默认放在AX中，如果时16位乘法，结果高位默认在DX中存放，低位在AX中存放。格式如下：
     ```
     mul reg
     mul 内存单元
     ```
     内存单元可以用不同的寻址方式给出，比如：     
     ```
     mul byte ptr ds:[0]
     ```
     含义为：(ax)=(al)*((ds)*16+0)。      
     ```
     mul word ptr [bx+si+8]
     ```
     含义为：(ax)=(ax)*((ds)*16+(bx)+(si)+8)结果的低16位；(dx)=(ax)*((ds)*16+(bx)+(si)+8)结果的高16位。    
15.  参数和返回值的存储：寄存器、内存。用寄存器来存储参数和结果是最常是用的方法。对于存放参数的寄存器和存放结果的寄存器，调用者和子程序的读写操作恰恰相反；调用者将参数送入参数寄存器，从结果寄存器中渠道返回值；子程序从参数寄存器中取到参数，将返回值送入结果寄存器。             
     ```
     assume cs:code
     data segment
       dw 1, 2, 3, 4, 5, 6, 7, 8
       dw 0, 0, 0, 0, 0, 0, 0, 0
     data ends

     code segment
     start: mov ax, data
            mov ds, ax
            mov si, 0               ;ds:si指向第一组word单元
            mov di, 16              ;ds:di指向第二组dword单元
            mov cx, 8
         s: mov bx, [si]
            call cube
            mov [di], ax
            mov [di].2, ax
            add si, 2               ;ds:si指向下一个word单元
            add di, 4               ;ds:si指向下一个dword单元
            loop s
            mov ax, 4C00H
            int 21H
      cube: mov ax, bx
            mul bx
            mul bx
            ret
     code ends
     end start
     ```
     以上代码中，子程序只有一个参数，放在bx中。如果有两个参数，那么可以是用两个寄存器来放，但是再多些，就不能放到寄存器中了。这时候需要将批量数据放到内存中，然后将它们所在内存空间的首地址放在寄存器汇总，传递给需要的子程序。对于具有批量数据的返回结果，也可用同样的方法。    
16.  将参数和返回值放到内存中的demo:      
     ```
     capital: and byte ptr [si], 11011111b  ;将ds:si所指单元的字母转化为大写
              inc si
              loop capital
              ret
     ```
     ```
     assume cs:code
     data segment
       db 'conversation'
     data ends
     code segment
       start: mov ax, data
              mov ds, ax
              mov si, 0     ;ds:si指向字符串（批量数据所在空间的首地址）
              mov cx, 12    ;cx存放字符串的长度
              call capital
              mov ax, 4C00H
              int 21H
       capital: and byte ptr [si], 11011111b
                inc si
                loop capital
                ret
     code ends
     end start
     ```
