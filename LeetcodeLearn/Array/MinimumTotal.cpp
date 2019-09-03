#include <iostream>
#include <vector>

using namespace std;

class Solution 
{
    public:
    int minimumTotal(vector<vector<int>>& triangle) 
    {
        if (triangle.empty() || triangle[0].empty())
        {
            return 0;
        }

        if (triangle.size() == 1)
        {
            return triangle[0][0];
        }

        for (int i=1; i<triangle.size(); ++i)
        {
            for (int j=0; j<triangle[i].size(); ++j)
            {
                if (j == 0)
                {
                    triangle[i][j] += triangle[i-1][0];
                }    
                else if (j != (triangle[i].size()-1))
                {
                    triangle[i][j] += min(triangle[i-1][j-1], triangle[i-1][j]); 
                }
                else
                {
                    triangle[i][j] += triangle[i-1][j-1];
                }
            }
        }

        int mini = triangle[triangle.size()-1][0];
        for (int i=1; i<triangle[triangle.size()-1].size(); ++i)
        {
            mini = min(mini, triangle[triangle.size()-1][i]);
        }

        return mini;
    }
};

int main()
{
    vector<vector<int>> nums = {{}};

    class Solution a_class;
    cout << a_class.minimumTotal(nums) << endl;
    return 0;
}
