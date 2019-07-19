#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution 
{
public:
    vector<int> pancakeSort(vector<int>& A) 
    {
        if (A.empty())
        {
            return vector<int>();
        }

        vector<int> B(A);
        sort(B.begin(), B.end());


        unordered_map<int, int> unorder_vec_idx;
        int size = A.size();
        for (int i=0; i<size; ++i)
        {
            unorder_vec_idx.insert({A[i], i});
        }

        int i = 1;
        vector<int> ret;
        while (i < size-1)
        {
            int right = size-i; 
            int left = unorder_vec_idx[B[right]];

            if (left == right)
            {
                continue;
            }

            vector<int>::iterator left_iter = A.begin()+left;
            vector<int>::iterator right_iter = A.begin()+right;
            if (left_iter == right_iter)
            {
                continue;
            }

            reverse(left_iter, right_iter+1);

            ++i;
            ret.push_back(right-left+1);

            int j=left;
            auto it = unorder_vec_idx.begin();
            for (; j<size; ++j)
            {
                it->first = A[j];
                it->second = j;
                it++;
            }
        }
    }
};

int main()
{
    vector<int> vec = {3,2,4,1};
    class Solution a_class;

    vector<int> another_vec = a_class.pancakeSort(vec);
    for (int i=0; i<another_vec.size(); ++i)
    {
        cout << another_vec[i] << ", ";
    }
    cout << endl;

    return 0;
}
