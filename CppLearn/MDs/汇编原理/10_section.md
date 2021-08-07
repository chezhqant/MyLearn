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
