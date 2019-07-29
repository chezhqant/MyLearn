#include <iostream>
#include <vector>

using namespace std;

// refer: https://leetcode-cn.com/problems/sort-array-by-parity/submissions/

class Solution 
{
public:
    vector<int> sortArrayByParity(vector<int>& A) 
    {
        if (A.empty())
        {
            return vector<int>();
        }

        if (A.size() == 1)
        {
            vector<int> temp(A);
        }

        int i = 0;
        int j = A.size()-1;

        while (i<j)
        {
            if (A[i] % 2)//如果是奇数
            {
                if (A[j] % 2 == 0)//如果是偶数
                {
                    swap(A[i], A[j]);
                    ++i;
                }

                 --j; 
            }
            else
            {
                ++i;
            }
        }

        return A;
    }
};

int main()
{
    return 0;
}
