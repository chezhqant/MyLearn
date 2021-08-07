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
    + CPU执行retf指令时，相当于进行 `pop CS`      
6.  CPU执行call指令时，进行两步操作：     
    + 将当前的IP或者CP和IP压入栈中      
    + 转移      
    call指令不能实现短转移，初次之外，call指令实现转移的方法和jmp指令的原理相同。       
6.  一句位移进行转移。`call 标号（将当前的IP压栈后，转到标号处执行指令）`   
    CPU执行此种格式的call指令时，进行如下操作：   
    + (sp)=(sp)=2     
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
7.  转移的目的地址在指令中。`call far ptr 标号` 实现的是段间转移位移。      
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
8.  转移地址在寄存器中。`call 16为寄存器`，功能：     
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
9.  转移地址在内存中。转移地址在内存中的call指令有两种格式：      
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
