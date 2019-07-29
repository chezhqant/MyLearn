#include <iostream>
#include <vector>

using namespace std;

/* refer: https://leetcode-cn.com/problems/remove-element/ */

/*
 * 因为原题上不要求保持数组顺序，所以从左右开始，左边一旦找出=val的值得时候，在left<right的情况下找到右边不等于val的值，两者互换。
 * 若left<right不成立，则跳出最外层while循环，不再执行++left;
 */

class Solution 
{
public:
    int removeElement(vector<int>& nums, int val) 
    {
        if (nums.empty())
        {
            return 0;
        }

        if (nums.size() == 1)
        {
            return ((nums[0]-val) != 0);
        }

        int left = 0;
        int right = nums.size()-1;

        while (left <= right)//必须有相等的时候的判断,比如说nums=[2,1], val=2,如果不判断left=1的时候就会漏检
        {
            if (nums[left] == val)
            {
                while ((left<right) && (nums[right]==val))
                {
                    --right; 
                }

                if (left < right)
                {
                    swap(nums[left], nums[right]);
                }
                else
                {
                    break;
                }
            } 

            ++left;
        }

        return left;
    }
};

int main()
{
    vector<int> nums = {2,2,2,2,1,2,2};
    int val = 2;

    class Solution a_class;

    cout << a_class.removeElement(nums, val) << endl;

    return 0;
}
