#include <iostream>
#include <vector>

using namespace std;

// refer:https://leetcode-cn.com/problems/flipping-an-image/submissions/

class Solution 
{
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) 
    {
        if (A.empty())
        {
            return vector<vector<int> > ();
        }

        int rows = A.size();
        int cols = A[0].size();

        vector<vector<int> > ret(A);

        for (int i=0; i<rows; ++i)
        {
            for (int j=(cols-1); j>=0; --j)
            {
                ret[i][cols-j-1] = ((A[i][j] == 1) ? 0 : 1);
            }
        }

        for (int i=0; i<rows; ++i)
        {
            for (int j=0; j<cols; ++j)
            {
                cout << ret[i][j] << ", ";
            }
            cout << endl;
        }


        return ret;
    }
};

int main()
{
    vector<vector<int> > vec = {{1,1,0,0},{1,0,0,1},{0,1,1,1},{1,0,1,0}};

    class Solution a_class;

    vector<vector<int> > another;
    a_class.flipAndInvertImage(vec);

    return 0;
}
