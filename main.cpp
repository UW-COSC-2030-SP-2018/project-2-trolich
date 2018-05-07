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

void printTF(bool tf)
{
	if (tf)
		cout << "True" << endl;
	else
		cout << "False" << endl;
}

vector<char> getChars(size_t listSize)
{
	vector<char> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(rand());
	}
	return theList;
}
string randString(int size)
{
	string word;
	for (int i = 0; i < size; i++)
	{
		word.push_back(rand());
	}
	return word;
}

int main()
{
	int maxSize = 10000;
	vector<char> vec = getChars(maxSize);
	vector<char> vec2 = vec;
	vector<char> vec3 = vec;

	QuickSort(vec);
	sort(vec2.begin(), vec2.end());
	cout << "Quick sort == stl sort: ";
	printTF((vec == vec2));

	MergeSort(vec3);
	cout << "Merge sort == stl sort == quick sort: ";
	printTF((vec == vec3 && vec2 == vec3));

	cout << "Vector contains w:";
	printTF(binarySearch(vec, 'w'));
	cout << "Vector contains a:";
	printTF(binarySearch(vec, 'a'));

	BloomFilter filter(10000, 5);
	for (int i = 0; i < 100; i++)
	{
		filter.add(randString(i + 1));
	}
	cout << "Bloom filter, size 10000, 100 random words. Possible Collisions:" << endl;
	cout << "hello world: ";
	printTF(filter.contains("hello world"));
	cout << "goodbye: ";
	printTF(filter.contains("goodbye"));
	cout << "abc: ";
	printTF(filter.contains("abc"));

	BloomFilter filter2(100, 2);
	for (int i = 0; i < 100; i++)
	{
		filter2.add(randString(i + 1));
	}
	cout << "Bloom filter, size 100, 100 random words. Possible Collisions:" << endl;
	cout << "hello world: ";
	printTF(filter2.contains("hello world"));
	cout << "goodbye: ";
	printTF(filter2.contains("goodbye"));
	cout << "abc: ";
	printTF(filter2.contains("abc"));
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
