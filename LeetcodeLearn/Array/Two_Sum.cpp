#include <iostream>
#include <vector>
#include <map>

using namespace std;

// refer: https://leetcode.com/problems/two-sum/
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
       if (nums.size() < 2) 
       {
            return vector<int>();
       }

       map<int,int> data_subscript;

       for(int i=0; i<nums.size(); ++i)
       {
            data_subscript.insert(std::pair<int, int>(nums[i], i));
       }

       map<int,int>::iterator left = data_subscript.begin();
       map<int,int>::iterator right = data_subscript.end();

       vector<int> ret;
       while (left->first < right->first)
       {
            int two_sum = left->first + right->first;

            if (two_sum == target)/*{{{*/
            {
                ret.push_back(left->second);
                ret.push_back(right->second);
                ++left;
                --right;
            }/*}}}*/
            else if (two_sum > target)
            {
                --right;
            }
            else
            {
                ++left;
            }
       }
    }
};

int main()
{


    return 0;
}

