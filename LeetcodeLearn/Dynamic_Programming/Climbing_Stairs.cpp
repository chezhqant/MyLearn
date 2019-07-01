#include <iostream>
#include <vector>

using namespace std;

// refer:https://leetcode.com/problems/climbing-stairs/

/* 臨界條件：遍歷完成
最優子結構:climbStairs(n-1)
狀態轉移方程:ClimbStairs(n-1)+ClimbStairs(n-2) */

class Solution {
    public:
    int climbStairs(int n) {
            vector<int> ret;
            ret.push_back(0);
            ret.push_back(1);
            ret.push_back(2);
            
            for (int i = 3; i<=n; ++i)
            {
                        ret.push_back(ret[i-1]+ret[i-2]);
                    }
            
            return ret[n];
        }

    /* // 第二種方法:遞歸
    int ClimbStairs(int n)
    {
        if (n < 3)
        {
            return n;
        }

        return ClimbStairs(n-1)+ClimbStairs(n-2);
    } */
};

int main()
{
    return 0;
}
