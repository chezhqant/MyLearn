#include <iostream>
#include <vector>

using namespace std;

// refer: https://leetcode-cn.com/problems/squares-of-a-sorted-array/submissions/

class Solution 
{
public:
    vector<int> sortedSquares(vector<int>& A) 
    {
        if (A.empty())
        {
            return vector<int>();
        }

        vector<int> ret(A);
        int last_lt_0 = 0;
        for (int i=0; i<A.size(); ++i)
        {
            if (A[i]<0)
            {
                last_lt_0 = i; 
            }
            A[i] = A[i]*A[i];
        }

        int first_gt_0 = last_lt_0+1;

        int i = 0;
        while (last_lt_0>=0 && first_gt_0<A.size())
        {
            if (A[first_gt_0]<=A[last_lt_0])
            {
                ret[i++] = A[first_gt_0++];
            }
            else
            {
                ret[i++] = A[last_lt_0--];
            }
        }
        while (last_lt_0>=0)
        {
            ret[i++] = A[last_lt_0--];
        }
        while (first_gt_0<A.size())
        {
            ret[i++] = A[first_gt_0++];
        }

        for (int i=0; i<A.size(); ++i)
        {
            cout << ret[i] << ", ";
        }
        cout << endl;

        return ret;
    }
};

int main()
{
    vector<int> vec = {-7,-3,2,3,11};

    class Solution a_class;

    a_class.sortedSquares(vec);
    return 0;
}
