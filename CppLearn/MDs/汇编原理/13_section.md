## 第十三章 int 指令 -- 另外一种内中断      
1.  int 指令的格式： `int n`，`n` 为中断类型码，它的功能是引发中断过程。       
2.  CPU执行 `int n` 指令，相当于引发一个n号中断的中断过程，执行过程如下：     
    + 取中断类型码n     
    + 标志寄存器入栈：IF=0，TF=0      
    + CS、IP入栈      
    + (IP)=(n*4)，(CS)=(n*4+2)        
    从此处转去执行n号中断的中断处理程序。可以在程序中是用int指令调用任何一个中断处理程序：     
    ```
    assume cs:code
    code segment
    start: mov ax, 0b800H
           mov es, ax
           mov byte ptr es:[12*160+40*2], '!'
           int 0
    code ends
    end start
    ```
    上述程序在windows2000中的DOS方式下执行时，将在屏幕上显示一个'!'，然后显示"Divide overflow"后返回系统中。"!"是我们编程显示的，而"Divide overflow" 是哪里来的呢？这是因为我们在结尾处是用了 `int 0` 指令。CPU执行 `int 0` 指令时，将引发中断过程，执行0号中断处理程序，而系统设置的0号中断处理程序的功能是显示"Divide overflow"，然后返回到系统。可见，int指令的最终功能和call指令相思，都是调用一段程序。我们可以将中断处理程序简称为中断例程。  
3.  [示例一](./demo_1.md)       
3.  [示例二](./demo_2.md)     
