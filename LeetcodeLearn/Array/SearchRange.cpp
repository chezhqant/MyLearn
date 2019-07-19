#include <iostream>
#include <vector>

using namespace std;

/* refer: https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/submissions/ */
/* 首先进行二分查找，查找出来有相等的数字，然后想两边辐射 */

class Solution 
{
public:
    void FindBorder(vector<int> &nums, vector<int> &ret, int target, int pos)
    {
        int temp = pos-1;
        while (temp >= 0)
        {
            if (nums[temp] == target)
            {
                ret[0] = temp--;
            }
            else
            {
                break; 
            }
        }

        temp = pos+1;
        while (temp < nums.size())
        {
            if (nums[temp] == target)
            {
                ret[1] = temp++;
            }
            else
            {
                break;
            }
        }
    }

    vector<int> searchRange(vector<int>& nums, int target)
    { 
        int size = nums.size();

        vector<int> ret(2, -1);
        if (size == 0 || target < nums[0] || target > nums[size-1])
        {
            return ret;
        }

        int left = 0;
        int right = size-1;
        int find_target_pos = -1;
        while (left <= right)
        {
            int mid = (left+right)/2;
            if (nums[mid] == target)
            {
                find_target_pos = mid; 
                break;
            }
            else if(target < nums[mid])
            {
                right = mid-1;
            }
            else
            {
                left = mid+1;
            }
        }

        if (find_target_pos != -1)
        {
            ret[0] = find_target_pos;
            ret[1] = find_target_pos;

            FindBorder(nums, ret, target, find_target_pos);
        }

        return ret;
    }
};

int main()
{
    vector<int> nums = {5,7,7,8,8,10};
    class Solution a_class;

    vector<int> ret = a_class.searchRange(nums, 6);
    for (int i=0; i<ret.size(); ++i)
    {
        cout << ret[i] << ", ";
    }
    cout << endl;

    return 0;
}
