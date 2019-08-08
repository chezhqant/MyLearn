#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//1  3  5  7
//10 11 16 20
//23 30 34 50

class Solution
{
public:
 bool searchMatrix(vector<vector<int> > &matrix, int target)
 {
  if (matrix.empty())
  {
   return false;
  }

  int find_row = 0;
  int down = matrix.size() - 1;
  int right = matrix[0].size()-1;

  if (target < matrix[0][0] || target > matrix[down][right])
  {
   return false;
  }

  for (int i=down-1; i >= 0; --i)
  {
   if (target > matrix[i][right])
   {
    find_row = i+1;
    break;
   }
  }

  for (int i=0; i<=right; ++i)
  {
   if (target == matrix[find_row][i])
   {
    return true;
   }
  }
  return false;
 }
};

int main()
{
 
 class Solution a_class;
 vector<vector<int> > vec(2);
 for (int i=0; i<2; ++i)
 {
    vec[i].resize(1);
 }

 vec[0][0] = 1;
 vec[1][0] = 3;

 cout << a_class.searchMatrix(vec, 3) << endl;;

 return 0;
}
