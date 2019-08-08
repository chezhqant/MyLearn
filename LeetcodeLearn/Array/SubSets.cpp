#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:

    //动态规划
     vector<vector<int> > subsets(vector<int> & nums)
     {
       vector<vector<int> > ret(1);
       if (nums.empty())
       {
          return ret;
         }
     
       vector<int> temp;
       temp.push_back(nums[0]);
       ret.push_back(temp);
       for (int i=1; i<nums.size(); ++i)
       {
          int ret_size = ret.size();
          for (int j=0; j<ret_size; ++j)
          {
              vector<int> temp(ret[j]);
              temp.push_back(nums[i]);
              ret.push_back(temp);
             }
         }
     
       return ret;
      }
 //位运算，比如:
 /*nums = {1,2,3}
 他有：[], [1], [2], [3], [1,2], [1,3], [2,3], [1,2,3]总共八个；
 对应：000, 100 010  001   110    101   011    111*/
/*
 *  vector<vector<int> > subsets(vector<int> &nums)
 *  {
 *  int total = 1 << nums.size();
 *  vector<vector<int> > ret(total);
 * 
 *  for (int i=0; i<total; ++i)
 *  {
 *   for (int j=i, k=0; j!=0; j>>=1, ++k)//k最终能用到的值肯定小于nums.size()
 *   {
 *    if (j & 1)//此处的1等于001
 *    {
 *     ret[i].push_back(nums[k]); //[1], [2],[1,2],[3], [1,3], [2,3], [1,2,3]
 *    }
 *   }
 *  }
 * 
 *  return ret;
 *  }
 */
 


//               /*root
//   选1        不选1
// 选2         不选2   选2   不选2
//选3    不选3    选3      不选3    选3   不选3  选3   不选3
//前中后遍历即可*/
void PreVisit(vector<vector<int> > &ret, vector<int> &temp, vector<int> &nums, int level, bool select)
{
if (level == nums.size())
{
 //ret.push_back(temp);
 return;
}
vector<int> another_temp(temp);
if (select)
{
 another_temp.push_back(nums[level]);
 if (!another_temp.empty())
 {
  ret.push_back(another_temp);
 }
}
  
PreVisit(ret, another_temp, nums, level+1, true);  
PreVisit(ret,another_temp, nums, level+1, false);
}
//
//           /*root
//   选1        不选1
// 选2         不选2   选2   不选2
//选3    不选3    选3      不选3    选3   不选3  选3   不选3
//前中后遍历即可*/
// //void MidVisit(vector<vector<int> > &ret, vector<int> &temp, vector<int> &nums, int level, bool select)
// //{
// // if (level == nums.size())  //[0][0,2],[0,]
// // {
// //  //ret.push_back(temp);
// //  return;
// // }
// // 
// // vector<int> another_temp(temp);
// //   
// // MidVisit(ret, another_temp, nums, level+1, true);
// // 
// // if (select)
// // {
// //  temp.push_back(nums[level]);
// //  if (!temp.empty())
// //  {
// //   ret.push_back(temp);
// //  }
// // }
// // 
// // MidVisit(ret,another_temp, nums, level+1, false);
// //}
//
//          /*root
//   选1        不选1
// 选2         不选2   选2   不选2
//选3    不选3    选3      不选3    选3   不选3  选3   不选3
//前中后遍历即可*/
// void BehVisit(vector<vector<int> > &ret, vector<int> &temp, vector<int> &nums, int level, bool select)
// {
//  if (level == nums.size())  //[3], [2], [2,1]
//  {
//   //ret.push_back(temp);
//   return;
//  }
//  
//  vector<int> another_temp(temp);
//    
//  BehVisit(ret, another_temp, nums, level+1, true);
//  BehVisit(ret,another_temp, nums, level+1, false);
//  if (select)
//  {
//   temp.push_back(nums[level]);
//   if (!temp.empty())
//   {
//    ret.push_back(temp);
//   }
//  }
//  
// }
vector<vector<int> > subsets(vector<int> &nums)
{
 vector<vector<int> > ret;
 vector<int> temp;
 PreVisit(ret, temp, nums, 0, true);
 PreVisit(ret, temp, nums, 0, false);

 cout << "------------------------------" << endl;
 return ret;
}
};

int main()
{
 
 int a_array[] = {1,2,3};
 class Solution a_class;
 vector<int> vec(a_array, a_array+sizeof(a_array)/sizeof(int));

 int total = 1 << vec.size();
 vector<vector<int> > ret(total);
 ret = a_class.subsets(vec);

 for (int i=0; i<vec.size(); ++i)
  {
   cout << vec[i] << " ";
  }
  cout << endl;

 return 0;

 
}
