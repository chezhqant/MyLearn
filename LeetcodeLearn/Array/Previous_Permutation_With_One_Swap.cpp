#include <iostream>
#include <vector>

using namespace std;

/*
 * refer: https://leetcode.com/problems/previous-permutation-with-one-swap/
 * 这道题我有点怀疑出错了
 */

void ShowVector(vector<int> &vec)
{
    for (int i=0; i<vec.size(); ++i)
    {
        cout << vec[i] << ", ";
    }
    cout << endl;

}

class Solution {
    public:
    vector<int> prevPermOpt1(vector<int>& A) 
    {
        if (A.empty())
        {
            return A;
        }

        int sub_forbit_discend = A.size()-1;
        for (int i=sub_forbit_discend; i>0; --i)
        {
            if (A[i]<A[i-1])
            {
                sub_forbit_discend = i-1;
                break;
            } 
        }

        if (sub_forbit_discend == A.size()-1)
        {
            return A;
        }
        
        for (int i=A.size()-1; i>sub_forbit_discend; --i)
        {
            if (A[i] < A[sub_forbit_discend])
            {
                while (A[i] == A[i-1])
                {
                    --i;
                }        

                swap(A[i], A[sub_forbit_discend]);
                break;
            }
        }

        ShowVector(A);

        /*
         *这道题竟然需要把这个注释了
         * for (int i=sub_forbit_discend+1, j=A.size()-1; i<j; ++i, --j)
         * {
         *     swap(A[i], A[j]);
         * }
         */ 
        return A;
    }
};

int main()
{
    class Solution a_class;
    vector<int> vec={1, 9, 4, 6, 7};

    ShowVector(vec);

    a_class.prevPermOpt1(vec);

    ShowVector(vec);
    
    return 0;
}
