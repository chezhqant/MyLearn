#include <iostream>
#include <vector>

using namespace std;

/*
 * 
 * 該題主要思路是將下標加上最大的步數，看看該元素能夠覆蓋的最大範圍是多少。用一個for循環遍歷，判斷該元素==下標值，如果是TRUE， 則需要判斷該元素以前的元素的最大覆蓋值是否大圩該元素的下標誌(主要思想是，只要該元素的值不是0，就一定能夠該元素，或者只要是0，如果該元素之前的任一元素得最大覆蓋值能夠越過0，也是可以的)。
 * 兩個問題：
 * 第一個是如果只有一個元素，那麼無論該元素的值是什麼都講能夠到達最後一個元素。
 * 第二個是如果最後一個元素是零，那麼只要能到達最後一個元素即可
 */

class Solution 
{
public:
    bool canJump(vector<int>& nums) 
    {
        if (nums.empty())
        {
            return false;
        }

        if (nums.size() == 1)
        {
            return true; 
        }

        int size = nums.size();
        for (int i=0; i<size; ++i)
        {
            nums[i] = i+nums[i];
        }

        int longest_path = 0;

        for (int i=0; i<size; ++i)
        {
            if ((nums[i] == i) && (i != (size-1)))
            {
                if (longest_path <= i)
                {
                    return false;
                }
            }
            else if (nums[i] > longest_path)
            {
                longest_path = nums[i]; 
            }
        }

        return true;
    }
};

int main()
{
    vector<int> vec = {0};

    class Solution a_class;
    cout << a_class.canJump(vec) << endl;

    return 0;
}
