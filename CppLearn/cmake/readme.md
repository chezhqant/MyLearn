___cmake 总结___

[cmake 官方教程，英文版](https://cmake.org/cmake/help/latest/index.html)    
[cmake API中文](https://gearyyoung.gitbooks.io/cmake-api/content/cmake/CMake%E8%AF%AD%E6%B3%95.html?q=)   

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
      [版本控制](https://murphypei.github.io/blog/2018/11/cmake-install-find-package)   
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
  12.  add_libraries   
       ADD_LIBRARY(libname [SHARED|STATIC|MODULE][EXCLUDE_FROM_ALL]source1 source2 ... sourceN)ADD_LIBRARY(libname [SHARED|STATIC|MODULE][EXCLUDE_FROM_ALL]source1 source2 ... sourceN)   
       你不需要写全libhello.so，只需要填写hello即可，cmake系统会自动为你生成libhello.X。类型有三种:   
       +  SHARED, 动态库   
       +  STATIC, 静态库   
       +  MODULE, 在使用dyId的系统有效，如果不支持dyId，则被当作SHARED对待    
       +  EXCLUDE_FROM_ALL，参数的意思是这个库不会被默认构建，除非有其他的组件依赖或者手工构建。    
  13.  set_target_properties    
       SET_TARGET_PROPERTIES(target1 target2 ...PROPERTIES prop1 value1prop2 value2 ...)    
       这条命令可以用来设置输出的名称，对于动态库，还可以用来指定动态库的版本和API版本。    
       set_target_properties(XXX_static PROPERTIES OUTPUT_NAME "XXX")，这样就可以同时得到XXX.so和XXX.a两个库了。
       按照规则，动态库是应该包含一个版本号，我们可以看一下系统的动态库，一般是：   
       +  libXXX.so.1.2   
       +  libXXX.so -> libXXX.so.1   
       +  libXXX.so.1 -> libXXX.so.1.2   
       为了实现动态库版本号，我们仍然需要是用SET_TARGET_PROPERTIES指令。具体使用方式是：    
       set_target_properties(XXX PROPERTIES VERSIOn 1.2 SOVERSION 1)   
       VERSION指代动态库版本，SOVERSION指代API版本。这将生成一下：      
       +  libXXX.so.1.2   
       +  libXXX.so -> libXXX.so.1   
       +  libXXX.so.1 -> libXXX.so.1.2   
  14.  get_target_property(VAR target property)    
       这里的property和VAR相当于一个map键值对，property是键，VAR是值，这个键值对从属于target，如果这个target没有这个键，那么VAR将返回OUTPUT_VALUE-NOTFOUND.   
  15.  include_directories    
       INCLUDE_DIRECTORIES([AFTER|BEFORE] [SYSTEM] dir1 dir2 ...)   
       这条指令可以用来向工程添加多个特定的头文件搜索路径，路径之间用空格分割，如果路径中包括了空格，可以是用双引号将它括起来，默认的行为是追加到当前的头文件搜索路径的后面，你可以通过两种方式来进行控制搜索路径添加的方式：    
       +  CMAKE_INCLUDE_DIRECTORIES_BEFORE，通过SET这个cmake变量为ON，可以将添加的头文件搜索路径放在已有路径的前面。    
       +  通过AFTER或者BEFORE参数，也可以控制是追加还是置前。现在我们在src/CMakeLists.txt中添加一个头肩搜索路径，方式很简单，加入：  
          include_directories(/usr/include/hello)   


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
    25.  pck_check_modules      
        1.  [理解一](http://www.supermew.top/archives/1591)   
        2.  [理解二](https://cmake.org/cmake/help/v3.0/module/FindPkgConfig.html)   

6.  变量    
    1. [CMAKE_INSTALL_MESSAGE](https://cmake.org/cmake/help/v3.1/variable/CMAKE_INSTALL_MESSAGE.html)   
    2.  [CMAKE_CXX_STANDARD](https://kheresy.wordpress.com/2017/08/28/abi-incompatible-of-g/)    
        C++11标准   
    3.  [CXX_STANDARD_REQUIRED](https://cmake.org/cmake/help/v3.1/prop_tgt/CXX_STANDARD_REQUIRED.html)      
    4.  CMAKE_CXX_FLAGS   
        + [解释一](https://blog.csdn.net/10km/article/details/51731959)   
        + [解释二](https://www.jianshu.com/p/e9b1e9e833b2)      
    5.  [-D_GLIBCXX_USE_CXX11_ABI](https://my.oschina.net/tigerBin/blog/2049922)    
    6.  [CMAKE_EXPORT_COMPILE_COMMANDS](https://ihuifeng.cc/2019/08/10/C-C-%E7%BC%96%E7%A8%8B%E5%AE%9E%E7%8E%B0%E7%B2%BE%E5%87%86%E7%9A%84%E8%AF%AD%E4%B9%89%E7%BA%A7%E8%A1%A5%E5%85%A8/)   
    7.  [cmake默认编译、链接选项](https://blog.csdn.net/icbm/article/details/52336497)    
    8.  [ENV](https://blog.csdn.net/10km/article/details/51769633)    
    9.  [CMAKE_CURRENT_LIST_DIR](https://elloop.github.io/tools/2016-04-10/learning-cmake-2-commands)   
    10.  CMAKE_BUILD_WITH_INSTALL_RPATH以及相关    
        1.  [理解一](https://www.shuzhiduo.com/A/n2d99oQ6dD/)    
        2.  [理解二](https://blog.csdn.net/guo1988kui/article/details/81037366)   
    11.  BUILD_SHARED_LIBS   
         option(BUILD_SHARED_LIBS ON) # 默认生成动态库，如果不设置的话默认生成静态库
    12.  如果cmake构建失败，需要查看细节的话，可以是用`make VERBOSE=1`，来构建。    
    13.  ___环境变量___: CMAKE_INCLUDE_PATH和CMAKE_LIBRARY_PATH   
         需要特别注意，这两个变量不是___cmake变量___，而是___环境变量___，使用方法是要在bash中用export或者使用set命令设置或者使用CMAKE_INCLUDE_PATH=/home/...的方式。    
         这两个变量主要用来解决以前的autotools工程中--extra-include-dir等参数的支持，也就是，如果头文件没有放在常规路径中（/usr/include, /usr/local/include等等），则可以通过这些变量进行弥补。比如，假设我有个hello.h在/usr/include/hello目录中，直接查找是找不到的，可以是用include_directories(/usr/include/hello)告诉工程这个头文件目录。为了将程序更加智能，我们可以是用CMAKE_INCLUDE_PATH来进行，是用bash的方法如下：    
         export CMAKE_INCLUDE_PATH=/usr/include/hello，然后在CMakeLists.txt中将include_directories(/usr/include/hello)替换为：    
         ```
         find_path(my_header hello.h)
         if(my_header)
           include_directories(${my_header})
         endif(my_header)
         ```
         find_path(my_header NAMES hello.h PATHS /usr/include/hello)，一般这样是用，这里我们没有指定路径，但是cmake仍然可以帮我找到hello.h的存放路径，就是因为我们设置了环境变量CMAKE_INCLUDE_PATH，如果不使用find_path, CMAKE_INCLUDE_PATH变量的设置是没有作用的，你不能指望他会直接为编译器命令添加参数-I<CMAKE_INCLUDE_PATH>。同样，CMAKE_LIBRARY_PATH可以用在find_library中。   
    14.  CMAKE_BINARY_DIR, PROJECT_BINARY_DIR,_BINARY_DIR: 这三个变量内容一致，如果时内部编译，就是指的工程的顶级目录，如果时外部编译，指的就是工程编译发生的目录。    
    15.  CMAKE_SOURCE_DIR,PROJECT_SOURCE_DIR,_SOURCE_DIR: 这三个变量内容一致，都指的是工程的顶级目录。  
    16.  CMAKE_CURRENT_BINARY_DIR：外部编译时，指的是target目录，内部编译时，指的是顶级目录.    
    17.  CMAKE_CURRENT_SOURCE_DIR：CMakeList.txt所在的目录.  
    18.  CMAKE_CURRENT_SOURCE_DIR：CMakeList.txt所在的目录.  
    19.  CMAKE_CURRENT_SOURCE_DIR：CMakeList.txt所在的目录.  
    20.  CMAKE_MODULE_PATH：如果工程复杂，可能需要编写一些cmake模块-，这里通过SET指定这个变量.   
    21.  LIBRARY_OUTPUT_DIR,BINARY_OUTPUT_DIR：库和可执行的最终存放目录.   
    22.  系统信息   
         +  CMAKE_MAJOR_VERSION，CMAKE 主版本号，比如2.4.6 中的2  
         +  CMAKE_MINOR_VERSION，CMAKE 次版本号，比如2.4.6 中的4  
         +  CMAKE_PATCH_VERSION，CMAKE 补丁等级，比如2.4.6 中的6  
         +  CMAKE_SYSTEM ，系统名称，比如Linux-2.6.22, 需要在project()之后使用，否则为空。    
         +  CMAKE_SYSTEM_NAME ，不包含版本的系统名，比如Linux, 需要在project()之后使用，否则为空。    
         +  CMAKE_SYSTEM_VERSION ，系统版本，比如2.6.22  
         +  CMAKE_SYSTEM_PROCESSOR，处理器名称，比如i686   
         +  UNIX ，在所有的类UNIX平台为TRUE，包括OS X 和cygwin  
         +  WIN32 ，在所有的win32 平台为TRUE，包括cygwin  
    23.  主要的开关选项    
         +  BUILD_SHARED_LIBS, 这个开关用来控制默认的库编译方式，如果不进行设置，使用add_library 并没有指定库类型的情况下，默认编译生成的库都是静态库。如果set(BUILD_SHARED_LIBS ON) 后，默认生成的为动态库   
         +  CMAKE_C_FLAGS 设置C编译选项，也可以通过指令add_definitions() 添加   
         +  CMAKE_CXX_FLAGS 设置C++ 编译选项，也可以通过指令add_definitions() 添加   
    24.  [将build产生的exe文件和lib文件放到指定的目录中](https://blog.csdn.net/u012487272/article/details/12882283)   

    25.  [CXX_EXTENSIONS](https://stackoverflow.com/questions/38132793/how-to-control-compiler-flag-invoked-when-specifing-cmake-cxx-standard)    

7.  [另一个比较全面的博客](http://ijinjay.github.io/blog/2017-04/CMake%E4%BD%BF%E7%94%A8.html)     
8.  [一个人的博客，有些东西很好，我就摘抄下来](https://www.jianshu.com/p/1ec2b5602b03)    
    1.  [cmake语法概览](./others_blog/cmake语法速览.md)     
    2.  [cmake的优势](./others_blog/cmake优势以及为什么是用cmake.md)      
    3.  [cmake实战](./others_blog/pictures/Cmake实战指南.html)      

9.  [cmake将变量传递给代码](https://www.coder.work/article/1206996)   
10.  [在各级子项目(目录)之间共享变量](https://blog.csdn.net/10km/article/details/50508184)    
___待总结___
11.  小bug?   
     1.  install路径设置   
         cmake -DCMAKE_INSTALL_PREFIX=<> 或在CMakeLists.txt中使用SET(CMAKE_INSTALL_PREFIX <>), 需要在project()之前设置，否则无效。或者使用cmake手册中的方法，可以在project()之后设置：    
         ```
         if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
           set(CMAKE_INSTALL_PREFIX "/my/default" CACHE PATH "..." FORCE)
        endif()
        ```
     2.  [变量设置失效问题](https://wuruofan.com/2020/05/cmake-learning-note/)   
     3.  [链接动态库时是用相对路径rpath using relatived path](https://wuruofan.com/2020/05/cmake-learning-note/)    
     4.  [cmake_skip_rpath系列](https://blog.csdn.net/zhawk/article/details/77104114)   
