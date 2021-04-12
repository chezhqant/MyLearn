___just for dynamic_Programming___

[参考](https://github.com/chezhai/fucking-algorithm/blob/master/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E7%B3%BB%E5%88%97/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E8%AF%A6%E8%A7%A3%E8%BF%9B%E9%98%B6.md)     
[最优子结构](https://github.com/chezhai/fucking-algorithm/blob/master/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E7%B3%BB%E5%88%97/%E6%9C%80%E4%BC%98%E5%AD%90%E7%BB%93%E6%9E%84.md)      
[数学归纳法](https://bbs.huaweicloud.com/blogs/193893)      

+ 总结   
  1.  动态规划三个要素：重叠子问题、最优子结构、状态转移方程      
  2.  关键：确定状态 -> 确定dp函数的意义 -> 选择（选择修改状态），并且择优 -> base case。   
  3.  具体步骤：先是用暴力递归求解，然后分析重叠子问题，若有则是用备忘录方式修改递归。然后自下而上写出动态规划。    
  4.  使用数学归纳法得到状态转移方程。      
  5.  <span id="jump1">一段代码<span>    
      ```
      dp[0][0]... = base case;
      for state_1 in state0:
        for state_2 in state2:
          ...
          dp[state0][state1]... = 最优解，一般是min(), max()
      ```
  
  
lsdf  
  
  
jasdklf  
jlsd  
jas;df  
j  
asdfjlasdf  
asdfjlasdfaf  
ajsdfljasf  
asdfjlaksdf  
asdfjasdkfa  
sdfjasldfkasd  
fajsdfkasdf  
asjdfkasdf  
sdjflkasdf  
asdfjaklsdf  
asdfjalksdfa  
sdfkjasldfjasd  
fasdjfklasdf  
asdjflkasdf  
asdfjkasdf  
asdfjaklsdfa  
sdfjaksldfasd  
fajsdkfasdf  
'asdjfklasdfasdkjlfajfd  
dfjalsdf  
sdfjalksdf  
sdfajsdkfasdf  
asdjfklasdf  
asdfjkalsdfa  
'sdfjklasdf  
asdfjlkasdfasdflkjasfd  
fjalksdf  
dsfjkasdfuqwe  
jwdkfqwenmsdf  
jaskdfasd  
qwejrkqwjer  
dsjfkajsdf  
asdfjakdsfw  
erjkewqr  

  6.  写完动态规划，可以考虑一下状态压缩    
  7.  我根据几道题总结的：    
      1.  先暴力递归，以最终结果为起点考虑。    
      2.  状态呢，就是驱动最终结果累计的存在    
      3.  每一步的递归都是当前状态的最优解（最优子结构, dp函数）。    
      4.  递归呢，要有终止条件。    
      5.  备忘录模式就是保存每次递归的结果，以便后面查询，而不是重复计算，要记得修改终止条件哦（重叠子问题）    
      6.  base case就是初始情况。   
      7.  按照[此位置](#jump1)，的方式去实现动态规划即可。    
