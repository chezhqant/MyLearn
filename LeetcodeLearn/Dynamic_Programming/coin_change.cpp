// reference: https://leetcode-cn.com/problems/coin-change/

/*! \brief 按照readme中的讲解，写代码
 *  1. 首先考虑最终要求的结果，最少的硬币能够达到钱数(amount)，所以假设N步是最少个数的硬币能够达到钱数，每次递归就递归一个硬币
 *  2. 状态呢，也就是amount，会驱动硬币数量的累加
 *  3. dp(): 每递归一次，就求出当前状态的最少硬币个数
 *  4. 递归结束的条件
 *  5. 每次递归得到的最少硬币的个数记录下来
 *  6. base case: 初始条件
 */

#include <iostream>
#include <vector>
#include <limits>

using std::vector;

class Solution {
public:

  // dp recursion mode
  int dp_recursion(const vector<int>& coins, int n);

  // dp memo mode
  int dp_memo(const vector<int>& coins, int n);

  // dynamic program mode
  int dp_func(const vector<int>& coins, int n);

  // get the fewest number of coins
  int coin_change(vector<int>& coins, int amount);

private:

  // just for memo
  vector<int> m_memo;

}; // end of class Solution

// 暴力递归的方式
int Solution::dp_recursion(const vector<int>& coins, int n)
{
  if (n < 0)
    return -1;

  if (n == 0)
    return 0;

  int fewest_coins = std::numeric_limits<int>::max() - 1;
  for (int i = 0; i < coins.size(); ++i) {

    const int coin_numbers = dp_recursion(coins, n - coins[i]);
    if (coin_numbers == -1)
      continue;

    fewest_coins = std::min(fewest_coins, 1 + coin_numbers);
  }

  return fewest_coins == std::numeric_limits<int>::max() - 1 ? -1 : fewest_coins;
}

// memo
int Solution::dp_memo(const vector<int>& coins, int n)
{
  if (n < 0)
    return -1;

  if (n == 0)
    return 0;

  if (m_memo[n - 1] != 0)
    return m_memo[n - 1];

  int fewest_coins = std::numeric_limits<int>::max() - 1;
  for (int i = 0; i < n; ++i) {
    dp_memo(coins, i);
  }
  for (int i = 0; i < coins.size(); ++i) {

    const int coin_numbers = dp_memo(coins, n - coins[i]);
    if (coin_numbers == -1)
      continue;

    fewest_coins = std::min(fewest_coins, 1 + coin_numbers);
  }
  m_memo[n - 1] = fewest_coins == std::numeric_limits<int>::max() - 1 ? -1 : fewest_coins;

  return m_memo[n - 1];
}

// dynamic program mode
int Solution::dp_func(const vector<int>& coins, int n)
{
  if (n < 0)
    return -1;

  if (n == 0)
    return 0;

  // 遍历所有情况，包括n，并且取一个永远达不到的值
  vector<int> dp_table(n + 1, n + 1);

  // base case
  dp_table[0] = 0;
  for (int i = 0; i < dp_table.size(); ++i) {
    for (int j = 0; j < coins.size(); ++j) {
      if (i - coins[j] < 0)
        continue;

      dp_table[i] = std::min(dp_table[i], 1 + dp_table[i - coins[j]]);
    }
  }

  return dp_table[n]  == n + 1 ? -1 : dp_table[n];
}

int Solution::coin_change(vector<int>& coins, int amount)
{
  // 暴力递归的方式
  // return dp_recursion(coins, amount);

  // memo mode
  // m_memo.resize(amount);
  // return dp_memo(coins, amount);

  return dp_func(coins, amount);
}

int main()
{
  // case 1
  int amount = 11;
  vector<int> coins{1, 2, 5};

  // case 2
  // int amount = 0;
  // vector<int> coins{1};
  
  // case 3
  // int amount = 3;
  // vector<int> coins{2};

  Solution s;
  std::cout << s.coin_change(coins, amount) << std::endl;

  return 0;
}
