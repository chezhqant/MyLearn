#include <iostream>
#include <vector>

using namespace std;

// refer:https://leetcode.com/problems/range-sum-query-immutable/
//这个方法不太好，运行时间太长
class NumArray {
 public:
    NumArray(vector<int>& nums) {
            another_nums=nums;
        }
    
    int sumRange(int i, int j) {
            if (i < 0 || j < 0)
            {
                        return 0;
                    }
            if (i > j)
            {
                        return 0;
                    }
            
            if (j > another_nums.size()-1)
            {
                        return 0;
                    }
            
            if (i == j)
            {
                        return another_nums[i];
                    }
            
            int sum=0;
            while (i <= j)
            {
                        sum += another_nums[i];
                        ++i;
                    }
            
            return sum;
        }
    vector<int> another_nums;
};

int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}
