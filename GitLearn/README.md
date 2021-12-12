***a file for learning git command, and is a addtion to '[git教程](https://www.runoob.com/git/git-tutorial.html)'***

***more information can get from [AXIHE](https://www.axihe.com/markdown-deu/markdown-hello/markdown-tutorial.html)***

***another [online tool](http://mahua.jser.me/)***

___a web can learn git command liking [playing game](https://learngitbranching.js.org/?locale=zh_CN).___

# <p align="center"> Catalogs </p> 



# <p align="center"> Contents </p>

[解决github网络慢](https://blog.csdn.net/ITleaks/article/details/80351680)      

![alt github命令总结图](./pictures/git命令.jpg)</br> 

1.  git命令参考网站</br> 
    +  [菜鸟教程](https://www.runoob.com/git/git-tutorial.html)</br>
    +  [参考网站1](https://www.jianshu.com/p/93318220cdce)</br>
    +  [参考网站2](https://www.imooc.com/article/2733)</br>
2.  git的一些命令详解   
    1.  [git push](https://blog.csdn.net/hobhunter/article/details/79463168)   
    2.  [git remote](https://www.cnblogs.com/irocker/p/git-remote.html)  
        1. [git remote set-url](https://blog.csdn.net/lamp_yang_3533/article/details/80379246)   
    3.  [git删除本地仓库](https://www.cnblogs.com/zgcr654321/p/9655543.html)   
    4.  [git commit](https://www.cnblogs.com/qianqiannian/p/6005628.html)   
    5.  [git fetch](https://www.cnblogs.com/chenlogin/p/6592228.html)   
    6.  [markdown](https://www.runoob.com/markdown/md-tutorial.html)          
        1.  [markdown画各种图](https://blog.csdn.net/lis_12/article/details/80693975)   
        2.  [markdown待办事项](https://blog.csdn.net/qq_21808961/article/details/83239631)      
    7.  What i found   
        1.  center/right/left  

            ```
            <p align="center"> chezhai </p>
            <p align="right"> chezhai </p>
            <p align="left"> chezhai </p>
            ```     

        2.  换行   
结尾用两个空格或者使用`</br>`   
    8.  [锚点](https://my.oschina.net/antsky/blog/1475173?utm\_medium=referral)   
        1.  自主添加锚点  

            ```
            先定义一个锚点(id),并显示"Hello World"
            <span id="jump">Hello World</span>
            然后使用markdown的语法
            [XXXX](#jump)
            ```   

    9.  [github中markdown中使用lex公式](https://www.jianshu.com/p/25f0139637b7)\/[补充](https://www.zybuluo.com/codeep/note/163962#1%E5%A6%82%E4%BD%95%E8%BE%93%E5%85%A5%E4%B8%80%E4%B8%AA%E6%96%B9%E7%A8%8B%E5%BC%8F%E5%BA%8F%E5%88%97)    
    0.  [GitHub中给公式加编号，加完编号后引用](https://blog.csdn.net/Mage\_EE/article/details/75331889)   
        1.  第一种    

            $$
            \begin{equation}
            E=mc^2 \text{，自动编号公式示例}
            \label{eq:Sample}
            \end{equation}
            $$

            在公式 \eqref{eq:Sample} 中，我们看到了这个被自动编号的公式。  
        2.  第二种   

            $$
            E=mc^2 \tag{3.2}\label{3.2}
            $$
            在公式 \eqref{3.2} 中，我们看到了这个被自动编号的公式。</br>

        3.  第三种   

             $$
             \begin{split}
             E=mc^2 \text{自动编号公式示例} \\\\ 
             E=mc^2 \text{自动编号公式示例} \\\\
             E=mc^2 \text{自动编号公式示例} \\\\
             E=mc^2 \text{自动编号公式示例} \\\\
             E=mc^2 \text{自动编号公式示例} \\\\
             E=mc^2 \text{自动编号公式示例}
             \end{split}\tag{3.3}\label{3.3}
             $$

            在公式 \eqref{3.3} 中，我们看到了这个被自动编号的公式。</br>

    1.  [git diff](https://www.cnblogs.com/qianqiannian/p/6010219.html)   
    2.  [git rm](https://www.cnblogs.com/everfight/p/git\_rm\_usage.html)   
        1. [删除远程仓库中的文件或者文件夹](https://blog.csdn.net/qq_31267183/article/details/86287057)   
    3.  [分支](https://git-scm.com/book/zh/v1/Git-%E5%88%86%E6%94%AF)   
    4.  [git reset](https://blog.csdn.net/y491887095/article/details/79486328)
    5.  [git submodule](https://segmentfault.com/a/1190000020297996?utm\_source=tag-newest)  
        1.  [再解](https://blog.phpgao.com/git_submodule.html)    
    6.  [git rebase](http://jartto.wang/2018/12/11/git-rebase/)   
    7.  [git的HEAD](https://www.jianshu.com/p/4419f6a76005)   
        0.  [git的相对引用](https://blog.csdn.net/m0_38022029/article/details/79058105)   
        1.  [移动HEAD指针](https://blog.csdn.net/claroja/article/details/78857853)    
        2.  [git 理解 Head指针&Branch指针](https://blog.csdn.net/claroja/article/details/78858533)    
    8.  [重命名远程分支](https://blog.csdn.net/u013276277/article/details/81975713)   
    9.  [git tag](https://blog.csdn.net/b735098742/article/details/78935748)    
    10.  [重新配置ssh-key，也解决fatal: Could not read from remote repository问题](https://blog.csdn.net/weixin_40922744/article/details/107576748)     
    11.  [git速度](https://www.codeprj.com/blog/aacfe41.html)     
         1.  git速度     
         2.  将http  /  https 换成git      
         3.  再不行只能找国内的替代网站了，比如gitee     
    12.  [git 记录账号密码](https://blog.csdn.net/zhengqijun_/article/details/63298202)     

    13.  commit 对应的时一棵树，这棵树对应的是当时整个功能的快照      
    14.  `git commit --amend` 能够修复最近一次的提交注释，修复非最近一次的提交注释使用的是 `git rebase`   
