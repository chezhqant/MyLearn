#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
 vector<int> plusOne(vector<int> &digits)
 {
  if (digits.empty())
  {
   return vector<int>();
  }

  int right = digits.size()-1;

  if (digits[right] == 9)
  {
   digits[right] = 0;
  }
  else
  {
   digits[right] += 1;
   return digits;
  }

  for (int i=right-1; i>=0; --i)
  {
   if (digits[i] == 9)
   {
    digits[i] = 0;
   }
   else
   {
    digits[i] += 1;
    break;
   }
  }

  if (digits[0] == 0)
  {
   digits.insert(digits.begin(), 1);
  }

  return digits;
 }
};

int main()
{
 
 int a_array[] = {1,9,9};
 class Solution a_class;
 vector<int> vec(a_array, a_array+sizeof(a_array)/sizeof(int));
 a_class.plusOne(vec);

 for (int i=0; i<vec.size(); ++i)
  {
   cout << vec[i] << " ";
  }
  cout << endl;

 return 0;
}
