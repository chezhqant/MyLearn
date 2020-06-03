___cmake 总结___

[cmake概览](./pictures/1.jpg "cmake概览")   

0.  两个过程    
    +  CMake包括两个过程：configure和generate。configure的过程就是从输入创建内部表示，generate的过程是生成工程文件过程。    
    +  cmake需要cache文件的原因是每次build的时候，如果有external project，那么无需再次给定环境变量，对于一个项目有多个CMakeLists.txt文件来说比较方便。    
    +  configure的具体过程就是：如果存在CMakeCache.txt则首先读取CMakeCache.txt，否则读取CMakeLists.txt，由cmake的语言解释器解释它，遇到了像include，add_subdirectory命令等，会有command pattern object来执行，并递归解释子目录下的CMakeLists.txt，当所有CMakeLists.txt都解释完后会得到一个CMakeCache.txt文件.     
    +  CMakeCache.txt   
       +  当cmake第一次运行一个空的构建的时候，他就会创建一个CMakeCache.txt文件，文件里面存放了一些可以用来制定工程的设置，比如：变量、选项等
       +  对于同一个变量，如果Cache文件里面有设置，那么CMakeLists文件里就会优先使用Cache文件里面的同名变量。
       +  CMakeLists里面通过设置了一个Cache里面没有的变量，那就将这个变量的值写入到Cache里面
        
          ```
          //变量var的值被设置成1024，如果变量var在Cache中已经存在，该命令不会覆盖cac he里面的值
          SET(var 1024)
          //如果var在Cache中存在，就优先使用Cache里面的值，如果不存在，就将该值写入Cache里面
          SET(var 1024..CACHE..)
          //无论Cache里面是否存在，都始终使用该值
          SET(var..CACHE..FORCE)
          ```

