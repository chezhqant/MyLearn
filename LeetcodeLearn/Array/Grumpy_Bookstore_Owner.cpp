#include <iostream>
#include <vector>

using namespace std;

/*
 * refer:https://leetcode.com/problems/grumpy-bookstore-owner/submissions/
 * 对于grumpy[i] = 0的时间点，显然客户都是满意的，遍历customers可以把所有这些客户的数量求和，同时把对于的customers[i] 设成0。例如示例1中的customers = [1,0,1,2,1,1,7,5]，经过操作后变成 [0,0,0,2,0,1,0,5]。接下来就是问题就转换成求customers中长度为X的连续子数组的和的最大值，最后把第一步的中的和加上第二部操作中的最大值即为结果。
 */

class Solution 
{
 public:
    int maxSatisfied(vector<int>&customers, vector<int>&grumpy, int X) 
    {
        if (customers.empty())
        {
            return 0;
        }

        if (customers.size() == 1)
        {
            return customers[0];
        }


        int sum = 0;
        int size = customers.size();
        for (int i=0; i<size; ++i)
        {
            if (!grumpy[i])
            {
                sum += customers[i];
                customers[i] = 0;
            }
        }

        if (X >= size)
        {
            for (int i=0; i<size; ++i)
            {
                if (grumpy[i])    
                {
                    sum += customers[i];
                }
            }
            return sum;
        }

        int max = 0;
        for (int i=0; i<=size-X; ++i)
        {
            int x = X;
            int temp = 0;
            while (x>0)
            {
                temp += customers[i+x-1];
                --x;
            } 
            
            if (max < temp)
            {
                max = temp;
            }

            temp = 0;
        }
        return sum+max;
    }
};

int main()
{
    /* vector<int> customers = {9, 10, 4, 5};
    vector<int> grumpy = {1,0,1,1};  */
    vector<int> customers = {1,0,1,2,1,1,7,5};
    vector<int> grumpy = {0,1,0,1,0,1,0,1};
    /* vector<int> customers = {2,4,1,4,1};
    vector<int> grumpy = {1,0,1,0,1};  
    vector<int> customers = {4,10,10};
    vector<int> grumpy = {1,1,0};*/


    int X = 3;

    class Solution a_class;
    cout << endl;
    cout << a_class.maxSatisfied(customers, grumpy, X) << endl;

    return 0;
}
