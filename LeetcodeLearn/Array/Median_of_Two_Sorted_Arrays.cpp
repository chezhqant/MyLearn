#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    //第一种方法，LeetCode效果不佳
    void merge(vector<int> &nums, int left_begin, int left_end, int right_begin, int right_end)
    {
        int left_begin_copy = left_begin; 

        int size = (left_end-left_begin+1) + (right_end-right_begin+1);
        vector<int> temp;

        while ((left_begin<=left_end) && (right_begin<=right_end))
        {
            if (nums[left_begin] < nums[right_begin])
            {
                temp.push_back(nums[left_begin++]);
            }
            else
            {
                temp.push_back(nums[right_begin++]);
            }
        }

        while (left_begin <= left_end)
        {
            temp.push_back(nums[left_begin++]);
        }
        while (right_begin <= right_end)
        {
            temp.push_back(nums[right_begin++]);
        }

        for (int i=0; i< size; ++i)
        {
            nums[left_begin_copy+i] = temp[i];
        }
    }
    void split(vector<int> &nums, int left, int right)
    {
        if (left < right) 
        {
            int mid = (left+right) >> 1;
            split(nums, left, mid);
            split(nums, mid+1, right);

            merge(nums, left, mid, mid+1, right);
        }
    }
    double FindMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
    {
        nums1.insert(nums1.begin(), nums2.begin(), nums2.end());
        
        int left = 0;
        int right = nums1.size() - 1;
        cout << "right=" << right << endl;

        split(nums1, left, right);

        if ((right+1)%2 == 0)
        {
            return double(nums1[right/2]+nums1[right/2+1])/2;
        }
        else
        {
            return double(nums1[right/2]);
        }
    }


    //第二种方法
    //想象一下，两个已经排序好的数组，找出第K大(不是数组的下标)的数字，同时对两个数组取第(k/2)大的数(有可能某个数组还没有k/2大，所以取nums1_median=min(k/2, nums1_size)),两者的比较:
    //nums1[nums1_median-1]>nums2[nums2_median-1],此时将nums2[nums_median]左边的数都删除掉
    //同理nums1[nums1_median-1]>nums2[nums2_median-1];
    //如果两者相等，则两者任一都是我们要找的第K大的数字
    double FindMedianSortedArrays(vector<int>::iterator nums1, int nums1_size, vector<int>::iterator nums2, int nums2_size, int k)
    {
        if (nums1_size>nums2_size)//确保长度更大的数组，在参数表的第三项
        {
            return FindMedianSortedArrays(nums2, nums2_size, nums1, nums1_size, k);
        }

        if (nums1_size == 0)//这个长度小，最有可能是0
        {
            return *(nums2+k-1);
        }
        if (k == 1)//找出两者的第0项哪个最大
        {
            return min(*nums1, *nums2);
        }

        int nums1_median = min(k / 2, nums1_size);//因为两者中最短的数组长度不一定大于k/2
        int nums2_median = k - nums1_median;//上面的要查找的个数为nums1_median，那个另一个数组要查找的个数就为总个数K-nums1_median

        if (nums1[nums1_median-1] > nums2[nums2_median-1])//谁的中间数小，就删除其左边的数值
        {
            return FindMedianSortedArrays(nums1, nums1_size, nums2+nums2_median, nums2_size-nums2_median, nums1_median);
        }
        else if (nums1[nums1_median-1] < nums2[nums2_median-1])
        {
            return FindMedianSortedArrays(nums1+nums1_median, nums1_size-nums1_median, nums2, nums2_size, nums2_median);
        }
        else
        {
            return *(nums1+nums1_median-1);
        }
    }
    double FindMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int nums1_size = nums1.size();
        int nums2_size = nums2.size();

        if ((nums1_size+nums2_size) & 0x1)//两者大小之和为基数，则直接查找
        {
            return FindMedianSortedArrays(nums1.begin(), nums1_size, nums2.begin(), nums2_size, (nums1_size+nums2_size)/2+1);
        }
        else
        {
            return (FindMedianSortedArrays(nums1.begin(), nums1_size, nums2.begin(), nums2_size, (nums1_size+nums2_size)/2) + FindMedianSortedArrays(nums1.begin(), nums1_size, nums2.begin(), nums2_size, (nums1_size+nums2_size)/2+1))/2;//两者大小之和为偶数，则要查找中间的两个数字

        }
    }
};

int main()
{
    vector<int> nums1 = {23,490,7823};
    vector<int> nums2 = {67, 128, 273};

    class Solution a_class;
    cout << a_class.FindMedianSortedArrays(nums1, nums2) << endl;

    /*
     * for (int i=0; i<nums1.size(); ++i)
     * {
     *     cout << nums1[i] << endl;
     * }
     */
    return 0;
}

