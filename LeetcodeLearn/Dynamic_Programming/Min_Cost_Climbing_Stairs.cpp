#include <iostream>
#include <vector> 

using namespace std;

// refer:https://leetcode.com/problems/min-cost-climbing-stairs/submissions/

/*
 * dp[0]=0//没有楼梯
 * dp[1]=0//一层楼梯
 * dp[2]=min(dp[0],dp[1])//两层楼梯
 * dp[3]=min(dp[1]+cost[1], dp[2]+cost[2])//三层楼梯    
*/

class Solution {
    public:
    int minCostClimbingStairs(vector<int>& cost) 
    {
        int size = cost.size();
        
        vector<int> dp(size+1, 0);
        dp[2] = min(cost[0], cost[1]);
        for (int i=3; i<(size+1); i++)
        {
            dp[i] = min(dp[i-1]+cost[i-1], dp[i-2]+cost[i-2]); 
        }

        return dp[size];
    }
};

int main()
{
    vector<int> vec = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};

    class Solution a_class;
    cout << a_class.minCostClimbingStairs(vec) << endl;
    return 0;
}
