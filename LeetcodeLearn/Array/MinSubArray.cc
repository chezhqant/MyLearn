#include <iostream>
#include <vector>

using namespace std;

class Solution 
{
public:
    int minSubArrayLen(int s, vector<int>& nums) 
    {
        if (nums.empty())
        {
            return 0;
        }

        int left = 0;
        int sum = nums[0];
        int i = 1;
        while (i < nums.size())
        {
            if (sum > s)
            {
                sum -= nums[left];
                ++left;
            } 
            else if (sum == s)
            {
                return (i-left)+1;
            }
            else
            {
                sum += nums[i++];
            }
        }

        return 0;
    }
};

int main()
{
    vector<int> nums{2,3,1,2,4,3};
    class Solution a_class;
    cout << a_class.minSubArrayLen(7, nums) << endl;

    return 0;
}
