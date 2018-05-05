// Timothy Rolich
// Cosc 2030, Project 2
// 5/5/18
// main.cpp

#include<vector>
#include<iostream>

using namespace std;
using std::cout;

template <class T>
void QuickSort(vector<T> & vec);

template <class T>
void QuickSortHelper(vector<T> & vec, int first, int last);

template <class T>
int partition(vector<T> & vec, int first, int last);

int main()
{
	vector<char> vec = { 'a','b','g','c','f','a' };
	QuickSort(vec);
	vector<char>::iterator it = vec.begin();
	while (it != vec.end())
	{
		cout << *it;
		cout << endl;
		it++;
	}
	return 0;
}

template<class T>
void QuickSort(vector<T> & vec)
{
	return QuickSortHelper(vec, 0, vec.size() - 1);
}

template <class T>
void QuickSortHelper(vector<T> & vec, int first, int last) 
{
	if (first < last)
	{
		int split = partition(vec, first, last);

		QuickSortHelper(vec, first, split -1);
		QuickSortHelper(vec, split + 1, last);
	}
}
	
template <class T>
int partition(vector<T> & vec, int first, int last)
{
	T pivot = vec[first];

	int left = first + 1;
	int right = last;

	bool done = false;
	while (!done)
	{
		while (left <= right && vec[left] <= pivot)
			left = left + 1;
		while (vec[right] >= pivot && right >= left)
			right = right - 1;

		if (right < left)
			done = true;
		else
		{
			T temp = vec[left];
			vec[left] = vec[right];
			vec[right] = temp;
		}
	}

	T temp = vec[first];
	vec[first] = vec[right];
	vec[right] = temp;

	return right;
}