***this file is my learnd python3, and is addtion to [python3教程](https://www.runoob.com/python3/python3-tutorial.html)***

***[谷歌编写规格指南](https://zh-google-styleguide.readthedocs.io/en/latest/google-python-styleguide/python\_language\_rules/)***
> # Contents

> > ## 1. Class</br>
> > > ### 1.1 专有方法 </br>
> > > > #### 1.1.0 \_\_call\_\_再次理解
> > > > ```
> > > > #coding:utf-8
> > > > 
> > > > import os
> > > > 
> > > > class A:
> > > >     def __init__(self, value):
> > > >         self.num = value
> > > > 
> > > >     def f1(self):
> > > >         print("excute f1")
> > > >         self.result = [1] #虽然没有在__init__中定义，但它仍然是实例变量，只不过这个函数一定得被执行，才能创建这个实例变量，在这个程序中，因为"a()"触发了"__call__"，"__call__"又触发了f1(),所以在"a.f3()"中，能够使用self.result
> > > >     
> > > >     def f2(self):
> > > >         print("excute f2")
> > > >         self.result = [2]
> > > > 
> > > >     def f3(self):
> > > >         self()#这句话在pycharm中有解释为：covert method to attribute, 它调用了__call__；功能与"a()"是一样的
> > > >         return self.result
> > > > 
> > > >     def __call__(self):
> > > >         print(r"__call is called")
> > > >         self.f1()
> > > > 
> > > > if __name__ == "__main__":
> > > >     a = A(3)
> > > >     #a()
> > > >     a.f3()
> > > >     #print(a.result)
> > > > ```
> > > > #### 1.1.1. [\_\_call\_\_](https://www.cnblogs.com/superxuezhazha/p/5793536.html) </br>
> > > > #### 1.1.2. [\_\_getattr\_\_\/\_\_setattr\_\_\/\_\_getitem\_\_\/\_\_setitem\_\_](https://blog.csdn.net/chituozha5528/article/details/78355216) </br>
> > > > #### 1.1.3. [python类的专有方法](https://segmentfault.com/a/1190000007256392) </br>
> > > > #### 1.1.4. [\_\_file\_\_](https://www.cnblogs.com/ajaxa/p/9016475.html)</br>
> > > > #### 1.1.5. [\_\_dict\_\_](https://www.cnblogs.com/alvin2010/p/9102344.html)</br>
> > > > #### 1.1.6. [\_\_getattr\_\_](https://www.jianshu.com/p/dec562715df6)</br>
> > > > #### 1.1.7. [\_\_enter\_\_\/\_\_exit\_\_](https://www.cnblogs.com/lipijin/p/4460487.html)   
> > > > #### 1.1.8. [\_\_dict\_\_](https://www.cnblogs.com/alvin2010/p/9102344.html)     
> > > > #### 1.1.9. [\_\_name\_\_](https://www.cnblogs.com/1204guo/p/7966461.html)    

> > > ### 1.2 [MRO](https://www.cnblogs.com/ssyfj/p/9017280.html) </br>
> > > ### 1.3 [super函数](https://www.imooc.com/article/50836) </br>
> > > ### 1.4 [@property\/@staticmethod\/@classmethod](https://www.cnblogs.com/wangyongsong/p/6750454.html) </br>
> > > > #### 1.4.1 [@classmethod 的使用场合](https://blog.csdn.net/dyh4201/article/details/78336529) </br>
> > > > #### 1.4.2 [@classmethod和@staticmethod的再次理解](https://eclipsesv.com/page/2/) </br>
> > > ### 1.5 [python的下划线们](https://blog.csdn.net/lcczzu/article/details/84819587)</br>
> > > ### 1.6 [object类](https://blog.csdn.net/DeepOscar/article/details/80947155) </br>
> > > ### 1.7 [类变量和实例变量](https://www.cnblogs.com/crazyrunning/p/6945183.html) </br>
> > > > #### 1.7.1 [为什么类的变量是定义在类方法内的?](https://www.cnblogs.com/chownjy/p/8663024.html)

> > ## 2. Functions </br>
> > > ### 2.1 [重构](https://blog.csdn.net/liuwei_q/article/details/83032297)  
> > > ### 2.2 [lambda/filter/reduce/map](https://www.cnblogs.com/kaituorensheng/p/5300340.html)  
> > > ### [with](https://www.jianshu.com/p/5b01fb36fd4c) </br>
> > > ### [闭包](https://blog.csdn.net/weixin_44141532/article/details/87116038) </br>
> > > ### [yield](https://www.ibm.com/developerworks/cn/opensource/os-cn-python-yield/index.html) </br>

> > ## 3. Packages
> > > ### 3.1. [csv](https://www.cnblogs.com/wuxunyan/p/10442444.html)</br>
> > > ### 3.2. [sys.module](https://www.cnblogs.com/zhaojingyu/p/9069076.html)</br>
> > > ### 3.3. [xml解释器](https://blog.csdn.net/guangmingsky/article/details/77601225)</br>
> > > ### 3.4. [pika](https://pypi.org/project/pika/)</br>
> > > ### 3.5. [python导入包](https://blog.csdn.net/chinesepython/article/details/82113575) </br>
> > > ### 3.6. [logging](https://www.cnblogs.com/Nicholas0707/p/9021672.html) </br>
> > > ### 3.7. [shutil](https://www.jb51.net/article/145522.htm) </br>
> > > ### 3.8. [Python的常用模块](https://www.cnblogs.com/brf-test/p/11241161.html) </br>
> > > ### 3.9. [os模块](https://www.cnblogs.com/kaituorensheng/archive/2013/03/18/2965766.html) </br>
> > > ### 3.10. [pydicm](https://blog.csdn.net/linhai1028/article/details/79551488) </br>
> > > ### 3.11. [PySimpleGUI](https://linux.cn/article-10027-1.html)</br>
> > > ### 3.12. [collections](https://www.cnblogs.com/zhizhan/p/5692668.html) </br>
> > > ### 3.13. [pymysql](https://www.runoob.com/python3/python3-mysql.html) </br>
> > > ### 3.14. [multiprocessing](https://www.osgeo.cn/cpython/library/multiprocessing.html) </br>
> > > ### 3.15. [python json模块](https://www.runoob.com/python/python-json.html)</br>
> > > ### 3.16. [subprocess](https://zhuanlan.zhihu.com/p/72829009)   
> > > ### 3.17. [configparser](https://www.jianshu.com/p/2f0636e27477)    
> > > ### 3.18. [glob](https://www.jianshu.com/p/32e3364b22ee)   
> > > ### 3.19. [io.ByteIO](https://www.cnblogs.com/yqpy/p/8556090.html)   
> > > ### 3.20. [re](https://docs.python.org/zh-cn/3/library/re.html)    



> > ## 4. Common Functions
> > > ### 4.1.1. [time的相关函数](https://blog.csdn.net/brucewong0516/article/details/79044905)</br>
> > > ### 4.1.2. [copy && copy.deepcopy](https://blog.csdn.net/u010712012/article/details/79754132) </br>
> > > ### 4.1.3. [\_\_import\_\_和import比较](https://blog.csdn.net/weixin_42670402/article/details/83472429) </br>
> > > ### 4.1.4. import  
> > > > #### 4.1.4.1 [第一个理解](http://sinhub.cn/2019/05/python-import-machinery-part-one/)    
> > > > #### 4.1.4.2 [第二个理解](https://blog.csdn.net/weixin_38256474/article/details/81228492)   
> > > > 我得出的结果：  
> > > > import A.B.C：此时只会在当前文件的命名空间中导入A的module，其他的不会导入    
> > > > 但是import A.B.C as D:此时只有D这么一个module，连A也没有   
> > > > from A.B import C:此时命名空间只有Cimport A.B.C：此时只会在当前文件的命名空间中导入A的module，其他的不会导入   
> > > > 但是import A.B.C as D:此时只有D这么一个module，连A也没有   
> > > > from A.B import C:此时命名空间只有C   

> > ## 5. 异常</br>
> > > ### 5.1. [基本理解](https://www.jianshu.com/p/66e2e4104e7c)


> > ## 6. 杂项 </br>
> > > ### 6.1 [环境变量](https://blog.csdn.net/v_xchen_v/article/details/80393967) </br>
> > > ### 6.2 [Python字符串前面加u,r,b的含义](https://www.cnblogs.com/liangmingshen/p/9274021.html)
> > > ### 6.3 [python的\*](https://www.cnblogs.com/jony7/p/8035376.html)
> > > ### 6.4 [基本类型]   
> > > > #### 6.4.1. [list]   
> > > > > ##### 6.4.1.1. [\[list::\]](https://blog.csdn.net/qq\_41940950/article/details/80765674)   
> > > ### 6.5 [一些包的特殊用法]
> > > > #### 6.5.1 [matplotlib.plot画多张图，在一张图上画多个函数](https://blog.csdn.net/haikuotiankong7/article/details/90551841)    
