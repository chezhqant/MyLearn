1.  编写、安装中断7cH的中断例程，功能：求一word型数据的平方。参数：(ax)=要计算的数据。返回值：dx, ax中存放结果的高16位和低16位。应用举例：求2*3456^2        
    ```
    assume cs:code
    code segment
    start: mov ax, 3456         ; (ax)=3456
           int 7cH              ; 调用中断7cH的中断例程，计算ax中的数据的平方
           add ax, ax
           adc dx, dx           ; dx:ax存放结果，将结果乘以2
           mov ax, 4c00H
           int 21H
    code ends
    end start
    ```
    我们要做三部分：      
    + 编写实现求平方功能的程序      
    + 安装程序，我们将其安装在0:200处     
    + 设置中断向量表，将程序的入口地址保存在7cH表项中，使其称为中断7cH的中断例程        
    安装程序：      
    ```
    assume cs:code
    code segment
    start: mov ax, cs
           mov ds, ax
           mov si, offset sqr           ; 设置ds:si指向源地址
           mov ax, 0
           mov es, ax
           mov di, 200H                 ; 设置es:di指向目的地址
           mov cx, offset sqrend-offset sqr ; 设置cx为传输长度
           cld                          ; 设置传输方向为正
           rep movsb

           mov ax, 0
           mov es, ax
           mov word ptr es:[7cH*4], 200H
           mov word ptr es:[7cH*4+2], 0

           mov ax, 4c00H
           int 21H

      sqr: mul ax
           iret

   sqrend: nop

    code ends
    end start
    ```
    在中断例程sqr的最后，要是用iret指令，用汇编语法描述，iret指令的功能为：   
    ```
    pop IP
    pop CS
    popf
    ```
    CPU执行 `int 7cH` 指令进入中断例程之前，标志寄存器、当前的CS和IP被压入栈中，在执行完中断例程后，应该用 `iret` 指令恢复 `int 7cH` 执行前的标志寄存器和CS、IP的值，从而接着执行应用程序。`int` 指令和 `iret` 指令的配合是用与 `call` 指令和 `ret` 指令的配合是用具有相似的思路。      
2.  编写、安装中断 `7cH` 的中断例程，功能：将一个全是字符，以0结尾的字符串，转化为大写。参数：ds:si指向字符串的首地址。应用举例：将data段中的字符串转化为大写：      
    ```

    ```
