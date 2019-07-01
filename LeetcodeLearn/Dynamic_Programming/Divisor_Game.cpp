#include <iostream>
#include <vector>

using namespace std;

// refer:https://leetcode.com/problems/divisor-game/submissions/
/*
 * 使用DP数组：
 * Dp[0]=false
 * Dp[1]=false
 * Dp[2]=true
 * Dp[3]=false
 * Dp[4]=true
 */
// 这样以简单到复杂，每一个当前计算的都是以前面的为前提计算

class Solution {
public:
    bool divisorGame(int N) 
    {
        vector<bool> dp(N+1, false);


        dp[1] = false;
        dp[2] = true;

        for (int i=3; i<N+1; ++i)
        {
            int j=1;
            while (j <= (i/2))
            {
                if ((i%j==0) && (dp[i-j]==false))
                {
                    // cout <<"i-j:" << (i-j) << "dp[i-j]: " << dp[i-j] << endl;
                    dp[i] = true;
                    break;
                    // cout << "i: " << i << " ---- " << dp[i] << endl;
                }
                ++j;
            }
        }

        return dp[N];
    }
};

int main()
{
    class Solution a_class;
    cout << a_class.divisorGame(4) << endl;

    return 0;
}
