#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
public:
        vector<vector<int> > subsetWithDup(vector<int> &nums)
        {
                if (nums.empty())
                {
                        return vector<vector<int> > ();
                }

                sort(nums.begin(), nums.end());

                vector<vector<int> > ret(1, vector<int>());
                vector<int> temp(1,nums[0]);
                ret.push_back(temp);

                int size = ret.size();
                int same_times = 1;
                for (int j=1; j<nums.size(); ++j)
                {
                        if (nums[j] != nums[j-1])
                        {
                            same_times = 1;
                            for (int i=0; i<size; ++i)
                            {
                                vector<int> temp(ret[i]);
                                temp.push_back(nums[j]);
                                ret.push_back(temp);
                            }
                        }
                        else
                        {
                            ++same_times;
                            int k = 0;
                            for (; k<size; ++k)
                            {
                                vector<int> temp(ret[k]);
                                temp.push_back(nums[j]);

                                if ((temp.size()==same_times) && (temp[0]==temp[temp.size()-1]))
                                {
                                    break;
                                }
                            }
                            for (; k<size; ++k)
                            {
                                vector<int> temp(ret[k]);
                                temp.push_back(nums[j]);
                                ret.push_back(temp);
                            }
                        }

                        size = ret.size();
                }

                for (int i=0; i<ret.size(); ++i)
                {
                        for (int j=0; j<ret[i].size(); ++j)
                        {
                                cout << ret[i][j] << ",";
                        }
                        cout << endl;
                }

                return ret;
        }
};

int main()
{
        vector<int> nums = {4,4,4,1,4};
        class Solution a_class;
        a_class.subsetWithDup(nums);


        return 0;
}
