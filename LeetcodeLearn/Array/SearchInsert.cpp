#include <iostream>
#include <vector>

using namespace std;

// refer: https://leetcode-cn.com/problems/search-insert-position/solution/

class Solution 
{
public:
    int searchInsert(vector<int>& nums, int target) 
    {
        if (nums.empty())
        {
            return -1;
        }

        int left = 0;
        int right = nums.size() - 1;

        if (nums[left] > target)
        {
            return 0;
        }
        if (nums[right] < target)
        {
            return right+1;
        }

        while (left <= right)
        {
            int mid = (left + right) / 2;

            if (nums[mid] == target)
            {
                return mid;
            }
            else if (nums[mid] > target)
            {
                if (nums[mid-1] < target)
                {
                    return mid;
                }
                
                right = mid - 1;
            }
            else
            {
                if (nums[mid+1] > target)
                {
                    return mid+1;
                }

                left = mid + 1;
            }
        }
    }
};

int main()
{
    vector<int> vec = {1,3,5,6};

    class Solution a_class;

    cout << a_class.searchInsert(vec, 5) << endl;
    return 0;
}
