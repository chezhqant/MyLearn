#include <iostream>
#include <vector>

using namespace std;

// refer:https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

/* 臨界條件：遍歷完成
狀態轉移矩陣：max(nums[j]-nums[i]) && j>i
最優子結構：暫時想不出來 */

class Solution {
    public:
    int maxProfit(vector<int>& prices) 
    {
        if (prices.empty())
        {
            return 0;
        } 
        int min_price=prices[0];
        int max_agio=0;

        for (int i=1; i<prices.size(); ++i)
        {
            if (prices[i] < min_price)
            {
                min_price = prices[i];
            }
            else if ((prices[i]-min_price)>max_agio)
            {
                max_agio = prices[i]-min_price;
            }
        }

        return max_agio;
    }
};

int main()
{
    vector<int> nums = {7,1,5,3,6,4};
    class Solution a_class;
    cout << a_class.maxProfit(nums) << endl;

    return 0;
}
