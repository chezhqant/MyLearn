#include <iostream>
#include <vector>

using namespace std;


// /*******************************************************
/// brief: 将所有的nums元素的每一位的1超过一半的，加起来就是结果
// *******************************************************/
class Solution 
{
public:
/*{{{
 *     int majorityElement(vector<int>& nums) 
 *     {
 *         if (nums.size() == 0)
 *         {
 *             return 0;
 *         }
 * 
 *         int ret=0;
 *         
 *         int int_length = sizeof(ret)*8;
 *         for (int i=0; i<int_length; ++i)
 *         {
 *             int nums_1 = 0;
 *             int nums_0 = 0;
 * 
 *             for (int j=0; j<nums.size(); ++j)
 *             {
 *                 if ((nums[j]>>i) & 1)
 *                 {
 *                     ++nums_1;
 *                 }
 *                 else
 *                 {
 *                     ++nums_0;
 *                 }
 *                 
 *             }
 * 
 *             if (nums_1 > nums_0)
 *             {
 *                 ret += (1<<i);
 *             }
 *         }
 * 
 *         return ret;
 *     }
 *//*}}}*/

    int majorityElement(vector<int>& nums)
    {
        if (nums.size() == 0)
        {
            return 0;
        }

        int number_nums = 1;
        int number = nums[0];
        for (int i=1; i<nums.size(); ++i)
        {
            if (nums[i] == number)
            {
                ++number_nums;
            }
            else if (number_nums == 1)
            {
                number = nums[i];
            }
            else
            {
                --number_nums;
            }
        }

        return number;
    }
};

int main()
{
    vector<int> nums{3,2,3};

    class Solution a_class;
    cout << a_class.majorityElement(nums) << endl;
    return 0;
}
