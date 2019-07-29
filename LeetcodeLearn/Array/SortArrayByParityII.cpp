#include <iostream>
#include <vector>

using namespace std;

// refer:https://leetcode-cn.com/problems/sort-array-by-parity-ii/submissions/

class Solution 
{
public:
    vector<int> sortArrayByParityII(vector<int>& A) 
    {
        if (A.empty())
        {
            return vector<int>();
        }

        vector<int> odd;
        vector<int> even;

        for (int i=0; i<A.size(); ++i)
        {
            if (A[i]%2)
            {
                even.push_back(A[i]);
            }
            else
            {
                odd.push_back(A[i]);
            }
        }

        int j = 0;
        for (int i=0; i<A.size(); ++i)
        {
            A[i++] = odd[j];
            A[i] = even[j++];
        }
        for (int i=0; i<A.size(); ++i)
        {
            cout << A[i] << ", ";
        }
        cout << endl;

        return A;
    }
};

int main()
{
    vector<int> vec = {2,3,1,1,4,0,0,4,3,3};
    class Solution a_class;

    a_class.sortArrayByParityII(vec);
    return 0;
}
