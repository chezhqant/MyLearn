#include <iostream>
#include <vector>

using namespace std;

/*! \brief problem: https://leetcode-cn.com/problems/1-bit-and-2-bit-characters/
 * 解题方法一：倒推法
 * 1. 若bits长度为0，return false
 * 2. 若bits长度为1，return true
 * 3. 若bits长度>=2，从后往前推：
 *    1. 若最后一位是1，则bits肯定不是1bit字符
 *    2. 若最后一位是0，判断连续的1的个数是否为偶数：
 *       1. 若倒数第二位为0，则肯定是1bit字符
 *       2. 若倒数第二位是1，判断1的连续个数是否为偶数，若为偶数，则为1bit字符；若为奇数，则为2bit字符
 */
/* class Solution { */
// public:

  /* ! \brief 判断bits的1的连续数量是否为偶数
   * param bits:      传入的bits数组
   * param pos:       pos的位置为倒数第三位
   * return:          若数量为偶数，则返回true，否则为奇数
   */
  // bool is_odd(const vector<int>& bits, const int pos)
  // {
    // int nums = 1;
    // for (int i = pos; i >= 0; --i) {
      // if (bits[i] == 1)
        // ++nums;
      // else
        // break;
    // }

    // return (nums % 2 == 0) ? true : false;
  // }

  // bool isOneBitCharacter(vector<int>& bits) {
    // if (bits.size() == 0)
      // return false;

    // if (bits.size() == 1)
      // return true;

    // const int length = bits.size();
    // // 倒数第二位
    // const int pos = length - 2;
    // if (bits[pos] == 0)
      // return true;
    // else
      // return is_odd(bits, pos-1);
  // }
/* }; */

/*! \brief 正推法：遍历即可
 * 只遍历bits.size()-2，也就是说倒数第二个:
 * 如果为1，则到最后一位为10或者11；
 * 如果为0，则到最后一位为00
 */
class Solution {
public:
  bool isOneBitCharacter(vector<int>& bits) {
    if (bits.size() == 0)
      return false;
    
    if (bits.size() == 1)
      return true;

    int i = 0;
    int num = -1;
    for (; i < bits.size() - 1; ++i)
      if (bits[i] == 1)
        ++i;

    return (i == bits.size()) ? false : true;
  }
};

int main()
{
  // std::vector<int> bits = {1, 0, 0};
  std::vector<int> bits({1, 1, 1, 0});
  class Solution demo;
  std::cout << demo.isOneBitCharacter(bits) << std::endl;
  
  return 0;
}

