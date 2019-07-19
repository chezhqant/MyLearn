#include <iostream>
#include <vector>

using namespace std;

/*
 * refer: https://leetcode.com/problems/house-robber/
 * dp[1] = nums[0];
 * dp[2] = max(nums[0], nums[1]);
 * dp[3] = max(nums[2]+dp[1], dp[2]);
 * dp[4] = max(nums[3]+dp[2], dp[3]);
 */


class Solution {
public:
    int rob(vector<int>& nums) 
    {
        int size = nums.size();

        if (nums.empty())
        {
            return 0;
        }
        else if (size == 1)
        {
            return nums[0];
        }
        else if (size == 2)
        {
            return max(nums[0], nums[1]);
        }

        vector<int> dp(size, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        dp[2] = max(nums[2]+dp[0], nums[1]);

        if (size < 4)
        {
            return dp[size-1];
        }

        for (int i=3; i<nums.size(); ++i)
        {
            dp[i] = nums[i] + max(dp[i-3], dp[i-2]);
        }

        return max(dp[size-1], dp[size-2]);
    }
};

int main()
{
    vector<int> nums={0};

    class Solution a_class;

    cout << a_class.rob(nums) << endl;
    return 0;
}
