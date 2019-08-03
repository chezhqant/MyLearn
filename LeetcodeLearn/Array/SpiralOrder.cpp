#include <iostream>
#include <vector>

using namespace std;

// refer: https://leetcode-cn.com/problems/spiral-matrix/submissions/
// 按照這種，每一種運算符號算是一個循環

/*{{{
 * - - - - +
 * + - - * +
 * + * \ \ +
 * + - - - -
 *//*}}}*/

class Solution 
{
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) 
    {
        if (matrix.empty())
        {
            return vector<int>();
        }

        int rows = matrix.size();
        int cols = matrix[0].size();


        vector<int> ret;
        if (rows == 1)
        {
            for (int i=0; i<cols; ++i)
            {
                ret.push_back(matrix[0][i]);
            }

            return ret;
        }
        else if (cols == 1)
        {
            for (int i=0; i<rows; ++i)
            {
                ret.push_back(matrix[i][0]);
            }
            
            return ret;
        }

        int loop = (rows>cols) ? (cols+1)/2 : (rows+1)/2;

        int row_left = 0;
        int row_right = cols-1;
        int col_up = 0;
        int col_down = rows-1;

        while (loop--)
        {
            if (row_left == row_right)
            {
                for (int i=col_up; i<=col_down; ++i)
                {
                    ret.push_back(matrix[i][row_left]);
                }
                return ret;
            }
            else if (col_up == col_down)
            {
                for (int i=row_left; i<=row_right; ++i)
                {
                    ret.push_back(matrix[col_up][i]);
                }
                return ret;
            }

            for (int i=row_left; i<row_right; ++i) 
            {
                ret.push_back(matrix[col_up][i]);
            }
            for (int j=col_up; j<col_down; ++j)
            {
                ret.push_back(matrix[j][row_right]);
            }
            for (int i=row_right; i>row_left; --i)
            {
                ret.push_back(matrix[col_down][i]);
            }
            for (int j=col_down; j>col_up; --j)
            {
                ret.push_back(matrix[j][row_left]);
            }
            ++row_left;
            --row_right;
            ++col_up;
            --col_down;
        }

        return ret;
    }
};

int main()
{
    /*{{{
     * vector<vector<int> > matrix = {
     *  { 1, 2, 3, 13, 14},
     *  { 4, 5, 6, 15, 16},
     *  { 7, 8, 9, 17, 18},
     *  {10, 11, 12, 19, 20}
     * };
     *//*}}}*/

    vector<vector<int> > matrix = {{1}};
    class Solution a_class;

    vector<int> ret = a_class.spiralOrder(matrix);
    for (int i=0; i<ret.size(); ++i)
    {
        cout << ret[i] << ", " << endl;
    }

    return 0;
}
