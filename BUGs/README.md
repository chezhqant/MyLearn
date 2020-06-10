___this file is for record bugs___

##  python

##  c family
1.  [fatal error:X11/XXXX.h:No such directory](https://blog.csdn.net/bedisdover/article/details/51840639)   

## cmake
1.  export静态库的问题    
    比如我现在有两个库A，B。假设B依赖于A，如果在同一个cmakelists.txt文件中写他们，记得不能使用两条export语句，只能使用list(append， targets)，然后使用export(targets)，我犯的错误是：
    ```
    target_link_libraries(A)
    export(A)
    target_link_libraries(B A)
    export (B)

    实际上应该是：
    set(TARGETS)
    target_link_libraries(A)
    list(APPEND TARGETS A)
    target_link_libraries(B A)
    list(APPEND TARGETS B)
    export (B, XXX.cmake)
    ```
