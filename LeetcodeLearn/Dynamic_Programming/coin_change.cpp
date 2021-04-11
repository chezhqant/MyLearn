// reference: https://leetcode-cn.com/problems/coin-change/

/*! \brief 按照readme中的讲解，写代码
 *  状态：amount
 *  dp(): 输入一个目前的金额，dp函数返回需要的最少金币数量
 *  最优子结构：对于dp，每次输入一个金额就是一种状态，该状态若是最优的，可以让最终的结果是最优的（自下而上哦）
 *  选择+择优：你选择的金币，不同的金币会导致状态发生改变, 当前选择的金币民面值，使得当前的状态是最优的
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
