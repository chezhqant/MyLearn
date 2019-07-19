#include <iostream>
#include <vector>

/*
 * refer:https://leetcode.com/problems/height-checker/submissions/
 * 排序比较两个vector每个值是否一样即可
 */

using namespace std;

class Solution {
    public:
    int heightChecker(vector<int>& heights) {
            if (heights.empty())
            {
                return 0;
            }
            
            vector<int> heights_copy(heights);
            int size = heights.size();
            for (int i=0; i<size; ++i)
            {
                for (int j=i+1; j>0; --j)
                {
                    if (heights_copy[j] >= heights_copy[j-1])
                    {
                        break;
                    }
                    else
                    {
                        swap(heights_copy[j-1], heights_copy[j]);
                    }
                }
            }

            int has_numbers_not_conformance = 0;
            for (int i=0; i<size; ++i)
            {
                if (heights[i] != heights_copy[i])
                {
                    ++has_numbers_not_conformance;
                }
            }

            return has_numbers_not_conformance;
        }
};

int main()
{
    vector<int> vec = {1,1,4,2,1,3};
    class Solution a_class;

    cout << a_class.heightChecker(vec) << endl;

    return 0;
}
