#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define Min (-pow(2,31))
#define Max (pow(2,31)-1)

class Solution {
public:

    int reverse(int x){
    long int Y=0;
    
    while(x%10 || abs(x)>=10){       
        Y = Y*10 + x%10; 
        x /= 10;       
    }
    
    if(Y< Min || Y>Max)  Y = 0;
    return Y;
    }
};

int main()
{
    int x = -2147483648;
    class Solution a_class;
    cout << a_class.reverse(x) << endl;
    return 0;
}
