___just for dynamic_Programming___

[参考](https://github.com/chezhai/fucking-algorithm/blob/master/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E7%B3%BB%E5%88%97/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E8%AF%A6%E8%A7%A3%E8%BF%9B%E9%98%B6.md)     
[最优子结构](https://github.com/chezhai/fucking-algorithm/blob/master/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E7%B3%BB%E5%88%97/%E6%9C%80%E4%BC%98%E5%AD%90%E7%BB%93%E6%9E%84.md)      
[数学归纳法](https://bbs.huaweicloud.com/blogs/193893)      

+ 总结   
  1.  动态规划三个要素：重叠子问题、最优子结构、状态转移方程      
  2.  关键：确定状态 -> 确定dp函数的意义 -> 选择（选择修改状态），并且择优 -> base case。   
  3.  具体步骤：先是用暴力递归求解，然后分析重叠子问题，若有则是用备忘录方式修改递归。然后自下而上写出动态规划。    
  4.  使用数学归纳法得到状态转移方程。      
  5.  一段代码    
      ```
      dp[0][0]... = base case;
      for state_1 in state0:
        for state_2 in state2:
          ...
          dp[state0][state1]... = 最优解，一般是min(), max()
      ```
  6.  写完动态规划，可以考虑一下状态压缩

  7.  目前发现有些能够是用暴力递归先解问题，然后是用备忘录方式再写，然后再写动态规划。比如[凑零钱问题](./coin_cnage.cpp)。但是有些问题不能用暴力递归的方式去解，最起码我没有找到（也没时间找），所以只需要判断: 1. 是否有最优子结构。2. 找到状态。  3. 确定dp函数的意义。4. 选择&择优。5. base case。比如[找到最长的递增子序列](./longest_increasing_subsequence.cpp)。     
