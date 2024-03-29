## 第16章 直接定址表       
1.  之前，我们在代码中是用标号来标记指令、数据、段的起始地址，比如下面，将code段中的a标号处的8个数据累加，结果存储到b标号处的字中：        
    ```
    assume cs:code
    code segment
      a: db 1,2,3,4,5,6,7,8
      b: dw 0
    start: mov si, offset a
           mov bx, offset b
           mov cx, 8
        s: mov al, cs:[si]
           mov ah, 0
           add cs:[bx], ax
           inc si
           loop s

           mov ax, 4c00H
           int 21H

    code ends
    end start
    ```
    上述代码中，`code, a, b, start, s` 都是标号，这些标号仅仅表示了内存单元的地址。但是我们可以是用一种标号，这种标号不但表示内存单元的地址，还表示了内存单元的长度，即表示在此标号处的单元，是一个字节单元还是字单元，还是双字单元：     
    ```
    assume cs:code
    code segment
      a db 1,2,3,4,5,6,7,8
      b dw 0
    start: mov si, offset a
           mov bx, offset b
           mov cx, 8
        s: mov al, cs:[si]
           mov ah, 0
           add cs:[bx], ax
           inc si
           loop s

           mov ax, 4c00H
           int 21H

    code ends
    end start
    ```
    上述代码中，`a, b`后面没有是用“:“，他们是同事描述内存地址和单元长度的标号，标号a，描述了地址code:0，和从这个地址开始，以后的内存单元都是字节单元，而标号b描述了地址code:8，和从这个地址开始，以后的内存单元都是字单元。因为这种标号包含了对单元长度的描述，所以在指令中，它可以代表一个段中的内存单元。比如，对于程序中 `b dw 0`。      
    ```
    指令: mov ax, b
    相当于：mov ax, cs:[8]

    指令：mov b, 2
    相当于：mov word ptr cs:[8], 2

    指令：inc b
    相当于：inc word ptr cs:[8]
    ```
    在这些指令中，标号b代表了一个内存单元，地址为code:8，长度为2字节。      
2.  下面的指令会引起编译错误: `mov al, b`，因为b表示的内存单元是字单元，而al是8位寄存器。如果我们将程序中的指令：`add b, ax` 写为 `all b, al`，将出现同样的编译错误。对于程序中的 `a db 1,2,3,4,5,6,7,8`：   
    ```
    指令：mov al, a[si]
    相当于：mov al, cs:0[si]

    指令：mov al, a[3]
    相当于：mov al, cs:0[3]

    指令：mov al, a[bx+si+3]
    相当于：mov al, cs:0[bx+si+3]
    ```
    可见，使用这种包含单元长度的标号，可以使我们以简洁的形式访问内存中的数据，以后我们将这种标号称为数据标号，它标记了存储数据的单元的地址和长度。它不同于仅仅表示地址的地址标号      
3.  不在代码段中定义数据，而是将数据定义到其他段中。在其他段中，我们也可以是用数据标号来描述存储数据单元的地址和长度。在后面加有”:“的地址标号，只能在代码段中使用，不能在其他段中使用。   
4.  下面的程序将data段中a标号处的8个数据累加，结果存储到b标号处的字中：         
    ```
    assume cs:code, ds:data
    data segment
      a db 1,2,3,4,5,6,7,8
      b dw 0
    data ends

    code segment
    start: mov ax, data
           mov ds, ax
           mov si, 0
           mov cx, 8

        s: mov al, a[si]
           mov ah, 0
           add b, ax
           inc si
           loop s

           mov ax, 4c00H
           int 21H

    code ends
    end start
    ```
    如果想在代码段中，直接用数据标号访问数据，则需要用伪指令assume将标号所在的段和一个段寄存器联系起来。否则编译器在编译的时候，无法确定标号的段地址在哪一个寄存器中。当然，这种联系是编译器需要的，但是绝不是说，我们因为编译器的工作需要，用assume指令将段寄存器和某个段相联系，段寄存器中就会真的存放该段的地址。我们在程序中还要是用指令对段寄存器进行设置。     
    比如在上面的程序中，我们要在代码段code中用data段中的数据标号a，b访问数据，则必须用assume将一个寄存器和data段相连。在程序中，我们用ds寄存器和data段相连，则编译器对相关指令的编译如下：    
    ```
    指令：mov al, a[si]
    编译为：mov al, [si+0]

    指令：add b, ax
    编译为add [8], ax
    ```
    因为这些实际编译出的指令，都默认访问单元的段地址在ds中，而实际上要访问的段为data，所以，若要访问正确，在这些指令执行前，ds中必须为data段的段地址。则我们在程序中使用指令：   
    ```
    mov ax, data
    mov ds, ax
    设置ds执行data段
    ```
    我们可以将标号当作数据来定义，此时，编译器将标号所表示的地址当作数据的值。比如：     
    ```
    data segment
      a db 1,2,3,4,5,6,7,8
      b dw 0
      c dw a, b
    data ends
    ```
    数据标号c处存储的两个字型数据为标号a，b的偏移地址。相当于：     
    ```
    data segment
      a db 1,2,3,4,5,6,7,8
      b dw 0
      c dw offset a, offset b
    data ends
    ```
    再比如：      
    ```
    data segment
      a db 1,2,3,4,5,6,7,8
      b dw 0
      c dd a, b
    data ends
    ```
    数据标号c处存储的两个双字型数据为标号a的偏移地址和段地址、标号b的偏移地址和段地址。相当于：      
    ```
    data segment
      a db 1,2,3,4,5,6,7,8
      b dw 0
      c dw offset a, seg a, offset b, seg b
    data ends
    ```
    seg操作符，功能为取得某一标号的段地址     
5.  直接定址表待实现        
