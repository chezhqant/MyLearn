#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//首先算是三个指针：p指向0的最右边的下一个；p2指向2的最左边的下一个；curr遍历整个数组的指针；
//原来考虑当nums[0]=2的时候怎么办，后来发现，因为是从0开始遍历的，p0最终的指向永远不可能指向2！！！

class Solution
{
public:
 void swap(int &num1, int &num2)
 {
  if (num1 == num2)
  {
   return;
  }

  //cout << num1 << ", " << num2 << endl;
  num1 = num1^num2;
  num2 = num2^num1;
  num1 = num1^num2;
  //cout << num1 << ", " << num2 << endl;
 }

 void sortColors(vector<int> &nums)
 {
  if (nums.empty())
  {
   return;
  }

  int p0 = 0;
  int curr = 0;
  int p2 = nums.size()-1;

  while (curr <= p2)
  {
   if (nums[curr] == 0)
   {
    swap(nums[p0++], nums[curr++]);//是0的时候
   }
   else if (nums[curr] == 2)
   {
    swap(nums[curr], nums[p2--]);//是2 的时候，注意，此时的curr不是curr++，因为还要再次判断curr的值
   }
   else
   {
    ++curr;
   }
  }
 }
};

int main()
{
 
 int a_array[] = {1,0,2, 2, 1, 2, 0,1, 2, 0};
 class Solution a_class;
 vector<int> vec(a_array, a_array+sizeof(a_array)/sizeof(int));
 a_class.sortColors(vec);

 for (int i=0; i<vec.size(); ++i)
  {
   cout << vec[i] << " ";
  }
  cout << endl;

 return 0;
}
