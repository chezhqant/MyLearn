#include <iostream>
#include <vector>

using namespace std;

/*
 * // refer:https://leetcode.com/problems/duplicate-zeros/
 * 首先一个循环，找到是否有0,没有0就直接返回;有0的话，就让size这个变量减1，因为没检测到一个0，就意味着size-1这个位置被复制的0占掉了。并且要知道，在这个循环中的(i+1)=size的时候，几遍arr[i]==0是TRUE，这时候这个0也无法复制！！！
 * 再有一个循环，从后往前复制，令i=(size-1); j=arr.size()-1;首先得判断arr[size-1]是不是0,如果是0，这时候这个0是不参与复制的。其他的如果遇到0，复制之后，添加一个0即可，如果没有遇到，直接复制。
 * 这个题的难点在于从后往前复制的时候(第二个循环)，究竟会不会使i>j?????很明显是不会的。为什么不会我讲不出来
 */

class Solution {
    public:
    void duplicateZeros(vector<int>& arr) 
    {
        if (arr.empty())
        {
            return;
        }


        int zero_nums = 0;
        int size = arr.size();
        bool last_is_zero = false;

        if (size > 10000)
        {
            return;
        }

        for (int i=0; i<size; ++i)
        {
            if (arr[i] == 0)
            {
                ++zero_nums;
                
                if ((i+1) == size)
                {
                    last_is_zero = true;
                    break;
                }
                --size;
            }
        }

        if (!zero_nums)
        {
            return;
        }

        int i = size-1;
        int j = arr.size()-1;
        if (last_is_zero)
        {
            arr[j--] = arr[i--];
        }

        for (; i>=0; --i, --j)
        {
            arr[j] = arr[i];

            if (arr[i] == 0)
            {
                --j;
                arr[j] = 0;
            }
        }
    }
};

int main()
{
    vector<int> nums = {8,4,5,0,0,0,0,7};

    class Solution a_class;

    a_class.duplicateZeros(nums);

    for (int i=0; i<nums.size(); ++i)
    {
        cout << nums[i] << " ";
    }
    cout << endl;
    return 0;
}
