#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<vector<int> > generate(int numRows)
    {
        if (numRows == 0)
        {
            return vector<vector<int> >();
        }

        vector<vector<int> > ret(numRows);
        for (int i=0; i<numRows; ++i)
        {
            ret[i].resize(i+1);
        }

        ret[0][0] = 1;
        for (int i=1; i<numRows; i++)
        {
            ret[i][0] = 1;
            for (int j=1; j<ret[i].size()-1; ++j)
            {
                ret[i][j] = ret[i-1][j-1]+ret[i-1][j];
            }
            ret[i][ret[i].size()-1] = 1;
        }

        for (int i=0; i<numRows; i++)
        {
            for (int j=0; j<ret[i].size(); ++j)
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
    int num_rows = 4;
    class Solution a_class;
    a_class.generate(num_rows);

    return 0;
}
