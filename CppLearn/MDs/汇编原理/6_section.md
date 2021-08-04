## 第六章 包含多个段的程序     
1.  程序取得所需空间的方法有两种，一是在加载程序的时候为程序分配，再就是程序在执行的过程中想系统申请。本课程不讨论第二种方法。      
2.  从规范的角度来讲，我们是不能自己随便决定哪个段空间可以是用的。应该让系统来分配。我们可以在程序汇中，__定义我们希望处理的数据__，这些数据就会被编译、链接程序作为程序的一部分写到可执行文件中。当可执行文件中的程序被加载入内存中，这些数据也同时被加载入内存中。数据也自然也获得了存储空间。      
3.  `dw` 的含义是定义字型数据，`dw` 就是 `define word`。     
4.  一个程序：      
    ```
    assume cs:code
    code segment
    dw 0123H, 0456H, 0789H, 0abcH, 0defH, 0fedH, 0cbaH, 0987H
    mov bx, 0
    mov ax, 0
    mov cx, 8
    ```
    上述代码中，定义的8个数据在哪里呢？因为 `dw` 定义的数据处于代码段的最开始，所以他们的地址就是: CS:0, CS:2, CS:6, CS:8, CS:A, CS:C, CS:E。      
<span id="锚点1">5.  一个程序</span>
    ```
    assume cs:code
    code segment
    dw 0123H, 0456H, 0789H, 0abcH, 0defH, 0fedH, 0cbaH, 0987H
    start: mov bx, 0
           mov ax, 0
           mov cx, 8
           s: add ax, cs:[bx]
              add bx, 2
              loop s
    mov ax, 4c00H
    int 21H
    code ends
    end start
    ```
    `start` 这个标号是在伪指令 `end` 的后面出现。`end` 除了通知编译器程序结束外，还可以通知编译器程序的入口在什么地方。`end` 指令指明了程序在编号 `start` 处，也就是说 `mov bx, 0` 是程序的第一条指令。      
6.  可执行文件的执行过程：      
    + 由其他程序（Debug，command或者其他程序）将可执行文件中的程序加载入内存        
    + 设置CS:IP 指向程序的第一条要执行的指令（即程序的入口），从而使程序得以运行。    
    + 程序运行结束后，返回到加载者      
7.  根据什么设置CPU的CS:IP指向程序的第一条执行的指令？也就是说如何知道哪一条指令是程序的第一条要执行的指令？这一点是由可执行文件中的描述信息指明的。我们知道 __可执行文件由描述信息和程序组成，程序来自于源程序中的汇编指令和定义的数据；描述信息主要是编译、链接程序对源程序中相关伪指令进行处理所得到的信息__。在 [第五条](#锚点1) 中，用伪指令描述了程序的结束和程序的入口，在编译、链接之后，由 `end start` 指明的程序入口，被转换为一个入口地址，储存在可执行文件的描述信息中，这个入口地址的偏移地址部分为: `10H`。当程序被加载入内存后，加载者从程序的可执行文件的描述信息中读到程序的入口地址。设置CS:IP，这样CPU就从我们希望的地址处开始执行。如果要CPU从何处开始执行程序，只要在源程序中用 `end 标号` 指明就可以了。       
8.  程序框架:     
    ```
    assume cs:code
    code segment
    数据
    ...
    ...
    start: 
    ...
    ...
    code ends
    end start
    ```
9.  我们可以通过敌营数据来取得一段空间，然后将这段空间当作栈空间来用。      
    ```
    assume cs:code
    code segment
    dw 0123H, 0456H, 0789H, 0abcH, 0defH, 0fedH, 0cbaH, 0987H
    dw 0, 0, 0, 0, 0, 0, 0, 0         ;该空间当作栈来用
    start: move ax, cs
           mov ss, ax
           mov sp, 32         ;将设置栈顶ss:sp指向cs:32
           mov bx, 0
           mov cx, 8
        s: push cs:[bx]
           add bx, 2
           loop s             ;以上代码段0~16单元中的8个字型数据依次入栈
           mov bx, 0
           mov cx, 8
       s0: pop cs:[bx]
           add bx, 2
           loop s0            ;以上依次出栈8个字型数据到代码段0~16单元中
           mov ax, 4c00H
           int 21H
    codesg ends
    end start                 ;指明程序的入口在start处
    ```
10.  一个程序：   
     ```
     assume cs:code, ds:data, ss:stack
     data: segment
       dw 0123H, 0456H, 0789H, 0abcH, 0defH, 0fedH, 0cbaH, 0987H
     data ends
     stack segment
       dw 0, 0, 0, 0, 0, 0, 0, 0
     stack ends
     code segment
     start: mov ax, stack
            mov ss, ax
            mov sp, 16      ;设置栈顶ss:sp指向stack:16
            mov ax, data
            mov ds, ax      ;ds指向data段
            mov bx, 0       ;ds:bx指向data段中的第一个单元
            mov cx, 8
         s: push [bx]
            add bx, 2
            loop s          ;以上将data段中的0-16单元中的8个字型数据依次入栈
            mov bx, 0
            mov cx, 8
        s0: pop [bx]
            add bx, 2
            loop s0         ;以上使8个字型数据一次出栈并送到data段的0-16单元中
            mov ax, 4c00H
            int 21H
     code ends
     end start
     ```
     以上，表示，定义一个段的方法和我们以前所述的定义代码段的方法没有区别，只是对于不同的段，要有不同的段名。      
     __对段地址的引用__ 可以是用 `mov ax, data`，一个段中的数据的段地址可由段名代表，偏移地址就要看它在段中的位置了。程序中 "data" 段中的数据 "0abcH" 的地址就是"data:6"。可以这么使用：      
     ```
     mov ax, data
     mov ds, ax
     mov ax, ds:[6]
     ```
     以上可以看出，CPU到底如何处理我们定义的段中的内容，是当作指令执行，还是当作数据访问，还是当作栈空间，完全是靠程序中具体的汇编指令，和汇编指令对CS:IP, SS:SP, DS等寄存器的设置来决定的。      
