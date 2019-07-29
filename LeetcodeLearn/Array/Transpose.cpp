#include <iostream>
#include <vector>

using namespace std;

// refer:https://leetcode-cn.com/problems/transpose-matrix/submissions/

class Solution 
{
public:
    vector<vector<int>> transpose(vector<vector<int>>& A) 
    {
        if (A.empty())
        {
            return vector<vector<int> >();
        }

        int rows = A.size();
        int cols = A[0].size();

        vector<vector<int> > ret(cols);
        for (int i=0; i<cols; ++i)
        {
            ret[i].resize(rows);
        }

        for (int i=0; i<rows; ++i)
        {
            for (int j=0; j<cols; ++j)
            {
                ret[j][i] = A[i][j];
            }
        }

        for (int i=0; i<cols; ++i)
        {
            for (int j=0; j<rows; ++j)
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
    vector<vector<int> > vec = {{1,2,3},{4,5,6}};
    class Solution a_class;

    a_class.transpose(vec);

    return 0;
}
