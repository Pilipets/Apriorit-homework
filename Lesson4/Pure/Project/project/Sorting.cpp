#include<iostream>
#include<vector>
#include"Sorting.h"
using std::vector;

void BubbleSort(std::vector<int>& array)
{
	bool continueFlag = false;
	int notSortedAmount = array.size(); //Optimization for the number of comparisons
	//by introducing amount of unsorted elements
	do
	{
		continueFlag = false;
		for (int i = 0; i < notSortedAmount - 1; ++i)
		{
			if (array[i] > array[i + 1])
			{
				int tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;

				continueFlag = true;
			}
		}
		notSortedAmount -= 1; //one more element has taken its place in sorted array

	} while (continueFlag);

}
