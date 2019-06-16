#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum SORT_MODE
{
	BUBBLE = 1,
	SELECT = 2,
	QUICK = 3,
	INSERT = 4,
	HEAP = 5,
	MERGE = 6	
};

void bubble(vector<int> &array)/*{{{*/
{
	int left = 0;
	int right = array.size() - 1;

	for (int i = left; i < right; i++)
	{
		for (int j = left; j < right - i; j++)
		{
			if (array[j + 1] < array[j])
			{
				swap(array[j], array[j + 1]);
			}
		}
	}
}/*}}}*/

//find the least num, change it with the left element
void select(vector<int> &array)/*{{{*/
{
	for (int i = 0; i < array.size() - 1; i++)
	{
		int bigger = array[i];
		int location = i;
		for (int j = i + 1; j < array.size(); j++)	
		{
			if (array[j] < bigger)
			{
				location = j;
				bigger = array[j];	
			}
		}
		if (array[i] != bigger)
		{
			swap(array[i], array[location]);
		}
	}	
}/*}}}*/

//from right to begin
void quick(vector<int> &array, int left, int right)/*{{{*/
{
	if (left >= right)
	{
		return;
	}

	int temp = array[left];
	int first = left;
	int last = right;
	while (left < right)
	{
		while (left < right && array[right] >= temp)
		{
			right--;
		}

		while (left < right && array[left] <= temp)
		{
			left++;
		}
		
		if (left < right)
		{
			swap(array[left], array[right]);
		}

	}
	swap(array[first], array[left]);
	quick(array, first, left - 1);
	quick(array, left + 1, last);
}/*}}}*/

void insert(vector<int> &array)/*{{{*/
{
	for (int i = 0; i < array.size() - 1; i++)
	{
		for (int j = i + 1; j > 0; j--)
		{
			if (array[j] >= array[j - 1])
			{
				break;
			}
			else
			{
				swap(array[j], array[j - 1]);
			}
		}
	}
}/*}}}*/

void heapify(vector<int> &array, int parrent, int size)/*{{{*/
{

	int child = 2 * parrent + 1;
	while (child + 1 <= size)
	{
		if (child + 1 < size && array[child] < array[child + 1])
		{
			child++;
		}
		if (child < size && array[parrent] < array[child])
		{
			swap(array[parrent], array[child]);
		}

		parrent = child;
		child = 2 * parrent + 1;
	}	
}
void heap(vector<int> &array)
{
	int size = array.size();
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		heapify(array, i, size);
	}

	for (int i = size - 1; i > 0; i--)
	{
		swap(array[i], array[0]);
		heapify(array, 0, i);
	}
}/*}}}*/

void merge(vector<int> &array, int left_begin, int left_end, int right_begin, int right_end)
{
	int left_begin_copy = left_begin;
	int size = (left_end - left_begin + 1) + (right_end - right_begin + 1);
	int location = 0;
	vector<int> temp(size);

	while (left_begin <= left_end && right_begin <= right_end)
	{
		if (array[left_begin] <= array[right_begin])
		{
			temp[location++] = array[left_begin++];
		}
		else
		{
			temp[location++] = array[right_begin++];
		}
	}

	while (left_begin <= left_end)
	{
		temp[location++] = array[left_begin++];
	}
	while (right_begin <= right_end)
	{
		temp[location++] = array[right_begin++];
	}

	location = 0;
	for (int i = left_begin_copy; i < size + left_begin_copy; i++)
	{
		array[i] = temp[location++];
	}
}
void split(vector<int> &array, int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) >> 1;
		split(array, left, mid);
		split(array, mid + 1, right);

		merge(array, left, mid, mid + 1, right);
	}	
}

void sort(vector<int> &array, enum SORT_MODE &mode)
{
	switch (mode)
	{
		case BUBBLE:
		{
			bubble(array);
			break;
		}
		
		case SELECT:
		{
			select(array);
			break;
		}

		case QUICK:
		{
			quick(array, 0, array.size() - 1);	
			break;
		}

		case INSERT:
		{
			insert(array);
			break;
		}

		case HEAP:
		{
			heap(array);
			break;
		}

		case MERGE:
		{
			split(array, 0, array.size() - 1);
			break;
		}	

		default:
		{
			cout << "no this mode!!!" << endl;
			break;
		}
	}
}

int main()
{
//	vector<int> array = {54, 42, 4, 128, 40,288, 49};	
	vector<int> array = {54, 4, 128, 40,288, 49};	


	cout << "before sorted: " << endl;
	for (vector<int>::iterator it = array.begin(); it != array.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	enum SORT_MODE mode = HEAP;
	sort(array, mode);

	cout << "mode is " << mode << endl;
	cout << "after sorted: " << endl;
	for (vector<int>::iterator it = array.begin(); it != array.end(); it++)
	{
		cout << *it << " ";;
	}
	cout << endl;


	return 0;
}

