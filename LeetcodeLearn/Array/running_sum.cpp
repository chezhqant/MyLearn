#include <iostream>
#include <vector>

// reference: https://leetcode-cn.com/problems/running-sum-of-1d-array/

class Solution {
public:
  std::vector<int> runningSum(std::vector<int>& nums) {
    if (nums.empty())
      return std::vector<int>();

    std::vector<int> ret(nums.size(), 0);
    int sum = 0;
    for (int i=0; i<nums.size(); ++i) {
      sum += nums[i];
      ret[i] = sum;
    }

    return ret;
  }
};

int main()
{
  class Solution s;
  std::vector<int> nums{1, 2, 3, 4};
  std::vector<int> ret;

  ret = s.runningSum(nums);
  for (auto iter=ret.begin(); iter<ret.end(); ++iter)
    std::cout << *iter << std::endl;

  return 0;
}
