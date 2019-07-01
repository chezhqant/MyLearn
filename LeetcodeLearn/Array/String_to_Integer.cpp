#include <iostream>
#include <string>
#include <limits.h>

using namespace std;

// refer:https://leetcode.com/problems/string-to-integer-atoi/

class Solution {
public:
    int MyAtoi(string str) {
        if(str.empty())
        {
            return 0;
        }
       
        int length = str.length();
        long long ret=0;
        bool is_negative = false;

        // 找出第一個非空的位置
        int i = 0;
        for (; i< length; ++i)
        {
            if (str[i] != ' ')
            {
                break;
            }
        }
        //判斷是否權威空
        if (i == length)
        {
            return 0;
        }

        //判斷第一個位置是否是數字或者正負號
        if (str[i] != '+')
        {
            if ((str[i]<58 && str[i]>47))
            {
                ret = str[i]-'0';
            }
            else if(str[i] != '-')
            {
                return 0;
            }
            else
            {
                is_negative = true;
            }
        }

        //找出連續的數字
        for (++i; i<length; ++i)
        {
            if (str[i]>57 || str[i]<48)
            {
                break;
            }
            ret *= 10;
            if (ret > INT_MAX)//判斷對於有符號整形是否溢出
            {
                break;
            }
            ret += str[i]-'0';
        }

        if (is_negative)
        {
            return ret>INT_MAX ? INT_MIN:-ret;
        }
        else
        {
            return ret>INT_MAX ? INT_MAX:ret;
        }
    }
};

int main()
{
    string str = "+ 42";
    cout << str << endl;
    class Solution a_class;

    cout << a_class.MyAtoi(str) << endl;
    return 0;
}

