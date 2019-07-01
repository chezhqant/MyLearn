#include <iostream>
#include <vector>

using namespace std;

// refer:https://leetcode.com/problems/maximum-subarray/submissions/

/*
 * 臨界條件：nums遍歷完
 * 狀態轉移方程：
 * 1、如果local_max<=0,則重新獲取連續數列
 * 2、如果local_max+nums[i]>nums[i]，則將nums[i]加入連續數列中，必須得是">nums[i]"
 * 最優子結構：glocal_max(局部最優),遍歷完成之後變為全局最優
 */

class Solution 
{
public:
    int maxSubArray(vector<int>& nums) 
    {
        if (nums.empty())
        {
            return 0;
        }

        int local_max = nums[0];
        int global_max = nums[0];

        for (int i=1; i<nums.size(); ++i)
        {
            if (local_max<=0)
            {
                if (local_max < nums[i])
                {
                    local_max = nums[i];
                }
            }
            else if ((local_max+nums[i])>nums[i])
            {
                local_max += nums[i]; 
            }

            if (local_max > global_max)
            {
                global_max = local_max;
            }
        }

        return global_max;
    }
};

int main()
{
    vector<int> nums = {1,2,-1,-2,2,1,-2,1,4,-5,4};

    class Solution a_class;
    cout << a_class.maxSubArray(nums) << endl;
    return 0;
}
