___this file is for learning design patterns___   


1.  [设计模式](https://www.cnblogs.com/5iedu/category/825371.html)    
    + [PIMPL](https://zhuanlan.zhihu.com/p/76975231?utm_source=wechat_session&utm_medium=social&utm_oi=1139653771880796160&utm_campaign=shareopn)     
    + [原型设计模式与拷贝构造函数](https://www.zhihu.com/question/52610176)     
2.  [另一个版本的设计模式](https://www.cnblogs.com/WindSun/p/10223126.html)   
3.  [基础流程图，目前来说是够用了](https://www.cnblogs.com/ywqu/category/223486.html)   
4.  [pimpl，这样写隐藏接口的实现细节](https://zhuanlan.zhihu.com/p/264820635?utm_source=wechat_session&utm_medium=social&utm_oi=1139653771880796160&utm_campaign=shareopn)      
5.  [curiously recurring template pattern](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern)      

### 原则      
1.  SOLID原则、迪米特原则（最少知识原则）、KISS原则、YAGNI原则、DRY原则      
    + ___能让新手看懂的代码，才是好代码!!!___
    + __单一职责原则__  函数、模块等功能单一，重点是功能       
    + __开闭原则__  对扩展开放、对修改关闭      
    + __里氏替换原则__  所有用到父类的地方，都可以直接、简单的替换为子类，衍生出来 -> 宽入严出      
    + __接口隔离原则__  对外暴露越少越好，重点是依赖，一个模块依赖另一个模块越少越好; 依赖的某个功能点中的实现不应该包含冗余的功能，所以它可以帮忙审视单一职责        
    + __依赖倒置原则__  依赖抽象、依赖接口编程，不依赖具体编程      
    + __KISS原则__  Keep It Simple,Stupid，分解->短小精悍的实现     
    + __YAGNI原则__  You Ain't Gonna Need It，不需要的就别做，做得越多错的越多      
    + __DRY原则__  有重复的就抽取，当然有些只是相似，不是重复！     
