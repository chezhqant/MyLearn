#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution 
{
public:
    void rotate(vector<int>& nums, int k) 
    {
        if (nums.size() == 0)
        {
            return;
        }

        if (k > nums.size())
        {
            return;
        }

        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin()+k);
        reverse(nums.begin()+k, nums.end());
    }
};

int main()
{
    vector<int> nums{1,2,3,4,5,6};
    class Solution a_class;
    a_class.rotate(nums, 1);

    return 0;
}

