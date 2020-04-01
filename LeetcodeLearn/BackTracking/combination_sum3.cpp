#include <iostream>
#include <vector>

using namespace std;

// refer: http://lixiaoqiu.com/2018/01/28/算法-回溯法

class Solution {
public:
  vector<vector<int>> combinationSum3(int k, int n) {
    if (k <= 0) {
      return vector<vector<int> >();
    }

    if (k >= n) {
      return vector<vector<int> >();
    }

    if (n <= 0) {
      return vector<vector<int> >();
    }

    const vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  }

  void back_tracking(vector<vector<int> >& ret, int k, int n, int number, int sum, vector<int> vec) {
    if (k == 0) {
      return;
    }

  for (int i = number; i <= 9; ++i) {
    sum += i;

    if (sum < n) {
      vec.push_back(i);
      back_tracking(ret, (k - 1), n, i + 1, sum, vec);
    } else if (sum == n) {
      ret.push_back(vec);
      vec.clear();
      return;
    } else {
      vec.clear();
      return;
    }
  }
};

int main()
{

    
    return 0;
}
