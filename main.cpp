// Timothy Rolich
// Cosc 2030, Project 2
// 5/5/18
// main.cpp

#include<algorithm>
#include<iostream>
#include "project2.h"

using namespace std;
using std::cout;
using std::sort;
using std::equal;

template <class T>
void QuickSort(vector<T> & vec);

template <class T>
void QuickSortHelper(vector<T> & vec, int first, int last);

template <class T>
int partition(vector<T> & vec, int first, int last);

template <class T>
void MergeSort(vector<T> & vec);

template <class T>
bool binarySearch(vector<T> & vec, T item);

int MyHash(const string word);

int main()
{
	vector<char> vec = { 'a','b','g','c','f','a' };
	vector<char> vec2 = vec;
	vector<char> vec3 = vec;

	QuickSort(vec);
	sort(vec2.begin(), vec2.end());
	cout << (vec == vec2) << endl;

	MergeSort(vec3);
	cout << (vec == vec3 && vec2 == vec3) << endl;

	cout << binarySearch(vec, 'w') << endl;
	cout << binarySearch(vec, 'a') << endl;

	cout << MyHash("hello") << endl;
	cout << MyHash("goodbye") << endl;

	BloomFilter filter(100, 5);
	filter.add("hello world");
	cout << filter.contains("hello world") << endl;
	cout << filter.contains("goodbye") << endl;
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

template <class T>
void MergeSort(vector<T> & vec)
{
	if (vec.size() > 1)
	{
		int mid = vec.size() / 2;
		vector<T> left;
		vector<T> right;
		typename vector<T>::iterator it = vec.begin();
		int w = 0;
		while (it != vec.end())
		{
			if (w < mid)
				left.push_back(*it);
			else
				right.push_back(*it);
			it++; w++;
		}

		MergeSort(left);
		MergeSort(right);

		unsigned int i = 0;
		unsigned int j = 0;
		unsigned int k = 0;
		while ((i < left.size()) && (j < right.size()))
		{
			if (left[i] < right[j])
			{
				vec[k] = left[i];
				i++;
			}
			else
			{
				vec[k] = right[j];
				j++;
			}
			k++;
		}

		while (i < left.size())
		{
			vec[k] = left[i];
			i++;
			k++;
		}

		while (j < right.size())
		{
			vec[k] = right[j];
			j++;
			k++;
		}
	}
}

template <class T>
bool binarySearch(vector<T> & vec, T item)
{
	if (vec.size() == 0)
		return false;
	else if (vec.size() == 1)
		return (vec[0] == item);
	else
	{
		int mid = vec.size() / 2;

		if (vec[mid] == item)
			return true;
		else
		{
			vector<T> left;
			vector<T> right;
			typename vector<T>::iterator it = vec.begin();
			int i = 0;
			while (it != vec.end())
			{
				if (i < mid)
					left.push_back(*it);
				else
					right.push_back(*it);
				it++; i++;
			}
			if (item < vec[mid])
			{
				return binarySearch(left, item);
			}
			else
			{
				return binarySearch(right, item);
			}
		}
	}
}
