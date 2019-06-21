#include <iostream>
#include <vector>

using namespace std;

// 两指针法：从两边向中间走，比较两端的高度，使短的那一端向另一端靠近
/* 这是别人的解释：矩阵的面积与两个因素有关： 
 * 矩阵的长度：两条垂直线的距离 矩阵的宽度：
 * 两条垂直线其中较短一条的长度 因此，要矩阵面积最大化，两条垂直线的距离越远越好，两条垂直线的最短长度也要越长越好。 我们设置两个指针 left 和 right，分别指向数组的最左端和最右端。此时，两条垂直线的距离是最远的，若要下一个矩阵面积比当前 */
/* refer:https://leetcode.com/problems/container-with-most-water/submissions/ */
class Solution {
    public:
    int MaxArea(vector<int>& height) 
    {
        if (height.size() < 1)
        {
            return 0;
        }

        int left = 0;
        int right = height.size() - 1;

        int max_area = 0;
        while (left < right)
        {
            int width = 0;
            bool is_left_shorter = true;

            if (height[left] > height[right])
            {
                width = height[right];
                is_left_shorter = false;
            }
            else
            {
                width = height[left];
            }

            int temp_area = (right-left) * width;
            if (max_area < temp_area)
            {
                max_area = temp_area;    
            }

            if (is_left_shorter)
            {
                ++left;
            }
            else
            {
                --right;
            }
        }

        return max_area;
    }
};

int main()
{
    vector<int> nums = {1,8,6,2,5,4,8,3,7};

    Solution a_sol;
    int max_area = a_sol.MaxArea(nums);

    cout << max_area << endl;

    return 0;
}
