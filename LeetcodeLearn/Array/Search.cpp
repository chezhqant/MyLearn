#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Solution
{
public:
 //[0,0,1,2,2,5,6]可能变为[2,5,6,0,0,1,2]
 //[1,1,1,1,1]
 //[1,1,1,1,1,2,2] [2,1,1,1,1,1,2]
 //[4,5,1,2,3]
 //[5,5,5,5,5,1,2,3,4,5]
 bool search(vector<int> &nums, int target)
 {
  if (nums.empty())
  {
   return false;
  }
  else if (nums.size() == 1)
  {
   return nums[0] == target ? true : false;
  }

  int left = 0;
  int right = nums.size()-1;

  while (left<=right)
  {
   int mid = (left+right)/2;
   if (target > nums[left])
   {
    if (nums[mid] >= nums[left])
    {
     if (target < nums[mid])
     {
      right = mid-1;
     }
     else if (target > nums[mid])
     {
      left = mid+1;
     }
     else
     {
      return true;
     }
    }
    else//nums[mid]<nums[left]
    {
     right = mid-1;
    }
   }
   else if (target == nums[left])
   {
    return true;
   }
   else//target < nums[left]
   {
    if (nums[mid] >= nums[left])
    {
     left = mid+1;
    }
    else//nums[mid]<nums[left]
    {
     if (target > nums[mid])
     {
      left = mid+1;
     }
     else if (target == nums[mid])
     {
      return true;
     }
     else//target < nums[mid]
     {
      right = mid-1;
     }
    }
   }
  }

  return false;
 }
};

int main()
{
 
 
 int p[] = {1,3,1,1,1};
 vector<int> vec(p, p+sizeof(p)/sizeof(int));
 class Solution a_class;

 int number = 3;

 cout << a_class.search(vec, number) << endl;

 return 0;

 
}
