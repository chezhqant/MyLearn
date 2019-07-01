#include <iostream>
#include <string>

using namespace std;

/*{{{
 * eg: PAYPALISHIRING 
 * 
 * 3行
 * 0   4   8    12
 * 1 3 5 7 9 11 13
 * 2   6   10 
 * 4行
 * 0         6          12
 * 1     5   7      11  13//a_loop=(numRows*2-2);5距離1的距離為(a_loop-i(行)*2),5距離7的距離為(a_loop-(5距離1的距離))
 * 2  4      8  10
 * 3         9  
 * 5行
 * 0           8               16
 * 1        7  9           15  17           23
 * 2     6     10      14      18       22
 * 3  5        11  13          19   21
 * 4           12              20
 * 觀察，第一行和最後一行間距都是(numRows+(numRows-2))
 * 第二行至倒數第二行之間的每行，每個數字都可由前面的數字得出
 *//*}}}*/

// refer:https://leetcode.com/problems/zigzag-conversion/submissions/
class Solution {
    public:
    string Convert(string s, int numRows) 
    {
        if (s.empty())
        {
            return string(); 
        }

        // 如果只要求一行，組成不了"Z"
        if (numRows <= 1)
        {
            return s;
        }

        int a_loop = numRows*2 - 2;
        int length = s.length();
        string ret_str;

        // 第一行
        int sub=0;
        while (sub < length)
        {
            ret_str += s[sub];
            sub += (a_loop);
        }

        // 第二行至倒數第二行
        for (int i=1; i<numRows-1; ++i)
        {
            sub = i;

            // 比如前面的例子中"4行"，1, 5,7, 11,13,對於sub=1來說，左邊距離是left_interval,比如4；右邊距離(a_loop-左邊距離),比如2
            int left_interval = a_loop - i*2;
            int right_interval = a_loop - left_interval;
            while (sub < length)
            {
                ret_str += s[sub];
                sub += left_interval;
                if (sub < length)
                {
                    ret_str += s[sub];
                }
                else
                {
                    break;
                }
                sub += right_interval;
            }
        }

        //最後一行
        sub = numRows-1;
        while (sub < length)
        {
            ret_str += s[sub];
            sub += a_loop;
        }

        return ret_str;
    }
};

int main()
{
    //string a_str = "PAYPALISHIRING";
    string a_str = "AB";

    class Solution a_class;

    cout << a_class.Convert(a_str, 1) << endl;

    return 0;
}
