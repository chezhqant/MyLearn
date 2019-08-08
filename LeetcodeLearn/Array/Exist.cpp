#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Solution
{
public:
 bool FindNumthChar(vector<vector<char> > &board, vector<vector<bool> > &mark, char c, int &i, int &j)
 {
  int left = j-1;
  int right = j+1;
  int up = i-1;
  int down = i+1;

  if (left>=0)
  {
   if (!mark[i][left] && board[i][left] == c)
   {
    j = left;
    return true;
   }
  }
  if (down<=board.size()-1)
  {
   if (!mark[down][j] && board[down][j] == c)
   {
    i = down;
    return true;
   }
  }
  if ((up>=0))
  {
   if (!mark[up][j] && board[up][j] == c)
   {
    i = up;
    return true;
   }
  }
  if (right<=board[0].size()-1)
  {
   if (!mark[i][right] && board[i][right] == c)
   {
    j = right;
    return true;
   }
  }
  
  return false;
 }

 //find first char of word in board;
 bool FindFirstChar(vector<vector<char> > &board, char c, int &i, int &j)
 {
  for (int k=i; k<board.size(); ++k)
  {
   for (int l=j; l<board[0].size(); ++l)
   {
    if (board[i][j] == c)
    {
     i = k;
     k = l;
     return true;
    }
   }
  }

  return false;
 }


 bool exist(vector<vector<char> > &board, string word)
 {
  if (board.size() == 0)
  {
   return false;
  }
  if (board[0].size() == 0)
  {
   return false;
  }

  int word_length = word.length();
  if (word_length == 0)
  {
   return true;
  }
 
  int begin_row = 0;
  int begin_col = 0;
  
  while (FindFirstChar(board, word[0], begin_row, begin_col))
  {
   vector<vector<bool> > mark(board.size());
   for (int i=0; i<board.size(); ++i)
   {
    mark[i].resize(board[0].size());
   }
   for (int i=0; i<board.size(); ++i)
   {
    for (int j=0; j<board[0].size(); ++j)
    {
     mark[i][j] = false;
    }
   }

   int curr = 1;
   int begin_row_temp = begin_row;
   int begin_col_temp = begin_col;
   mark[begin_row][begin_col] = true;

   while (curr < word_length)
   {
    if (FindNumthChar(board, mark, word[curr], begin_row_temp, begin_col_temp))
    {
     mark[begin_row_temp][begin_col_temp] = true;
     ++curr;
    }
    else
    {
     if ((begin_col==board[0].size()-1))
     {
      if (begin_row!=board.size()-1)
      {
       ++begin_row;
       begin_col = 0;
      }
      else
      {
       break;
      }
     }
     else
     {
      ++begin_col;
     }
     break;
    }
   }

   if (curr == word_length)
   {
    return true;
   }
  }
  
  return false;
 }
};

int main()
{
 
 char a_array1[] = {'a', 'a', 'b', 'c'};
 char a_array2[] = {'c', 'd', 'e', 'c'};
 char a_array3[] = {'g', 'w', 'q', 'e'};

 string str = "aada";
 class Solution a_class;
 vector<vector<char> > vec;

 vector<char> temp1(a_array1, a_array1+sizeof(a_array1)/sizeof(char));
 vector<char> temp2(a_array2, a_array2+sizeof(a_array1)/sizeof(char));
 vector<char> temp3(a_array3, a_array3+sizeof(a_array1)/sizeof(char));
 vec.push_back(temp1);
 vec.push_back(temp2);
 vec.push_back(temp3);

 cout << a_class.exist(vec, str) << endl;

 return 0;

}
