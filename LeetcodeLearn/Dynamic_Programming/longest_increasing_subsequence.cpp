// reference: https://leetcode-cn.com/problems/longest-increasing-subsequence/

/*! \brief get longest increasing subsequence
 *  从最终的结果考虑：需要求的时最长的子序列的长度
 *  状态: 以当前的值作为子序列的结尾值，求最长递增子序列的长度
 *  dp函数：每增加一个元素，它可以得到当前最长子序列的长度
 *  递归的终止条件
 *  备忘录模式，记录递归的结果
 *  base case: dp_table[0] = 1
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

class Solution {
public:
  // recursion mode
  int dp_recursion(const vector<int>& nums, int last_max, int cur);

  // memo mode
  int dp_memo(const vector<int>& nums, vector<vector<int>>& length, int prev, int cur);

  // dp function mode
  int dp_func(const vector<int>& nums);

  int lengthOfLIS(vector<int>& nums);
};

int Solution::dp_func(const vector<int>& nums)
{
  vector<int> max_length(nums.size(), 0);

  max_length[0] = nums[0];
  for (int i = 1; i < nums.size(); ++i) {
    for(int j = 0; j < i; ++j) {
      if (nums[j] < nums[i])
        max_length[i] = std::max(max_length[j]+1, max_length[i]);
    } 
  } 

  return *(std::max_element(max_length.begin(), max_length.end()));
}

int Solution::dp_memo(const vector<int>& nums, vector<vector<int>>& max_length, int prev, int cur)
{
  if (cur == nums.size())
    return 0;

  if (max_length[prev+1][cur] > 0)
    return max_length[prev+1][cur];

  // prev < 0 || nums[prev] < nums[cur]
  int a = 0;
  if (prev < 0 || nums[prev] < nums[cur])
    a = dp_recursion(nums, cur, cur+1) + 1;

  // prev < 0 || nums[prev] < nums[cur] || nums[prev] >= nums[cur]
  int b = dp_recursion(nums, prev, cur+1);

  // nums[prev] > nums[cur], 这种情况不能要，因为以cur为最大点，要去除掉之前的长度值, 而这种情况可以用前述的代码包含进去
  // int c = dp_recursion(nums, cur, cur+1);

  max_length[prev+1][cur] = std::max(a, b);
  return max_length[prev+1][cur];
}

int Solution::dp_recursion(const vector<int>& nums, int prev, int cur)
{
  if (cur == nums.size())
    return 0;

  // prev < 0 || nums[prev] < nums[cur]
  int a = 0;
  if (prev < 0 || nums[prev] < nums[cur])
    a = dp_recursion(nums, cur, cur+1) + 1;

  // prev < 0 || nums[prev] < nums[cur] || nums[prev] >= nums[cur]
  int b = dp_recursion(nums, prev, cur+1);

  // nums[prev] > nums[cur], 这种情况不能要，因为以cur为最大点，要去除掉之前的长度值, 而这种情况可以用前述的代码包含进去
  // int c = dp_recursion(nums, cur, cur+1);

  return std::max(a, b);
}

int Solution::lengthOfLIS(vector<int>& nums)
{
  if (nums.empty())
    return 0;

  if (nums.size() == 1)
    return 1;

  // recursion
  // return dp_recursion(nums, -1, 0);

  // memo
  // vector<vector<int>> max_length(nums.size()+1, vector<int>(nums.size(), 0));
  // return dp_memo(nums, max_length, -1, 0);

  // dp function
  return dp_func(nums);
}

int main()
{
  // case 1
  // vector<int> nums = { 0, 1, 0, 3, 2, 3 };

  // case 2
  // vector<int> nums = { 10, 9, 2, 5, 3, 7, 101, 18 };

  // case 3
  // vector<int> nums = { 7, 7, 7, 7 };

  // case 4
  // vector<int> nums = { 4, 10, 4, 3, 8, 9 };

  // case 5
  vector<int> nums = { 1, 10, 2, 3 };


  Solution s;
  std::cout << s.lengthOfLIS(nums) << std::endl;

  return 0;
}
