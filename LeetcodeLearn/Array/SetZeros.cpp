#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
 void setZeroes(vector<vector<int> > &matrix)
 {
  if (matrix.empty())
  {
   return;
  }

  bool row = false;
  bool col = false;

  for (int i=0; i<matrix.size(); ++i)//行
  {
   for (int j=0; j<matrix[0].size(); ++j)//列
   {
    if (matrix[i][j] == 0)
    {
     if (i == 0)
     {
      row = true;
     }
     if (j == 0)
     {
      col = true;
     }

     matrix[i][0] = 0;
     matrix[0][j] = 0;
    }
   }
  }

  for (int i=1; i<matrix[0].size(); ++i)//列
  {
   if (matrix[0][i] == 0)
   {
    for(int j=1; j<matrix.size(); ++j)
    {
     matrix[j][i] == 0;
    }
   }
  }
  for (int i=1; i<matrix.size(); ++i)//行
  {
   if (matrix[0][i] == 0)
   {
    for(int j=1; j<matrix[0].size(); ++j)
    {
     matrix[i][j] == 0;
    }
   }
  }

  if (row)
  {
   for (int i=1; i<matrix[0].size(); ++i)
   {
    matrix[0][i] = 0;
   }
  }
  if (col)
  {
   for (int i=1; i<matrix.size(); ++i)
   {
    matrix[i][0] = 0;
   }
  }
 }
};

int main()
{
 
 int a_array[] = {1,9,9};
 class Solution a_class;
 vector<int> vec(a_array, a_array+sizeof(a_array)/sizeof(int));
 a_class;

 for (int i=0; i<vec.size(); ++i)
  {
   cout << vec[i] << " ";
  }
  cout << endl;

 return 0;

 
}
