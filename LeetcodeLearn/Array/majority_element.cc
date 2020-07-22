#include <iostream>
#include <vector>

using namespace std;


// /*******************************************************
/// brief: 将所有的nums元素的每一位的1超过一半的，加起来就是结果
// *******************************************************/
class Solution 
{
public:
/*{{{
 *     int majorityElement(vector<int>& nums) 
 *     {
 *         if (nums.size() == 0)
 *         {
 *             return 0;
 *         }
 * 
 *         int ret=0;
 *         
 *         int int_length = sizeof(ret)*8;
 *         for (int i=0; i<int_length; ++i)
 *         {
 *             int nums_1 = 0;
 *             int nums_0 = 0;
 * 
 *             for (int j=0; j<nums.size(); ++j)
 *             {
 *                 if ((nums[j]>>i) & 1)
 *                 {
 *                     ++nums_1;
 *                 }
 *                 else
 *                 {
 *                     ++nums_0;
 *                 }
 *                 
 *             }
 * 
 *             if (nums_1 > nums_0)
 *             {
 *                 ret += (1<<i);
 *             }
 *         }
 * 
 *         return ret;
 *     }
 *//*}}}*/

/*
 *     // 摩尔投票法
 *     int majorityElement(vector<int>& nums)
 *     {
 *         if (nums.size() == 0)
 *         {
 *             return 0;
 *         }
 * 
 *         int number_nums = 1;
 *         int number = nums[0];
 *         for (int i=1; i<nums.size(); ++i)
 *         {
 *             if (nums[i] == number)
 *             {
 *                 ++number_nums;
 *             }
 *             else if (number_nums == 1)
 *             {
 *                 number = nums[i];
 *             }
 *             else
 *             {
 *                 --number_nums;
 *             }
 *         }
 * 
 *         return number;
 *     }
 */

  /*! 分治的可行性论述
   * 分治算法要求原问题划分为子问题时仍具有和原问题一样的性质，考虑这样的划分，取中间下标，将原规模为n数据集合划分为两个规模为n/2集合。
   * 首先，原集合肯定满足有一个元素的个数大于n/2(题目给出，即“多数元素”)。那么划分为两个集合A，B的时候。有两种情况：
   * 1. 划分子集“多数元素”在A和B中均成为“多数元素”，那么返回子集的多数元素即为原集合的“多数元素”。因为在A集合中成为多数元素的要求是该元素的个数大于n/4（原集合大于n/2)，B集合同样如此。那么将两个集合的该元素个数统计起来肯定大于n/2，即为“多数元素”。(不可能出现两个元素个数同时大于n/2，否则原集合个数必定大于n
   * 2. 划分子集后，“多数元素”较均匀分布，只成为了其中一个集合的多数元素，那么只需要拿另一个集合的众数来检验到底谁才是“多数元素”
   * 3. 不会出现两个集合的众数都不是“多数元素的情况”，假设一个极端的例子[1,1,1,2,2,3,3,3,2,2]划分为两个集合[1,1,1，2,2]和[3,3,3,2,2]，左边的集合众数为1，右边的集合众数为3，但是该集合的任何一个元素的个数都不满足大于n/2
   */
  int majority_judge(vector<int>& nums, int num, int left, int right){
    int count = 0;
    for(int i=left;i<=right;i++){
      if(nums[i] == num)
        count ++;
    }
    // cout << num << "-" << count <<endl;
    return count; 
  }

  int helper(vector<int>& nums, int left, int right){
    if(left == right) return nums[left];
    else{
      int mid = (left + right) >> 1;
      int left_majority = helper(nums, left, mid);
      int right_majority = helper(nums, mid+1, right);
      int left_majority_count = majority_judge(nums, left_majority, left, right);
      int right_majority_count = majority_judge(nums, right_majority, left, right);
      return left_majority_count > right_majority_count ? left_majority : right_majority;
    }
  }

  int majorityElement(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    int result = helper(nums, left, right);
    int cnt = 0;
    int size = nums.size();
    for(int i = 0; i < size; i++) {
      if(nums[i] == result) cnt++;
    }
    if(cnt <= size / 2) result = -1;
    return result;
  }
};

int main()
{
    vector<int> nums{3,2,3};

    class Solution a_class;
    cout << a_class.majorityElement(nums) << endl;
    return 0;
}
