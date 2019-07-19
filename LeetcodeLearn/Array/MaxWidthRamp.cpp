#include <iostream>
#include <vector> 
#include <algorithm>

using namespace std;

/*
 * refer: https://leetcode-cn.com/problems/maximum-width-ramp/submissions/
 */

class Solution 
{
public:
    //这种方法提交上去超时
/*{{{
 *     int maxWidthRamp(vector<int>& A) 
 *     {
 *         if (A.empty())
 *         {
 *             return 0;
 *         }    
 * 
 *         int maximum_range = 0;
 *         int size = A.size();
 * 
 *         for (int i=0; i<size-1; ++i)
 *         {
 *             for (int j=size-1; j>(i+maximum_range); --j)
 *             {
 *                 if (A[i] <= A[j])
 *                 {
 *                     cout << A[i] << ", " << A[j] << ", " << maximum_range << endl;
 *                     if (maximum_range < (j-i))
 *                     {
 *                         maximum_range = (j-i);
 *                         break;
 *                     }
 *                 }
 *             }
 *         }
 * 
 *         return maximum_range;
 *     }
 *//*}}}*/

    //这种方法没有超时，但是效果也不太好
    struct Node
    {
        int _value;
        int _idx;

        Node(int value, int idx) : _value(value), _idx(idx)  {}
    };

    static bool Cmp(Node a, Node b)
    {
        if (a._value == b._value)
        {
            return a._idx < b._idx;
        }//必须得有这一步，具体不知道原因,估计跟sort的实现有关系

        return (a._value<=b._value) ? true : false;
    }

    int maxWidthRamp(vector<int> &A)
    {
        if (A.empty())
        {
            return 0;
        }


        int size = A.size();
        vector<Node> vec_node;
        for (int i=0; i<size; ++i)
        {
            vec_node.push_back(Node(A[i], i));
        }

        sort(vec_node.begin(), vec_node.end(), Cmp);

        int min_value_idx = size;
        int max_distance = 0;
        for (int i=0; i<size; ++i)
        {
            max_distance = max(max_distance, vec_node[i]._idx-min_value_idx);
            min_value_idx = min(vec_node[i]._idx, min_value_idx);
        }

        return max_distance;
    }
};

int main()
{
    vector<int> vec = {6,28,25,22,23,22,21,3,20,6,19,19,18,8,12,12,10,9,0,8,8,7,5,4,4,25,1,0,0,0};
    class Solution a_class;
    cout << a_class.maxWidthRamp(vec) << endl;

    return 0;
}
