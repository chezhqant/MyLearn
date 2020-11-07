1.  源文件  
    +  cmake的源文件，可以包含命令+注释+空格+换行。
    +  以cmake编写的源文件CMakeLists.txt命名或者以.cmake为扩展名。   
    +  一般在项目源码的最顶层目录防止CMakeLists.txt编写的整个项目的构建规则，或者通过add_subdirectory()命令把下一层源码目录的构建规则也添加进来。        
    +  cmake源文件中所有有效的语句都是命令（内置的命令或者自定义的函数或者宏命令）     
2.  注释    

    +  单行注释   
       ```
       # 注释内容   
       ```

    +  多行注释   
       ```
       #[=*[注释内容]=*]    
       ```
       其中*号表示0个或者多个=，当然左边的=号的数量要等于右边的=号的数量.      

       例：        
       ```
       #[[这是多行注释!   
       这是多行注释!    
       这是多行注释!]]    
       message("First Argument\n" #[[这是多行注释]] "Second Argument")      
       ```

3.  变量    

    在cmake语言中，所有的变量都是string类型，可以使用cmake内置的set()和unset()命令来明确的设置或者移除一个变量。   

    +  定义变量   
       见cmake文件夹下的cmake.md里面的set     

    +  变量的引用     
       见cmake文件夹下的cmake.md里面的set     

4.  列表      

    列表也是字符串，可以把列表看成特殊变量，这个变量有很多个值，每个值用分号进行分割。      

    +  定义列表   
       见cmake文件夹下的cmake.md里面的set     

    +  列表的引用   
       见cmake文件夹下的cmake.md里面的set     
       不加引号的引用cmake将自动在分号处进行切分成多个列表元素，并把他们作为多个独立的参数传给命令。加了引用的引用cmake不会进行切分，并保持分号不动，把整个引用的内容当作一个参数传递给命令。      

5.  流控制命令    

    在cmake语法中，不管是条件语句，循环语句，函数或者宏都是命令。   
    
    +  操作符   
       用于条件或者循环的表达式的操作符，这些操作符是大小敏感的，操作符的优先级：   
       `带()表达式 > 一元 > 二元 > 逻辑`      
       [操作符表格](./pictures/操作符.jpg)      

    +  布尔常量值   
       cmake中的布尔常量值也是大小写敏感的。    
       [布尔常量值表格](./pictures/布尔常量值表格.jpg)    

    +  条件命令   
       ```
       if(表达式)
         #要执行的命令块
         command1(ARGS ...)
         command2(ARGS ...)
       elseif(表达式2)
         #要执行的命令块
         command1(ARGS ...)
         command2(ARGS ...)
       else(表达式)
         #要执行的命令块
         command1(ARGS ...)
         command2(ARGS ...)
       endif(表达式)
       ```
       缩进和空格对语句解析没有影响。     

    +  循环命令   
       ```
       while(表达式)
         #要执行的命令块
         command1(ARGS ...)
         command2(ARGS ...)
       ```
       循环也可以是用break()退出，continue()命令可以跳出下来的语句块，立即基尼如下一次循环迭代。     

    +  循环遍历   
       ```
       foreach(循环变量 arg1 arg2 ...)
         #要执行的命令块
         command1(ARGS ...)
         command2(ARGS ...)
       endforeach(循环变量)
       ```
       每次迭代设置${循环变量} = argN   
       例子：   
       ```
       foreach(item "A" "B" "C")
         message(" ${item}")
       endforeach(item)
       ```
       ```
       foreach(循环变量 RANGE total)
         #要执行的命令块
         command1(ARGS ...)
         command2(ARGS ...)
       endforeach(循环变量)
       ```
       循环的范围是0~total      
       ```
       foreach(循环变量 RANGE start stop [step])
         #要执行的命令块
         command1(ARGS ...)
         command2(ARGS ...)
       endforeach(循环变量)
       ```
       循环的范围是start~stop，循环增量是step     
       ```
       foreach(loop_var IN [LISTS [lists1 [...]]]
                           [ITEMS [item1 [...]]])
       ```
       foreach支持对列表遍历      
       ```
       set(list_var "1;2;3;4")
       foreach(x IN LISTS list_var)
         message(" ${x}")
       endforeach(x)
       ```
       foreach也支持break()，continue()命令操作      

5.  命令    

    cmake支持很多内置的命令，像我们之前是用的set，message，if，while，foreach等待都是内置的命令。也可以是自定义命令。命令可以带字符串参数，但是没有返回值。命令名是大小写不敏感的，所以set和SET是一样的。但是命令带的参数名是大小写敏感的，ARG和arg是两个不同的参数。     