1.  [cmake手册](https://www.cnblogs.com/coderfenghc/tag/cmake/)
  1.  [cmake policy](https://www.cnblogs.com/hustdc/p/6644002.html)   
  2.  [cmake find\_package](https://www.jianshu.com/p/39fc5e548310)   
      [第二次理解](https://blog.csdn.net/dbzhang800/article/details/6329314)    
      [第三次理解](https://dawnarc.com/2018/04/buildcmake%E5%B8%B8%E7%94%A8%E9%85%8D%E7%BD%AE%E9%A1%B9/)    
  3.  [excute_process](https://blog.csdn.net/qq_28584889/article/details/97758450)    
  4.  [option()](https://zhjwpku.com/2019/11/15/cmake-basic-commands-intro.html)    
  5.  [cmake_dependent_option](http://www.up4dev.com/2019/12/12/cmake_dependent_option/)    
  6.  [cmake  function() macro()](https://elloop.github.io/tools/2016-04-11/learning-cmake-3-function-macro)      
  7.  [set](https://www.cnblogs.com/narjaja/p/8351500.html)     
  8.  [execute_process](https://blog.csdn.net/qq_28584889/article/details/97758450)   
  9.  [include](https://blog.csdn.net/liitdar/article/details/81144461)   
      [再解include](https://blog.csdn.net/qq_38410730/article/details/102677143)    
  10. [string](https://www.sunxidong.com/340.html)    
  11. [find_libraries，里面有类似命名空间的讲解，比如md::image3d](https://gongzq5.github.io/posts/CMake-%E4%BB%8E0%E5%BC%80%E5%A7%8B-2019-09-06/)    
2.  cmake实践这本书   
3.  [cmake下载路径](https://cmake.org/files)  
4.  cmake 构建选项
    1.  -C(没查出来什么意思)
    2.  -G
        通过 CMake 生成特定 IDE 的项目配置文件。这个操作依赖 IDE，即无法在一个没安装 Xcode 的 macOS 上通过 CMake 生成对应的工程文件。
        +  -GXcode 生成 Xcode 工程文件
        +  -GVisual Studio 15 2017 生成 Visual Studio 2017 工程文件
        +  -G"UnixMakefiles", 指定构建系统，当前只想创建Linux/Unix系统标准Makefile。所以指定为Unix Makefile.
    3.  CMAKE_BUILD_TYPE
        指定构建模式，比如 Debug 还是 Release，默认值 Debug
    4.  -H -B
        -H 用来指定一个源码目录，指定的目录必须含有一个 CMakeLists.txt 文件，-B 用来指定 CMake 生成的中间文件的存放目录。
        -H..\cocos2d-x -Bmsvc_build 指定要构建工程的工程路径是上一级目录的 cocos2d-x 子目录，指定 CMake 生成的文件存放在 msvc_build 目录。
    5.  --build   
        执行构建过程，同时指定曾使用 CMake 命令生成的构建文件所在目录。   
        cmake --build ./msvc_build 在执行这个构建过程时，CMake 会自动选择对应的构建工具。    
    6.  -D    
        -D后面不能有空格，例如：cmake -DCMAKE_BUILD_TYPE:STRING=Debug     
    7.  -U    
        此选项和-D功能相反，从Cache文件中删除变量，支持使用*和？通配符    
    8.  打印运行的每一行CMake
        +  命令行选项中：--trace，将打印运行的每一行CMake，例如windows下执行: cmake –trace ..
        +  命令：--trace-source="filename"就会打印出有关filename的执行
5.  cmake命令  
    1.  设置编译参数    
        +  add_definitions（-DENABLED），当在CMake里面添加该定义的时候，如果代码里面定义了#ifdef ENABLED #endif相关的片段，此时代码里面这一块代码就会生效   
        +  add_definitions( “-Wall -ansi –pedantic –g”)：该命令现已经被取代，使用： add_compile_definitions(WITH_OPENCV2)    
    2.  [add_custom_command()/add_custom_target()](https://zhuanlan.zhihu.com/p/95771200)
    3.  source_group命令    
        使用该命令可以将文件在VS中进行分组显示；source_group("Header Files" FILES {HEADER_FILES})；以上命令是将变量HEADER_FILES里面的文件，在VS显示的时候都显示在“Header Files”选项下面    
    4.  [add_subdirectory](https://zhuanlan.zhihu.com/p/85980099)   
    5.  [add_test](https://www.thinbug.com/q/36304289)  
        +  enable_testing(): 启用CMake项目的测试功能，只能在顶层CMakeLists.txt中使用。开启后能够使用add_test()命令    
        +  add_test(testname executable arg1 …)：使用CTest运行测试，executable可以是测试程序、脚本等，接下来给代码添加测试
    6.  [aux_source_directory](https://elloop.github.io/tools/2016-04-10/learning-cmake-2-commands)
    7.  build_command(查不到)   
    8.  configure_file(查不到)    
    9.  option    
        [理解](https://www.cnblogs.com/rickyk/p/3872568.html)   
    10. set   
        [理解](https://www.cnblogs.com/narjaja/p/8351500.html)    
6.  变量    
    1. [CMAKE_INSTALL_MESSAGE](https://cmake.org/cmake/help/v3.1/variable/CMAKE_INSTALL_MESSAGE.html)   
    2.  [CMAKE_CXX_STANDARD](https://kheresy.wordpress.com/2017/08/28/abi-incompatible-of-g/)    
        C++11标准   
    3.  [CXX_STANDARD_REQUIRED](https://cmake.org/cmake/help/v3.1/prop_tgt/CXX_STANDARD_REQUIRED.html)      
    4.  CMAKE_CXX_FLAGS   
        + [解释一](https://blog.csdn.net/10km/article/details/51    731959)     
        + [解释二](https://www.jianshu.com/p/e9b1e9e833b2)      
    5.  [-D_GLIBCXX_USE_CXX11_ABI](https://my.oschina.net/tigerBin/blog/2049922)    
    6.  [CMAKE_EXPORT_COMPILE_COMMANDS](https://ihuifeng.cc/2019/08/10/C-C-%E7%BC%96%E7%A8%8B%E5%AE%9E%E7%8E%B0%E7%B2%BE%E5%87%86%E7%9A%84%E8%AF%AD%E4%B9%89%E7%BA%A7%E8%A1%A5%E5%85%A8/)   
    7.  [cmake默认编译、链接选项](https://blog.csdn.net/icbm/article/details/52336497)    
    8.  [ENV](https://blog.csdn.net/10km/article/details/51769633)    

7.  [另一个比较全面的博客](http://ijinjay.github.io/blog/2017-04/CMake%E4%BD%BF%E7%94%A8.html)     

9.  [cmake将变量传递给代码](https://www.coder.work/article/1206996)   
10.  [在各级子项目(目录)之间共享变量](https://blog.csdn.net/10km/article/details/50508184)    
___待总结___
