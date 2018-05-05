// Timothy Rolich
// Cosc 2030, Project 2
// 5/5/18
// main.cpp

#include<vector>
#include<iostream>

using namespace std;

template <typename T>
vector<T> QuickSort(vector<T> vec);

int main()
{
	return 0;
}

template <typename T>
vector<T> QuickSort(vector<T> vec) {
	vector<T> sorted = vec;

	if (sorted.size() > 1)
	{
		T pivot = vec[0];
		int leftMark = 1;
		int rightMark = vec.size() - 1;

		bool done = false;
		while (!done)
		{
			while (leftMark <= rightMark && sorted[leftMark] <= pivot)
				leftMark++;
			while (sorted[rightMark] >= pivot && rightMark >= leftMark)
				rightMark--;

			if (rightMark < leftMark)
				done = true;
			else // Switch leftMark and rightMark values
			{
				T temp = sorted[leftMark];
				sorted[leftMark] = sorted[rightMark];
				sorted[rightMark] = temp;
			}
		}

		// Switch rightMark with the pivot
		T temp = pivot;
		pivot = sorted[rightMark];
		sorted[rightMark] = temp;


		// Split vector into 3, left, pivot, right
		vector<T> left;
		vector<T> middle;
		vector<T> right;
		typename vector<T>::iterator it = sorted.begin();
		while (it != sorted.end())
		{
			if (*it < pivot)
			{
				left.push_back(*it);
			}
			else if (*it > pivot)
			{
				right.push_back(*it);
			}
			else
			{
				middle.push_back(*it);
			}
			it++;
		}

		// Sort left and right
		left = QuickSort(left);
		right = QuickSort(right);
		sorted.clear();

		// Concatenate vectors and pivot
		it = left.begin();
		while (it != left.end())
		{
			sorted.push_back(*it);
			it++;
		}
		it = middle.begin();
		while (it != middle.end())
		{
			sorted.push_back(*it);
			it++;
		}
		it = right.begin();
		while (it != right.end())
		{
			sorted.push_back(*it);
			it++;
		}

	}
	return sorted;
}