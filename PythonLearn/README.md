***this file is my learnd python3, and is addtion to [python3教程](https://www.runoob.com/python3/python3-tutorial.html)***

***[谷歌编写规格指南](https://zh-google-styleguide.readthedocs.io/en/latest/google-python-styleguide/python\_language\_rules/)***



# Contents

## 1. Class</br>
### 1.1 专有方法 </br>
1.  \_\_call\_\_再次理解

    ```
    #coding:utf-8

    import os

    class A:
        def __init__(self, value):
            self.num = value

        def f1(self):
            print("excute f1")
            self.result = [1] #虽然没有在__init__中定义，但它仍然是实例变量，只不过这个函数一定得被执行，才能创建这个实例变量，在这个程序中，因为"a()"触发了"__call__"，"__call__"又触发了f1(),所以在"a.f3()"中，能够使用self.result
        
        def f2(self):
            print("excute f2")
            self.result = [2]

        def f3(self):
            self()#这句话在pycharm中有解释为：covert method to attribute, 它调用了__call__；功能与"a()"是一样的
            return self.result

        def __call__(self):
            print(r"__call is called")
            self.f1()

    if __name__ == "__main__":
        a = A(3)
        #a()
        a.f3()
        #print(a.result)
    ```

2.  [\_\_call\_\_](https://www.cnblogs.com/superxuezhazha/p/5793536.html) </br>
3.  [\_\_getattr\_\_\/\_\_setattr\_\_\/\_\_getitem\_\_\/\_\_setitem\_\_](https://blog.csdn.net/chituozha5528/article/details/78355216) </br>
4.  [python类的专有方法](https://segmentfault.com/a/1190000007256392) </br>
0.  [python类的魔术方法](https://pyzh.readthedocs.io/en/latest/python-magic-methods-guide.html)   
5.  [\_\_file\_\_](https://www.cnblogs.com/ajaxa/p/9016475.html)</br>
6.  [\_\_dict\_\_](https://www.cnblogs.com/alvin2010/p/9102344.html)</br>
7.  [\_\_getattr\_\_](https://www.jianshu.com/p/dec562715df6)</br>
9.  [\_\_enter\_\_\/\_\_exit\_\_](https://www.cnblogs.com/lipijin/p/4460487.html)   
1.  [\_\_dict\_\_](https://www.cnblogs.https://www.cnblogs.com/lipijin/p/4460487.html)  
2.  [\_\_dict\_\_](https://www.cnblogs.com/alvin2010/p/9102344.html)  
3.  [\_\_name\_\_](https://www.cnblogs.com/1204guo/p/7966461.html)  
4.  [\_\_glob\_\_](https://www.jianshu.com/p/32e3364b22ee)   
5.  [\_\_del\_\_](http://c.biancheng.net/view/2371.html)
6.  [\_\_getitem\_\_](__https://zhuanlan.zhihu.com/p/27661382)   

### 1.2 [MRO](https://www.cnblogs.com/ssyfj/p/9017280.html) </br>
### 1.3 [super函数](https://www.imooc.com/article/50836) </br>
### 1.4 [@property\/@staticmethod\/@classmethod](https://www.cnblogs.com/wangyongsong/p/6750454.html)   
1.  [@classmethod 的使用场合](https://blog.csdn.net/dyh4201/article/details/78336529) </br>
2.  [@classmethod和@staticmethod的再次理解](https://eclipsesv.com/page/2/) </br>
3.  [class method vs static method](http://net-informations.com/python/iq/method.htm)   
### 1.5 [python的下划线们](https://blog.csdn.net/lcczzu/article/details/84819587)</br>
### 1.6 [object类](https://blog.csdn.net/DeepOscar/article/details/80947155) </br>
### 1.7 [类变量和实例变量](https://www.cnblogs.com/crazyrunning/p/6945183.html) </br>
1.  [为什么类的变量是定义在类方法内的?](https://www.cnblogs.com/chownjy/p/8663024.html)
### 1.8 [python 包、模块的区别](https://blog.csdn.net/ityard/article/details/103502449)   
### 1.9 [python的protected](https://blog.csdn.net/c_base_jin/article/details/88778553)   
### 2.0 [python的搜索路径](https://blog.csdn.net/Charles5101/article/details/89951747)    
### 2.1 [@dataclass](https://toutiao.io/posts/fvnzri/preview)   
### 2.2 [python的self/cls](https://www.cnblogs.com/kex1n/p/5983200.html)    
### 2.3 [python的类变量之与C++不一样](https://www.jianshu.com/p/3aca78a84def)   

## 2. Functions </br>
1.  [重构](https://blog.csdn.net/liuwei_q/article/details/83032297)
2.  [lambda/filter/reduce/map](https://www.cnblogs.com/kaituorensheng/p/5300340.html)  
3.  [with](https://www.jianshu.com/p/5b01fb36fd4c) </br>
4.  [闭包](https://blog.csdn.net/weixin_44141532/article/details/87116038)
    1.  [理解二](https://www.zhihu.com/question/25950466)
5.  [yield](https://www.ibm.com/developerworks/cn/opensource/os-cn-python-yield/index.html) </br>
6.  [del](https://blog.csdn.net/weihongxu2222/article/details/51320006)   
7.  [iter](https://docs.python.org/zh-cn/3/library/functions.html)   
8.  [python 生成器、列表/字典/集合解析式区别](https://blog.csdn.net/luckytanggu/article/details/53154063)   
9.  [装饰器简述](https://www.runoob.com/w3cnote/python-func-decorators.html)    
10.  [python函数传递参数是传引用还是传值？](https://blog.csdn.net/duan20140614/article/details/85382955)    
11.  [函数参数中的冒号, 箭头](https://blog.csdn.net/qq_31347869/article/details/102401971)    

## 3. Packages
### 3.1. [csv](https://www.cnblogs.com/wuxunyan/p/10442444.html)</br>
### 3.2. [sys模块](http://www.ityouknow.com/python/2019/10/09/python-sys-demonstration-028.html)          
  1.  [sys.module](https://www.cnblogs.com/zhaojingyu/p/9069076.html)
  2.  [sys.argv](https://www.cnblogs.com/aland-1415/p/6613449.html)     
  3.  [sys.exit()/os.exit()](https://blog.csdn.net/index20001/article/details/74294945)     
### 3.3.  [xml结构树](https://www.runoob.com/xml/xml-tree.html)   
1.  [是用ElementTree解析xml]( https://www.runoob.com/xml/xml-tree.html)   
2.  [再解](https://blog.csdn.net/wolinghuanyun/article/details/52474515)   
### 3.4. [pika](https://pypi.org/project/pika/)</br>
### 3.5. [python导入包](https://blog.csdn.net/chinesepython/article/details/82113575) </br>
### 3.6. [logging](https://www.cnblogs.com/Nicholas0707/p/9021672.html) </br>
### 3.7. [shutil](https://www.jb51.net/article/145522.htm) </br>
### 3.8. [Python的常用模块](https://www.cnblogs.com/brf-test/p/11241161.html) </br>
### 3.9. [os模块](https://www.cnblogs.com/kaituorensheng/archive/2013/03/18/2965766.html) </br>
1.  [os.path](https://www.jianshu.com/p/cfa219ff0791?utm_campaign=maleskine&utm_content=note&utm_medium=seo_notes&utm_source=recommendation)     
2.  [os.path.realpath(__file__)和os.path.cwd()的区别](https://blog.csdn.net/cityzenoldwang/article/details/78448039)    
3.  os.getenv   
    看源代码可以发现，如果key在环境变量里面，返回key在环境变量里面的值，如果不存在，则返回default。     
### 3.10. [pydicm](https://blog.csdn.net/linhai1028/article/details/79551488) </br>
### 3.11. [PySimpleGUI](https://linux.cn/article-10027-1.html)</br>
### 3.12. [collections](https://www.cnblogs.com/zhizhan/p/5692668.html) </br>
### 3.13. [pymysql](https://www.runoob.com/python3/python3-mysql.html) </br>
### 3.14. [multiprocessing](https://www.osgeo.cn/cpython/library/multiprocessing.html) </br>
### 3.15. [python json模块](https://www.runoob.com/python/python-json.html)</br>
### 3.16. [subprocess](https://zhuanlan.zhihu.com/p/72829009)   
1.  [check_out()](https://python3-cookbook.readthedocs.io/zh_CN/latest/c13/p06_executing_external_command_and_get_its_output.html)      
### 3.17. [configparser](https://www.jianshu.com/p/2f0636e27477)    
### 3.18. [glob](https://www.jianshu.com/p/32e3364b22ee)   
### 3.19. [io.ByteIO](https://www.cnblogs.com/yqpy/p/8556090.html)   
### 3.20. [re手册](https://docs.python.org/zh-cn/3/library/re.html)    
1.  [博客版本](https://www.cnblogs.com/huxi/archive/2010/07/04/1771073.html)  
### 3.21. [argparse](http://blog.xiayf.cn/2013/03/30/argparse/)     
### 3.22. [configparser](https://www.jianshu.com/p/2f0636e27477)        
### 3.23. [ctypes](https://cloud.tencent.com/developer/section/1370537#stage      -100049081)
### 3.24. [bututils](https://www.osgeo.cn/cpython/distutils/apiref.html)    
### 3.25. [__future__](https://segmentfault.com/a/1190000010857744)       
### 3.26.  [openpyxl](https://geek-docs.com/python/python-tutorial/python-openpyxl.html)      
### 3.27.  [importlib](https://www.cnblogs.com/zhbzz2007/p/6715516.html)    
### 3.28  numpy   
1.  [np.stack](https://blog.csdn.net/csdn15698845876/article/details/73380803)    
2.  [numpy广播机制](https://www.cnblogs.com/jiaxin359/p/9021726.html)   
3.  [np.newaxis](https://www.jb51.net/article/144967.htm)   
4.  [numpy中的np.max 与 np.maximum区别](https://blog.csdn.net/CSDN5529/article/details/79038544)    
5.  [numpy.concatenate](https://www.cnblogs.com/shueixue/p/10953699.html)      
6.  [numpy的prod()函数和pad()函数](https://www.cnblogs.com/nxf-rabbit75/p/10044403.html)    
7.  [all（）和any（）比较矩阵](https://blog.csdn.net/qq_28618765/article/details/78086478)     
8.  [numpy.argmax](https://www.cnblogs.com/zhouyang209117/p/6512302.html)   
9.  [np.random.choice的用法](https://blog.csdn.net/qfpkzheng/article/details/79061601)     
10. [numpy.loadtxts](https://blog.csdn.net/yu_1628060739/article/details/102746114)   
11. [numpy数组的取整以及类型转换：ceil, floor, trunc, rint, around]( https://blog.csdn.net/sinat_34072381/article/details/84567523)   
### 3.29  [tqdm](https://www.cnblogs.com/q735613050/p/10127531.html)    
### 3.30  easydict(公司拿来当作pytorch的训练配置文件用)     

## 4. Common Functions
1.  [time的相关函数](https://blog.csdn.net/brucewong0516/article/details/79044905)</br>
2.  [copy && copy.deepcopy](https://blog.csdn.net/u010712012/article/details/79754132) </br>
3.  [\_\_import\_\_和import比较](https://blog.csdn.net/weixin_42670402/article/details/83472429) </br>
4.  import  
    1.  [第一个理解](http://sinhub.cn/2019/05/python-import-machinery-part-one/)    
    2.  [第二个理解](https://blog.csdn.net/weixin\_38256474/article/details/81228492)   
    > 我得出的结果：  
    > import A.B.C：此时只会在当前文件的命名空间中导入A的module，其他的不会导入    
    > 但是import A.B.C as D:此时只有D这么一个module，连A也没有   
    > from A.B import C:此时命名空间只有Cimport A.B.C：此时只会在当前文件的命名空间中导入A的module，其他的不会导入   
    > 但是import A.B.C as D:此时只有D这么一个module，连A也没有   
    > from A.B import C:此时命名空间只有C   
5.  [globals()](https://www.runoob.com/python/python-func-globals.html)     

## 5. 异常</br>
### 5.1. [基本理解](https://www.jianshu.com/p/66e2e4104e7c)


## 6. 杂项 </br>
### 6.1. [环境变量](https://blog.csdn.net/v_xchen_v/article/details/80393967) </br>
1.  [python的搜索路径](https://blog.csdn.net/Charles5101/article/details/89951747)    
### 6.2. [Python字符串前面加u,r,b的含义](https://www.cnblogs.com/liangmingshen/p/9274021.html)     
### 6.3. [python的\*](https://www.cnblogs.com/jony7/p/8035376.html)    
### 6.4. 基本类型      
1.  [list]   
    1. [\[list::\]](https://blog.csdn.net/qq\_41940950/article/details/80765674)   
2.  [enum](https://www.cnblogs.com/ucos/p/5896861.html)   
### 6.5. 一些包的特殊用法
1.  [matplotlib.plot画多张图，在一张图上画多个函数](https://blog.csdn.net/haikuotiankong7/article/details/90551841)    
2.  [matplotlib.plot的颜色和线条、线条的形状](https://www.cnblogs.com/zoe-chang/p/11269780.html)    
### 6.6. pyton编码
1.  [python编码的第一个解释](https://www.cnblogs.com/jessonluo/p/4801580.html)
2.  [pyhon编码的第二个解释](https://www.cnblogs.com/busui/p/9340339.html)
3.  [str.encode()](http://c.biancheng.net/view/4305.html) 
### 6.7. python的理解
1.  python的对象是引用  
    1.  [解释](https://blog.csdn.net/weihongxu2222/article/details/51320006)  
    2.  [Python中的变量、引用、拷贝和作用域](https://blog.csdn.net/li_101357/article/details/52745661)    
2.  [iterable和iterator](https://zhuanlan.zhihu.com/p/32162554)   
3.  [python程序怎么执行的?](https://www.jianshu.com/p/03af86845c95)   
4.  [module和包的区别](https://www.cnblogs.com/JetpropelledSnake/p/8905727.html)    
5.  [python setup.py](http://blog.konghy.cn/2018/04/29/setup-dot-py/)   
    1.  [python打包分发工具setuptools](http://www.bjhee.com/setuptools.html)    
    2.  [另一个版本的setuptools](https://segmentfault.com/a/1190000017037354)     
6.  [python os.environ](http://www.shuang0420.com/2017/03/10/Python%20os.environ.get()%20return%20None/)
7.  [可变对象和不可变对象]( https://blog.csdn.net/liuweiyuxiang/article/details/89349862)     
### 6.8. [Python PEP8 代码规范常见问题及解决方法](https://cloud.tencent.com/developer/article/1611332)    
8.  [50个Ipython的使用技巧](https://www.zhihu.com/question/405701348/answer/1326466804?utm_source=wechat_session&utm_medium=social&utm_oi=1139653771880796160)    
