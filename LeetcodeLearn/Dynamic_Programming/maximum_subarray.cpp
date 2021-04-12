// reference: https://leetcode-cn.com/problems/maximum-subarray/

/*! \brief get maximum subarray
 *  状态：sum
 *  dp函数: 遍历每个元素，每个元素加到上一次的sum会有一个temp_sum，与sum比较
 *  选择&择优：重点在于择优，是怎么个择优的办法
 *  base case: max_sum = nums[0]
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

class Solution {
public:

  // dp function mode
  int dp_func(const vector<int>& nums, vector<int>& dp_table);

  // compress state
  int dp_func(const vector<int>& nums);

  int maxSubArray(vector<int>& nums);
};

int Solution::dp_func(const vector<int>& nums, vector<int>& dp_table)
{
  int max_sum = nums[0];
  for (int i = 1; i < nums.size(); ++i) {
    dp_table[i] = std::max(dp_table[i-1]+nums[i], nums[i]);
    max_sum = std::max(dp_table[i], max_sum);
  }

  return max_sum;
}

int Solution::dp_func(const vector<int>& nums)
{
  int max_sum = nums[0];
  int dp_max_sum = nums[0];
  for (int i = 1; i < nums.size(); ++i) {
    dp_max_sum = std::max(dp_max_sum+nums[i], nums[i]);
    max_sum = std::max(dp_max_sum, max_sum);
  }

  return max_sum;
}

int Solution::maxSubArray(vector<int>& nums)
{
  if (nums.empty())
    return 0;

  if (nums.size() == 1)
    return nums[0];

  // classic dp
  // vector<int> dp_table(nums.size(), 0);
  // dp_table[0] = nums[0];
  // return dp_func(nums, dp_table);

  // compress state
  return dp_func(nums);

}

int main()
{
  // case 1
  // vector<int> nums = { 1 };

  // case 2
  vector<int> nums = { 5, 4, -1, 7, 8 };

  // case 3
  // vector<int> nums = { -2, 1, -3, 4, -1, 2, 1, -5, -4 };

  Solution s;

  std::cout << s.maxSubArray(nums) << std::endl;

  return 0;
}
