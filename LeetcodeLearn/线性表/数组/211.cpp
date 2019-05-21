/// @file: RemoveDuplicatesFromSortedArray.cpp
/// brief: Remove Duplicates From Sorted Array
/// @author: chezhai<che599669638@163.com>
/// @version 1.0.0
/// @date 2019-04-08
//
//descript:
//Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.
//Do not allocate extra space for another array, you must do this in place with constant memory.
//for example, Given input array A=[1,1,2].
//Your function should return length=2, and A is now [1,2]

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int RemoveDuplicates(vector<int> &nums)
    {
        if (nums.empty())
        {
            return 0;
        }

        stable_sort(nums.begin(), nums.end());
        for(vector<int>::const_iterator it = nums.begin(); it != nums.end(); ++it)
        {
            cout << *it << ", ";
        }
        cout << endl;

        int index = 0;
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[index] == nums[i])
            {
                continue;
            }
            else
            {
                nums[++index]=nums[i];
            }
        }

        return (index + 1);
    }

};

int main()
{
    vector<int> num({2,3,4,4,5});
    Solution s;
    cout << s.RemoveDuplicates(num) << endl;
    return 0;
}

