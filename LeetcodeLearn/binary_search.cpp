#include <iostream>

using namespace std;

int BinarySearch(int a_Array[], int number, int length)
{
	int high = length - 1;
	int low = 0;
	
	while(low <= high)
	{
		int mid = (high + low) / 2;
		
		if (a_Array[mid] = number)
		{
			return mid;
		}
		else if (a_Array[mid] < number)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}
	
	return -1;
}

//二分查找，递归版本
int BinarySearch(int a_Array[], int number, int low, int high)
{
	int mid = low + (high - low) / 2;
	
	if (a_Array[mid] == number)
	{
		return mid;
	}
	
	if (a_Array[mid] < number)
	{
		return BinarySearch(a_Array, number, low, mid - 1);
	}
	
	if (a_Array[mid] > number)
	{
		return BinarySearch(a_Array, number, mid + 1, high);
	}
}

int main()
{
	return 0;
}
