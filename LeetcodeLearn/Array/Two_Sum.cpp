#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

// refer: https://leetcode.com/problems/two-sum/
class Solution
{
public:
    // 第一种方法，在LeetCode上效果不佳
    // 从左到右开始搜索
    vector<int> TwoSum(vector<int> &nums, int target)/*{{{*/
    {
       if (nums.size() < 2) 
       {
            return vector<int>();
       }

       vector<int> ret;
       for (int i=0; i<(nums.size()-1); ++i)
       {
           int remain = target - nums[i];

           auto a_num = std::find(nums.begin()+i+1, nums.end(), remain);//不包括本元素


           /* 之所以使用while，是因为会出现重复性元素;
           比如：{2, 7, 11, 5, 4, 4, 15}, 当target=9的时候，nums[i]=5,ret中应该是{0,1, 3,4, 3,5} */
           while (a_num != nums.end())
           {
               ret.push_back(i);
               ret.push_back(a_num-nums.begin()); 

               a_num = std::find(a_num+1, nums.end(), remain);//不包括本元素
           }
       }

        return ret;
    }/*}}}*/
};

int main()
{
    vector<int> nums = {2, 7, 11, 5, 4, 4, 15};
    class Solution a_class;
    vector<int> ret = a_class.TwoSum(nums, 9);

    for (int i = 0; i < ret.size(); ++i)
    {
        cout << ret[i] << endl;
    }
    return 0;
}

