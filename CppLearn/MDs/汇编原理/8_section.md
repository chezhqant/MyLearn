## 第八章 数据处理的两个基本问题    
1.  本书是用两个描述性的符号 `reg` 来标识一个寄存器，用 `sreg` 表示一个段寄存器。     
2.  在8086CPU中，只有这4个寄存器可以用在“[]”中来进行内存单元的寻址。这四个寄存器是 __bx, si, di, bp__。 比如：      
    ```
    mov ax, [bx]      ;right
    mov av, [bx+si]   ;right
    mov ax, [bx+di]   ;right
    mov ax, [bp]      ;right
    mov ax, [bp+si]   ;right
    mov ax, [bp+di]   ;right
    mov ax, [cx]      ;wrong
    mov ax, [ax]      ;wrong
    mov ax, [dx]      ;wrong
    mov ax, [ds]      ;wrong
    ```
    在“[]”中，这四个寄存器可以单个出现，或者只能以四种组合出现：bx和si，bx和di，bp和si，bp和di。      
    ```
    mov ax, [bx]          ;right
    mov ax, [si]          ;right
    mov ax, [di]          ;right
    mov ax, [bp]          ;right
    mov ax, [bx+si]       ;right
    mov ax, [bx+di]       ;right
    mov ax, [bp+si]       ;right
    mov ax, [bp+di]       ;right
    mov ax, [bx+si+idata] ;right
    mov ax, [bx+di+idata] ;right
    mov ax, [bp+si+idata] ;right
    mov ax, [bp+di+idata] ;right
    mov ax, [bx+bp]       ;right
    mov ax, [si+di]       ;right
    ```
    只要在“[]”中是用寄存器bp，而指令中没有显性地给出段地址，段地址默认就在ss中：      
    ```
    mov ax, [bp]            ;(ax)=((ss)*16+(bp))
    mov ax, [bp+idata]      ;(ax)=((ss)*16+(bp)+idata)
    mov ax, [bp+si]         ;(ax)=((ss)*16+(bp)+(si))
    mov ax, [bp+si+idata]   ;(ax)=((ss)*16+(bp)+(si)+idata)
    ```
3.  绝大部分机器指令都是进行数据处理的指令，处理大致可以分为三类：读取、写入、运算。在机器指令这一层来讲，并不关心数据的值是多少，__而关心指令执行前一刻__，它将要处理的数据所在的位置。指令在执行前，索要处理的数据可以在三个地方：CPU内部、内存、端口。          
