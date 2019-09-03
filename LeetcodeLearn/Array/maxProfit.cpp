#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
        int maxProfit(vector<int> &prices)
        {
                if (prices.size() < 2)
                {
                        return 0;
                }

                int sum = 0;

                int purchase = 0;
                int i = 0;
                while ((i+1) < prices.size())
                {
                        if(prices[i] < prices[i+1])
                        {
                                purchase = prices[i];
                                break;
                        }
                        ++i;
                }

                if ((i+1) == prices.size())
                {
                        return 0;
                }

                while ((i+1) < prices.size())
                {
                        if (prices[i] > prices[i+1])
                        {
                                sum += (prices[i]-purchase);
                                while ((i+1) < prices.size())
                                {
                                        if(prices[i] < prices[i+1])
                                        {
                                                purchase = prices[i];
                                                break;
                                        }
                                        ++i;
                                }
                        }
                        else
                        {
                                ++i;
                        }

                }

                while (prices[i] == prices[i-1])
                {
                    --i;
                }
                if (prices[i] > prices[i-1])
                {
                    sum += (prices[i]-purchase);
                }

                cout << sum << endl;

                return sum;
        }
};

int main()
{
        vector<int> prices = {2,9,2,3,8,1,5,8,4,3,6,4,4};
        class Solution a_class;
        a_class.maxProfit(prices);

        return 0;
}
