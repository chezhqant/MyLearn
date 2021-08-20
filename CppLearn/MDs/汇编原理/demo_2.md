1.  编写、安装中断7cH的中断例程，功能：将一个全是字母，以0结尾的字符串，转化为大写。参数：`ds:si` 指向字符串的首地址。应用举例：将 `data` 段中的字符串转化为大写。      
    ```
    assume cs:code
    data segment
      db 'conversation', 0
    data ends

    code segment
    start: mov ax, data
           mov ds, ax
           mov si, 0
           int 7cH

           mov ax, 4c00H
           int 21H
    code ends
    end start
    ```
    安装程序如下：      
    ```
    assume cs:code
    code segment
    start: mov ax, cs
           mov ds, ax
           mov si, offset capital
           mov ax, 0
           mov es, ax
           mov di, 200H
           mov cx, offset capitalend-offset capital
           cld
           rep movsb

           mov ax, 0
           mov es, ax
           mov word ptr es:[7cH*4], 200H
           mov word ptr es:[7cH*4+2], 0
           mov ax, 4c00H
           int 21H

  capital: push cx
           push si
  changed: mov cl, [si]
           mov ch, 0
           jcxz ok
           and byte ptr [si], 11011111b
           inc si
           jmp short change
       ok: pop si
       pop cx
       iret
capitalend: nop
     code ends
     end start
    ```

    用 `7cH` 中断例程完成 `loop` 指令的功能。`loop s` 的执行需要两个信息，循环次数和到s的位移，所以，7cH中断例程要完成loop指令的功能，也需要这两个信息作为参数。我们用cx存放循环次数，用bx存放位移。应用举例：在屏幕中间显示80个"!"：        
    ```
    assume cs:code
    code segment
    start: mov ax, 0b800H
           mov es, ax
           mov di, 160*12
           mov bx, 00fset s-offset se ; 设置从标号se到标号s的转移位移
           mov cx, 80

        s: mov byte ptr es:[di], '!'
           add di, 2
           int 7ch        ; 如果(cx)不等于0，转移到标号s处

       se: nop
           mov ax, 4c00H
           int 21H

    code ends
    end start
    ```
    在上面的程序中，用 `int 7cH` 调用7cH中断例程进行转移，用bx传递转移的位移。分析：为了模拟loop指令，7cH中断例程应该具备下面功能：      
    + dec cx    
    + 如果(cx)不等于0，转到标号s处执行，否则向下执行。    
    下面分析7cH中断例程如何实现到目的地址的转移：     
    + 转到标号s显然应设(cs)=标号s的段地址，(IP)=标号s的偏移地址     
    + 中断例程如何得到标号s的段地址和偏移地址呢？     
    `int 7cH` 引发中断过程后，进入 7cH 中断例程，在中断过程中，当前的标志寄存器、CS和IP都要压栈，此时压入的CS和IP中的内容，分别是调用程序的段地址（可以认为是标号s的段地址）和int 7cH后一条指令的偏移地址（即标号se的偏移地址）。     
    可见，在中断例程中，可以重栈里取得标号s的段地址和标号se的偏移地址，而用标号se的偏移地址加上bx中存放的转移位移就可以得到标号s的偏移地址。   
    + 此时，可以知道可以从栈中直接和间接地得到标号s的段地址和偏移地址，那么如何用他们设置CS:IP呢？      
    可以是用iret指令，我们将栈中的se的偏移地址加上bx中的转移位移，则栈中的se的偏移地址就编程了s的偏移地址，我们再是用iret指令，用栈中的内容设置CS、IP，从而实现转移到标号s处。     
    ```
    lp: push bp
        mov bp, sp
        dec cx
        jcxz lpret
        add [bp+2], bx

 lpret: pop bx
        iret
    ```
    因为要访问栈，使用了bp，在程序开始处将bp入栈保存，结束时出栈恢复。当要修改栈中se的偏移地址的时候，栈中的情况为栈顶处是bp原来的数值，下面时se的偏移地址，再下面是s的打u你地址，再下面时标志寄存器的值。而此时，bp中为栈顶的偏移地址，所以((ss)*16+(bp)+2)处为se的偏移地址，将它加上bx中的转移位移就变为s的偏移地址，最后用iret出栈返回，CS:IP即从标号s处开始执行指令。如果(cx)=0，则不需要修改栈中se的偏移地址，直接返回1即可。CPU从标号se处向下执行指令。     
