#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
        int findPeakElement(vector<int> &nums)
        {
                if (nums.empty())
                {
                        return -1;
                }

                if (nums.size() == 1)
                {
                        return nums[0];
                }

                for (int i=1; i<nums.size(); ++i)
                {
                        if (nums[i] > nums[i-1])
                        {
                                if ((i+1) == nums.size())
                                {
                                        return -1;
                                }

                                if (nums[i+1] < nums[i])
                                {
                                        return i;
                                }
                                else if (nums[i+1] == nums[i])//nums[i+1]==nums[i]
                                {
                                        ++i;
                                }
                        }
                }

                return -1;
        }
};

int main()
{
        vector<int> nums{4,6};
        for (int i=0; i<nums.size(); ++i)
        {
                cout << nums[i] << ",";
        }
        cout << endl;

        class Solution a_class;
        cout << a_class.findPeakElement(nums) << endl;

        return 0;
}
