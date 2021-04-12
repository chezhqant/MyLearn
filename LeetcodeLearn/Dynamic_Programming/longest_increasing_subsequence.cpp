// reference: https://leetcode-cn.com/problems/longest-increasing-subsequence/

/*! \brief get longest increasing subsequence
 *  状态：子序列的长度（不是递增子序列的长度，而是给定的数列从0-size的长度）
 *  dp函数：每增加一个元素，它可以得到当前最长子序列的长度
 *  选择&择优：判断当前增加的元素是否会使递增子序列的长度变长
 *  base case: dp_table[0] = 1
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

class Solution {
public:
  // dp func mode
  int dp_func(const vector<int>& nums, int index, vector<int>& subsequence);

  int lengthOfLIS(vector<int>& nums);
};

int Solution::dp_func(const vector<int>& nums, int index, vector<int>& subsequence)
{
  auto found_iter = std::lower_bound(subsequence.begin(), subsequence.end(), nums[index]);

  if (found_iter != subsequence.end()) {
    int found_pos = found_iter - subsequence.begin();
    subsequence[found_pos] = nums[index];
  } else {
    subsequence.push_back(nums[index]);
  }

  return subsequence.size();
}

int Solution::lengthOfLIS(vector<int>& nums)
{
  if (nums.empty())
    return 0;

  if (nums.size() == 1)
    return 1;

  vector<int> subsequence{nums[0]};
  int length = 1;
  for (int i = 1; i < nums.size(); ++i)
    length = dp_func(nums, i, subsequence); 

  return length;
}

int main()
{
  // case 1
  // vector<int> nums = { 0, 1, 0, 3, 2, 3 };

  // case 2
  // vector<int> nums = { 10, 9, 2, 5, 3, 7, 101, 18 };

  // case 3
  vector<int> nums = { 7, 7, 7, 7 };

  Solution s;
  std::cout << s.lengthOfLIS(nums) << std::endl;

  return 0;
}
