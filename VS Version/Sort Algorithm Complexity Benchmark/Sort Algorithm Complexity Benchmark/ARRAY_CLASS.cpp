#include "ARRAY_CLASS.h"

//
//  ARRAY_CLASS.cpp
//  Algorithm-Time-Complexity
//
//  Created by Bryce Remick on 2/25/18.
//  Copyright © 2018 Bryce Remick. All rights reserved.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <ratio>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace chrono;

//Namespace containing functions to assist in measuring/calculating array sort times
namespace Array_Helpers {

	//Function to display an array
	template <class T>
	void dispArr(T[], int);

	//Function to copy an array into an array called 'copyArr'
	template <class T>
	void copyArr(T[], T[], int);

	//Insertion sort algorithm
	template <class T>
	void insertionSort(T[], int);

	//Selection sort algorithm
	template <class T>
	void selectionSort(T[], int);

	//Bubble sort algorithm
	template <class T>
	void bubbleSort(T[], int);

	//Quick sort algorithm
	template <class T>
	void quickSort(T[], int, int);

	//Mege sort algorithm
	template <class T>
	void mergeSort(T[], int, int);

	//Merge sort helper function
	template <class T>
	void merge(T[], int, int, int);

	//Function to display an array.
	//Accepts a template array pointer and an int as parameters
	template <class T>
	void dispArr(T arr[], int SIZE)
	{
		for (int i = 0; i < SIZE; i++) {
			cout << setw(5) << arr[i] << " ";
			if ((i + 1) % 10 == 0)
				cout << endl;
		}
	}
	//Function to copy array into a temp array, defined in ARRAY_CLASS as copyArr.
	//Accepts two template array pointers, and array size as parameters
	template <class T>
	void copyArr(T arr[], T arrCopy[], int SIZE)
	{
		for (int i = 0; i < SIZE; i++)
			arrCopy[i] = arr[i];
	}
	//Function to insertion sort an array
	//Accepts a pointer to an array, and array size as parameter.
	template <class T>
	void insertionSort(T arr[], int SIZE)
	{
		int i, j;
		T key;
		//inner loop to loop through array
		for (i = 1; i < SIZE; i++)
		{
			//key equal current array position
			key = arr[i];
			j = i - 1;

			while (j >= 0 && arr[j] > key)
			{
				//
				arr[j + 1] = arr[j];
				j = j - 1;
			}
			arr[j + 1] = key;
		}
	}
	//Function to selection sort an array
	//Accepts a pointer to an array, and array size as parameter.
	template <class T>
	void selectionSort(T arr[], int SIZE)
	{
		int pos_min;
		T temp;
		for (int i = 0; i < SIZE - 1; i++)
		{
			pos_min = i;
			for (int j = i + 1; j < SIZE; j++)
			{
				if (arr[j] < arr[pos_min])
					pos_min = j;
			}
			if (pos_min != i)
			{
				temp = arr[i];
				arr[i] = arr[pos_min];
				arr[pos_min] = temp;
			}
		}
	}
	//Function to bubble sort an array
	//Accepts a pointer to an array, and array size as parameter.
	template <class T>
	void bubbleSort(T arr[], int SIZE)
	{
		bool swapped = true;
		int j = 0;
		T tmp;
		while (swapped)
		{
			swapped = false;
			j++;
			for (int i = 0; i < SIZE - j; i++)
			{
				if (arr[i] > arr[i + 1])
				{
					tmp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = tmp;
					swapped = true;
				}
			}
		}
	}
	//Function to quick sort an array
	//Accepts a pointer to an array, and two integers as parameters
	//int left: farthest left index of array, int right: farthest right index of array
	template <class T>
	void quickSort(T arr[], int left, int right)
	{
		//copy left and right indexes into temp variable for looping
		int i = left, j = right;
		//Temporary value for swapping
		T tmp;
		//determine the pivot value in the array
		T pivot = arr[(left + right) / 2];

		//---Partition---
		//while left is <= right
		while (i <= j) {

			//traverse from right towards pivot
			while (arr[i] < pivot)
				i++;

			//traverse fro left towards pivot
			while (arr[j] > pivot)
				j--;

			//if left value is <= right value then swap
			if (i <= j) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
				i++;
				j--;
			}
		};

		//perform quick sort on left partition
		if (left < j)
			quickSort(arr, left, j);

		//perform quick sort on right partition
		if (i < right)
			quickSort(arr, i, right);
	}
	//Function to perform merge sort on an array
	//Accepts a pointer to an array, and two integers as parameters
	//int l: left index of array. int r: right index of array
	template <class T>
	void mergeSort(T arr[], int l, int r)
	{
		if (l < r)
		{
			// Same as (l+r)/2, but avoids overflow for
			// large l and h
			int m = l + (r - l) / 2;

			// Sort first and second halves
			mergeSort(arr, l, m);
			mergeSort(arr, m + 1, r);

			merge(arr, l, m, r);
		}
	}
	//Function to merge arrays back into one, after being partitioned
	//Accepts a pointer to an array, and 3 integers as parameters
	//int l: left index. int m: middle index. int r: right index
	template <class T>
	void merge(T arr[], int l, int m, int r)
	{
		int i, j, k;
		int n1 = m - l + 1;
		int n2 = r - m;

		/* create temp arrays */
		T *L = new T[n1];
		T *R = new T[n2];

		/* Copy data to temp arrays L[] and R[] */
		for (i = 0; i < n1; i++)
			L[i] = arr[l + i];
		for (j = 0; j < n2; j++)
			R[j] = arr[m + 1 + j];

		/* Merge the temp arrays back into arr[l..r]*/
		i = 0; // Initial index of first subarray
		j = 0; // Initial index of second subarray
		k = l; // Initial index of merged subarray
		while (i < n1 && j < n2)
		{
			if (L[i] <= R[j])
			{
				arr[k] = L[i];
				i++;
			}
			else
			{
				arr[k] = R[j];
				j++;
			}
			k++;
		}

		/* Copy the remaining elements of L[], if there
		are any */
		while (i < n1)
		{
			arr[k] = L[i];
			i++;
			k++;
		}

		/* Copy the remaining elements of R[], if there
		are any */
		while (j < n2)
		{
			arr[k] = R[j];
			j++;
			k++;
		}

		delete[] L;
		delete[] R;
		L = NULL;
		R = NULL;
	}

	
}
//Constructor function to initialize all arrays and then populate them
template <class T>
ARRAY_CLASS<T>::ARRAY_CLASS(int x)
{
	//create the size of arrays
	SIZE = x;

	//create random number generator seed
	srand(time(NULL));

	//create temp sort time arrays
	insertionSortTimes = new double[100];
	selectionSortTimes = new double[100];
	bubbleSortTimes = new double[100];
	quickSortTimes = new double[100];
	mergeSortTimes = new double[100];

	//create permanent sort time arrays
	allInsertionSortTimes = new double[400];
	allSelectionSortTimes = new double[400];
	allBubbleSortTimes = new double[400];
	allQuickSortTimes = new double[400];
	allMergeSortTimes = new double[400];

	//create arrays that will be sorted
	sortedArr = new T[SIZE];
	shuffledArr = new T[SIZE];
	reversedArr = new T[SIZE];
	tenPercentArr = new T[SIZE];
	arrCopy = new T[SIZE];

	cout << "Building Arrays[" << SIZE << "]..." << endl;

	//Populate sorted array
	for (int i = 0; i < SIZE; i++)
		sortedArr[i] = i;

	//Populate shuffled array
	for (int i = 0; i < SIZE; i++)
		shuffledArr[i] = (rand() % SIZE) + 1;

	//Populate reversed array
	int j = 0;
	for (int i = (SIZE - 1); i >= 0; i--)
	{
		reversedArr[j] = i;
		j++;
	}

	//Populate 10% shuffled array
	for (int i = 0; i < SIZE; i++)
	{
		if (i < (SIZE * .10))
			tenPercentArr[i] = (rand() % SIZE) + 1;
		else
			tenPercentArr[i] = i;
	}


}
//Destructor function to delete all arrays and set array pointers to NULL
template <class T>
ARRAY_CLASS<T>::~ARRAY_CLASS()
{
	//Delete all arrays
	delete[] sortedArr;
	delete[] shuffledArr;
	delete[] reversedArr;
	delete[] tenPercentArr;
	delete[] arrCopy;

	delete[] insertionSortTimes;
	delete[] selectionSortTimes;
	delete[] bubbleSortTimes;
	delete[] quickSortTimes;
	delete[] mergeSortTimes;

	delete[] allInsertionSortTimes;
	delete[] allSelectionSortTimes;
	delete[] allBubbleSortTimes;
	delete[] allQuickSortTimes;
	delete[] allMergeSortTimes;

	//Set array pointers to NULL
	sortedArr = NULL;
	shuffledArr = NULL;
	reversedArr = NULL;
	tenPercentArr = NULL;
	arrCopy = NULL;

	insertionSortTimes = NULL;
	selectionSortTimes = NULL;
	bubbleSortTimes = NULL;
	quickSortTimes = NULL;
	mergeSortTimes = NULL;

	allInsertionSortTimes = NULL;
	allSelectionSortTimes = NULL;
	allBubbleSortTimes = NULL;
	allQuickSortTimes = NULL;
	allMergeSortTimes = NULL;
}
//Function to display pre sorted arrays
template <class T>
void ARRAY_CLASS<T>::dispArrays()
{
	cout << endl << "Sorted Array" << "[" << SIZE << "]:" << endl;
	Array_Helpers::dispArr(sortedArr, SIZE);
	cout << endl << "Shuffled Array" << "[" << SIZE << "]:" << endl;
	Array_Helpers::dispArr(shuffledArr, SIZE);
	cout << endl << "Reversed Array" << "[" << SIZE << "]:" << endl;
	Array_Helpers::dispArr(reversedArr, SIZE);
	cout << endl << "10% Shuffled Array" << "[" << SIZE << "]:" << endl;
	Array_Helpers::dispArr(tenPercentArr, SIZE);
}
//Function that sorts arrays and measures the time it takes.
//The times are stored into arrays and variables
//and then manipulated to find the averages and standard deviations.
template <class T>
void ARRAY_CLASS<T>::performTests()
{
	//--------------------------------------Sorted Array----------------------------------------------
	//calculate sort times for the sorted array
	cout << "Sorting the Sorted Array[" << SIZE << "] x 100" << endl;
	for (int i = 0; i < 100; i++)
	{
		if (i % 2 == 0)
			cout << "#";
		//----------------------------Sorted Insertion Sort----------------------------------
		//copy original array, so as not to change original values
		Array_Helpers::copyArr(sortedArr, arrCopy, SIZE);
		//set a start time time_point
		high_resolution_clock::time_point startTime = high_resolution_clock::now();
		//perform sorting algorithm on copied array
		Array_Helpers::insertionSort(arrCopy, SIZE);
		//set an end time time_point
		high_resolution_clock::time_point endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time (in microseconds)
		duration<double, std::micro> duration = endTime - startTime;
		//store elapsed time into temp array
		insertionSortTimes[i] = duration.count();

		//----------------------------Sorted Selection Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(sortedArr, arrCopy, SIZE);
		//set a start time time_point
		startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::selectionSort(arrCopy, SIZE);
		//set an end time time_point
		endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration = endTime - startTime;
		//store elapsed time into array
		selectionSortTimes[i] = duration.count();

		//----------------------------Sorted Bubble Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(sortedArr, arrCopy, SIZE);
		//set a start time time_point
		startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::bubbleSort(arrCopy, SIZE);
		//set an end time time_point
		endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration = endTime - startTime;
		//store elapsed time into array
		bubbleSortTimes[i] = duration.count();

		//----------------------------Sorted Quick Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(sortedArr, arrCopy, SIZE);
		//set a start time time_point
		startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::quickSort(arrCopy, 0, SIZE - 1);
		//set an end time time_point
		endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration = endTime - startTime;
		//store elapsed time into array
		quickSortTimes[i] = duration.count();

		//----------------------------Sorted Merge Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(sortedArr, arrCopy, SIZE);
		//set a start time time_point
		startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::mergeSort(arrCopy, 0, SIZE - 1);
		//set an end time time_point
		endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration = endTime - startTime;
		//store elapsed time into array
		mergeSortTimes[i] = duration.count();
	}
	cout << endl;

	//temporary variables for adding
	double t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0;
	//for-loop to loop through the temp sort-time arrays
	for (int i = 0; i < 100; i++)
	{
		//add each element of array to temp variables
		t1 += insertionSortTimes[i];
		t2 += selectionSortTimes[i];
		t3 += bubbleSortTimes[i];
		t4 += quickSortTimes[i];
		t5 += mergeSortTimes[i];
	}
	//for-loop to loop through permanent sort-time arrays
	for (int i = 0; i < 100; i++)
	{
		//permanently store the sort times
		allInsertionSortTimes[i] = insertionSortTimes[i];
		allSelectionSortTimes[i] = selectionSortTimes[i];
		allBubbleSortTimes[i] = bubbleSortTimes[i];
		allQuickSortTimes[i] = quickSortTimes[i];
		allMergeSortTimes[i] = mergeSortTimes[i];
	}
	//calculate the average/mean of each sorting method for a sorted array
	sortedInsertionAvg = t1 / 100;
	sortedSelectionAvg = t2 / 100;
	sortedBubbleAvg = t3 / 100;
	sortedQuickAvg = t4 / 100;
	sortedMergeAvg = t5 / 100;

	//-----------------------------------Shuffled Array---------------------------------
	//calculate sort times for the sorted array
	cout << endl << "Sorting the Shuffled Array[" << SIZE << "] x 100" << endl;
	for (int i = 0; i < 100; i++)
	{
		if (i % 2 == 0)
			cout << "#";
		//----------------------------Shuffled Insertion Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(shuffledArr, arrCopy, SIZE);
		//set a start time time_point
		high_resolution_clock::time_point startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::insertionSort(arrCopy, SIZE);
		//set an end time time_point
		high_resolution_clock::time_point endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration<double, std::micro> duration = endTime - startTime;
		//store elapsed time into array
		insertionSortTimes[i] = duration.count();

		//----------------------------Shuffled Selection Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(shuffledArr, arrCopy, SIZE);
		//set a start time time_point
		startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::selectionSort(arrCopy, SIZE);
		//set an end time time_point
		endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration = endTime - startTime;
		//store elapsed time into array
		selectionSortTimes[i] = duration.count();

		//----------------------------Shuffled Bubble Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(shuffledArr, arrCopy, SIZE);
		//set a start time time_point
		startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::bubbleSort(arrCopy, SIZE);
		//set an end time time_point
		endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration = endTime - startTime;
		//store elapsed time into array
		bubbleSortTimes[i] = duration.count();

		//----------------------------Shuffled Quick Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(shuffledArr, arrCopy, SIZE);
		//set a start time time_point
		startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::quickSort(arrCopy, 0, SIZE - 1);
		//set an end time time_point
		endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration = endTime - startTime;
		//store elapsed time into array
		quickSortTimes[i] = duration.count();

		//----------------------------Shuffled Merge Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(shuffledArr, arrCopy, SIZE);
		//set a start time time_point
		startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::mergeSort(arrCopy, 0, SIZE - 1);
		//set an end time time_point
		endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration = endTime - startTime;
		//store elapsed time into array
		mergeSortTimes[i] = duration.count();
	}
	cout << endl;

	//temporary variables for adding
	t1 = 0;
	t2 = 0;
	t3 = 0;
	t4 = 0;
	t5 = 0;
	//for-loop to loop through temp sort-time arrays
	for (int i = 0; i < 100; i++)
	{
		//add each element of array to temp variables
		t1 += insertionSortTimes[i];
		t2 += selectionSortTimes[i];
		t3 += bubbleSortTimes[i];
		t4 += quickSortTimes[i];
		t5 += mergeSortTimes[i];
	}
	//for-loop to loop through permanent sort-time arrays
	for (int i = 100; i < 200; i++)
	{
		//permanently store the sort times
		allInsertionSortTimes[i] = insertionSortTimes[i % 100];
		allSelectionSortTimes[i] = selectionSortTimes[i % 100];
		allBubbleSortTimes[i] = bubbleSortTimes[i % 100];
		allQuickSortTimes[i] = quickSortTimes[i % 100];
		allMergeSortTimes[i] = mergeSortTimes[i % 100];
	}
	//calculate the average/mean of each sorting method for a shuffled array
	shuffledInsertionAvg = t1 / 100;
	shuffledSelectionAvg = t2 / 100;
	shuffledBubbleAvg = t3 / 100;
	shuffledQuickAvg = t4 / 100;
	shuffledMergeAvg = t5 / 100;


	//------------------------------Reversed Array------------------------------------
	//calculate sort times for the reversed array
	cout << endl << "Sorting the Reversed Array[" << SIZE << "] x 100" << endl;
	for (int i = 0; i < 100; i++)
	{
		if (i % 2 == 0)
			cout << "#";
		//----------------------------Reversed Insertion Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(reversedArr, arrCopy, SIZE);
		//set a start time time_point
		high_resolution_clock::time_point startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::insertionSort(arrCopy, SIZE);
		//set an end time time_point
		high_resolution_clock::time_point endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration<double, std::micro> duration = endTime - startTime;
		//store elapsed time into array
		insertionSortTimes[i] = duration.count();

		//----------------------------Reversed Selection Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(reversedArr, arrCopy, SIZE);
		//set a start time time_point
		startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::selectionSort(arrCopy, SIZE);
		//set an end time time_point
		endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration = endTime - startTime;
		//store elapsed time into array
		selectionSortTimes[i] = duration.count();

		//----------------------------Reversed Bubble Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(reversedArr, arrCopy, SIZE);
		//set a start time time_point
		startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::bubbleSort(arrCopy, SIZE);
		//set an end time time_point
		endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration = endTime - startTime;
		//store elapsed time into array
		bubbleSortTimes[i] = duration.count();

		//----------------------------Reversed Quick Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(reversedArr, arrCopy, SIZE);
		//set a start time time_point
		startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::quickSort(arrCopy, 0, SIZE - 1);
		//set an end time time_point
		endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration = endTime - startTime;
		//store elapsed time into array
		quickSortTimes[i] = duration.count();

		//----------------------------Reversed Merge Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(reversedArr, arrCopy, SIZE);
		//set a start time time_point
		startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::mergeSort(arrCopy, 0, SIZE - 1);
		//set an end time time_point
		endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration = endTime - startTime;
		//store elapsed time into array
		mergeSortTimes[i] = duration.count();
	}
	cout << endl;
	//temporary variables for adding
	t1 = 0;
	t2 = 0;
	t3 = 0;
	t4 = 0;
	t5 = 0;
	//for-loop to loop through the temp sort-time arrays
	for (int i = 0; i < 100; i++)
	{
		//add each element of array to temp variables
		t1 += insertionSortTimes[i];
		t2 += selectionSortTimes[i];
		t3 += bubbleSortTimes[i];
		t4 += quickSortTimes[i];
		t5 += mergeSortTimes[i];
	}
	//for-loop to loop through permanent sort-time arrays
	for (int i = 200; i < 300; i++)
	{
		//permanently store the sort times
		allInsertionSortTimes[i] = insertionSortTimes[i % 200];
		allSelectionSortTimes[i] = selectionSortTimes[i % 200];
		allBubbleSortTimes[i] = bubbleSortTimes[i % 200];
		allQuickSortTimes[i] = quickSortTimes[i % 200];
		allMergeSortTimes[i] = mergeSortTimes[i % 200];
	}
	//calculate the average/mean of each sorting method for a reversed array
	reversedInsertionAvg = t1 / 100;
	reversedSelectionAvg = t2 / 100;
	reversedBubbleAvg = t3 / 100;
	reversedQuickAvg = t4 / 100;
	reversedMergeAvg = t5 / 100;


	//---------------------------------10% shuffled Array--------------------------
	//calculate sort times for the 10% shuffled array
	cout << endl << "Sorting the 10% Shuffled Array[" << SIZE << "] x 100" << endl;
	for (int i = 0; i < 100; i++)
	{
		if (i % 2 == 0)
			cout << "#";
		//----------------------------10% shuffled Insertion Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(tenPercentArr, arrCopy, SIZE);
		//set a start time time_point
		high_resolution_clock::time_point startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::insertionSort(arrCopy, SIZE);
		//set an end time time_point
		high_resolution_clock::time_point endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration<double, std::micro> duration = endTime - startTime;
		//store elapsed time into array
		insertionSortTimes[i] = duration.count();

		//----------------------------10% shuffled Selection Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(tenPercentArr, arrCopy, SIZE);
		//set a start time time_point
		startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::selectionSort(arrCopy, SIZE);
		//set an end time time_point
		endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration = endTime - startTime;
		//store elapsed time into array
		selectionSortTimes[i] = duration.count();

		//----------------------------10% shuffled Bubble Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(tenPercentArr, arrCopy, SIZE);
		//set a start time time_point
		startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::bubbleSort(arrCopy, SIZE);
		//set an end time time_point
		endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration = endTime - startTime;
		//store elapsed time into array
		bubbleSortTimes[i] = duration.count();

		//----------------------------10% shuffled Quick Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(tenPercentArr, arrCopy, SIZE);
		//set a start time time_point
		startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::quickSort(arrCopy, 0, SIZE - 1);
		//set an end time time_point
		endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration = endTime - startTime;
		//store elapsed time into array
		quickSortTimes[i] = duration.count();

		//----------------------------10% shuffled Merge Sort----------------------------------
		//copy original array
		Array_Helpers::copyArr(tenPercentArr, arrCopy, SIZE);
		//set a start time time_point
		startTime = high_resolution_clock::now();
		//perform sorting algorithm
		Array_Helpers::mergeSort(arrCopy, 0, SIZE - 1);
		//set an end time time_point
		endTime = high_resolution_clock::now();
		//subtract start time from end time to calculate total elapsed time
		duration = endTime - startTime;
		//store elapsed time into array
		mergeSortTimes[i] = duration.count();
	}
	cout << endl;
	//temporary variables for adding
	t1 = 0;
	t2 = 0;
	t3 = 0;
	t4 = 0;
	t5 = 0;
	//for-loop to loop through the temp sort-time arrays
	for (int i = 0; i < 100; i++)
	{
		//add each element of array to temp variables
		t1 += insertionSortTimes[i];
		t2 += selectionSortTimes[i];
		t3 += bubbleSortTimes[i];
		t4 += quickSortTimes[i];
		t5 += mergeSortTimes[i];
	}
	//for-loop to loop through permanent sort-time arrays
	for (int i = 300; i < 400; i++)
	{
		//permanently store the sort times
		allInsertionSortTimes[i] = insertionSortTimes[i % 300];
		allSelectionSortTimes[i] = selectionSortTimes[i % 300];
		allBubbleSortTimes[i] = bubbleSortTimes[i % 300];
		allQuickSortTimes[i] = quickSortTimes[i % 300];
		allMergeSortTimes[i] = mergeSortTimes[i % 300];
	}
	//calculate the average/mean of each sorting method for a 10% shuffled array
	tenPercentInsertionAvg = t1 / 100;
	tenPercentSelectionAvg = t2 / 100;
	tenPercentBubbleAvg = t3 / 100;
	tenPercentQuickAvg = t4 / 100;
	tenPercentMergeAvg = t5 / 100;

	cout << "---------------------------------------------------------------" << endl;


	//----------------------------Calculations----------------------------------
	//Calculate the overall average sort times
	//temporary variables for adding
	t1 = 0;
	t2 = 0;
	t3 = 0;
	t4 = 0;
	t5 = 0;
	//for-loop to loop through the all sort-time arrays
	for (int i = 0; i < 400; i++)
	{
		//add each element of array to temp variables
		t1 += allInsertionSortTimes[i];
		t2 += allSelectionSortTimes[i];
		t3 += allBubbleSortTimes[i];
		t4 += allQuickSortTimes[i];
		t5 += allMergeSortTimes[i];
	}
	//calculate the OVERALL average/mean of each sorting method
	insertionSortAvg = t1 / 400;
	selectionSortAvg = t2 / 400;
	bubbleSortAvg = t3 / 400;
	quickSortAvg = t4 / 400;
	mergeSortAvg = t5 / 400;

	//Calculate the standard deviations of the sorting algorithms
	//create temporary arrays that will store the sort times, to perform the STD formula on
	double *tempInsertionTimes = new double[400];
	double *tempSelectionTimes = new double[400];
	double *tempBubbleTimes = new double[400];
	double *tempQuickTimes = new double[400];
	double *tempMergeTimes = new double[400];

	//copy all sort times into temporary arrys
	for (int i = 0; i < 400; i++)
	{
		tempInsertionTimes[i] = allInsertionSortTimes[i];
		tempSelectionTimes[i] = allSelectionSortTimes[i];
		tempBubbleTimes[i] = allBubbleSortTimes[i];
		tempQuickTimes[i] = allQuickSortTimes[i];
		tempMergeTimes[i] = allMergeSortTimes[i];
	}
	//subtract the mean from each sort time
	for (int i = 0; i < 400; i++)
	{
		tempInsertionTimes[i] = tempInsertionTimes[i] - insertionSortAvg;
		tempSelectionTimes[i] = tempSelectionTimes[i] - selectionSortAvg;
		tempBubbleTimes[i] = tempBubbleTimes[i] - bubbleSortAvg;
		tempQuickTimes[i] = tempQuickTimes[i] - quickSortAvg;
		tempMergeTimes[i] = tempMergeTimes[i] - mergeSortAvg;
	}
	//square each element
	for (int i = 0; i < 400; i++)
	{
		tempInsertionTimes[i] = tempInsertionTimes[i] * tempInsertionTimes[i];
		tempSelectionTimes[i] = tempSelectionTimes[i] * tempSelectionTimes[i];
		tempBubbleTimes[i] = tempBubbleTimes[i] * tempBubbleTimes[i];
		tempQuickTimes[i] = tempQuickTimes[i] * tempQuickTimes[i];
		tempMergeTimes[i] = tempMergeTimes[i] * tempMergeTimes[i];
	}
	//find the mean of the squared elements
	//temp variables for adding
	t1 = 0;
	t2 = 0;
	t3 = 0;
	t4 = 0;
	t5 = 0;
	//for-loop to loop through the all temp sort-time arrays
	for (int i = 0; i < 400; i++)
	{
		//add each element of array to temp variables
		t1 += tempInsertionTimes[i];
		t2 += tempSelectionTimes[i];
		t3 += tempBubbleTimes[i];
		t4 += tempQuickTimes[i];
		t5 += tempMergeTimes[i];
	}
	//calculate the standard deviation of each sort algorithm
	//by finding the square root of the mean of each sort algorithm
	insertionSortSTD = sqrt((t1 / 400));
	selectionSortSTD = sqrt((t2 / 400));
	bubbleSortSTD = sqrt((t3 / 400));
	quickSortSTD = sqrt((t4 / 400));
	mergeSortSTD = sqrt((t5 / 400));

	//delete temporary sort time arrays
	delete[] tempInsertionTimes;
	delete[] tempSelectionTimes;
	delete[] tempBubbleTimes;
	delete[] tempQuickTimes;
	delete[] tempMergeTimes;
	//set array pointers to NULL
	tempInsertionTimes = NULL;
	tempSelectionTimes = NULL;
	tempBubbleTimes = NULL;
	tempQuickTimes = NULL;
	tempMergeTimes = NULL;

}

//Function to display the average time of each sort algorithm ACROSS EACH array.
//Will also display the average of each sort algorithm ACROSS ALL arrays,
//and the standard deviation of each sort algorithm ACROSS ALL arrays.
template <class T>
void ARRAY_CLASS<T>::dispResults()
{
	//Display average time of all sort algorithms on the SORTED array
	cout << "Sorted Array[" << SIZE << "]" << endl;
	cout << "----------------";
	cout << endl << "Sorted Insertion Sort Avg: " << sortedInsertionAvg << " Microseconds" << endl;
	cout << "Sorted Selection Sort Avg: " << sortedSelectionAvg << " Microseconds" << endl;
	cout << "Sorted Bubble Sort Avg: " << sortedBubbleAvg << " Microseconds" << endl;
	cout << "Sorted Quick Sort Avg: " << sortedQuickAvg << " Microseconds" << endl;
	cout << "Sorted Merge Sort Avg: " << sortedMergeAvg << " Microseconds" << endl << endl;

	//Display average time of all sort algorithms on the SHUFFLED array
	cout << "Shuffled Array[" << SIZE << "]" << endl;
	cout << "------------------";
	cout << endl << "Shuffled Insertion Sort Avg: " << shuffledInsertionAvg << " Microseconds" << endl;
	cout << "Shuffled Selection Sort Avg: " << shuffledSelectionAvg << " Microseconds" << endl;
	cout << "Shuffled Bubble Sort Avg: " << shuffledBubbleAvg << " Microseconds" << endl;
	cout << "Shuffled Quick Sort Avg: " << shuffledQuickAvg << " Microseconds" << endl;
	cout << "Shuffled Merge Sort Avg: " << shuffledMergeAvg << " Microseconds" << endl << endl;

	//Display average time of all sort algorithms on the REVERSED array
	cout << "Reversed Array[" << SIZE << "]" << endl;
	cout << "-------------------";
	cout << endl << "Reversed Insertion Sort Avg: " << reversedInsertionAvg << " Microseconds" << endl;
	cout << "Reversed Selection Sort Avg: " << reversedSelectionAvg << " Microseconds" << endl;
	cout << "Reversed Bubble Sort Avg: " << reversedBubbleAvg << " Microseconds" << endl;
	cout << "Reversed Quick Sort Avg: " << reversedQuickAvg << " Microseconds" << endl;
	cout << "Reversed Merge Sort Avg: " << reversedMergeAvg << " Microseconds" << endl << endl;

	//Display average time of all sort algorithms on the 10% SHUFFLED array
	cout << "10% Shuffled Array[" << SIZE << "]" << endl;
	cout << "------------------------------";
	cout << endl << "10% Insertion Sort Avg: " << tenPercentInsertionAvg << " Microseconds" << endl;
	cout << "10% Selection Sort Avg: " << tenPercentSelectionAvg << " Microseconds" << endl;
	cout << "10% Bubble Sort Avg: " << tenPercentBubbleAvg << " Microseconds" << endl;
	cout << "10% Quick Sort Avg: " << tenPercentQuickAvg << " Microseconds" << endl;
	cout << "10% Merge Sort Avg: " << tenPercentMergeAvg << " Microseconds" << endl << endl;

	//Display averages of each sort algorithm ACROSS ALL arrays
	cout << "Overall Averages across all arrays[" << SIZE << "]" << endl;
	cout << "-------------------------------------" << endl;
	cout << "Overall Insertion Sort Avg: " << insertionSortAvg << " Microseconds" << endl;
	cout << "Overall Selection Sort Avg: " << selectionSortAvg << " Microseconds" << endl;
	cout << "Overall Bubble Sort Avg: " << bubbleSortAvg << " Microseconds" << endl;
	cout << "Overall Quick Sort Avg: " << quickSortAvg << " Microseconds" << endl;
	cout << "Overall Merge Sort Avg: " << mergeSortAvg << " Microseconds" << endl << endl;

	//Display standard deviation of each sort algorithm ACROSS ALL arrays
	cout << "Standard Deviation of each sorting algorithm across all arrays[" << SIZE << "]" << endl;
	cout << "-------------------------------------" << endl;
	cout << "Insertion Sort STD: " << insertionSortSTD << " Microseconds" << endl;
	cout << "Selection Sort STD: " << selectionSortSTD << " Microseconds" << endl;
	cout << "Bubble Sort STD: " << bubbleSortSTD << " Microseconds" << endl;
	cout << "Quick Sort STD: " << quickSortSTD << " Microseconds" << endl;
	cout << "Merge Sort STD: " << mergeSortSTD << " Microseconds" << endl << endl;

	cout << "---------------------------------------------------------------" << endl;
}
//Function that does the exact same thing as dispResults(), but instead writes the output
//to an external file named "results.txt"
template <class T>
void ARRAY_CLASS<T>::writeResults()
{
	cout << "Writing results to 'results.txt'" << endl;
	cout << "---------------------------------------------------------------" << endl << endl;
	//Create file instance
	ofstream resultFile;
	//Create/Open "results.txt". 'ios:app' is to continue writing at end of the file, when opened.
	resultFile.open("results.txt", ios::app);

	resultFile << "Sorted Array[" << SIZE << "]" << endl;
	resultFile << "----------------------------";
	resultFile << endl << "Sorted Insertion Sort Avg: " << sortedInsertionAvg << " Microseconds" << endl;
	resultFile << "Sorted Selection Sort Avg: " << sortedSelectionAvg << " Microseconds" << endl;
	resultFile << "Sorted Bubble Sort Avg: " << sortedBubbleAvg << " Microseconds" << endl;
	resultFile << "Sorted Quick Sort Avg: " << sortedQuickAvg << " Microseconds" << endl;
	resultFile << "Sorted Merge Sort Avg: " << sortedMergeAvg << " Microseconds" << endl << endl;

	resultFile << "Shuffled Array[" << SIZE << "]" << endl;
	resultFile << "------------------------------";
	resultFile << endl << "Shuffled Insertion Sort Avg: " << shuffledInsertionAvg << " Microseconds" << endl;
	resultFile << "Shuffled Selection Sort Avg: " << shuffledSelectionAvg << " Microseconds" << endl;
	resultFile << "Shuffled Bubble Sort Avg: " << shuffledBubbleAvg << " Microseconds" << endl;
	resultFile << "Shuffled Quick Sort Avg: " << shuffledQuickAvg << " Microseconds" << endl;
	resultFile << "Shuffled Merge Sort Avg: " << shuffledMergeAvg << " Microseconds" << endl << endl;

	resultFile << "Reversed Array[" << SIZE << "]" << endl;
	resultFile << "------------------------------";
	resultFile << endl << "Reversed Insertion Sort Avg: " << reversedInsertionAvg << " Microseconds" << endl;
	resultFile << "Reversed Selection Sort Avg: " << reversedSelectionAvg << " Microseconds" << endl;
	resultFile << "Reversed Bubble Sort Avg: " << reversedBubbleAvg << " Microseconds" << endl;
	resultFile << "Reversed Quick Sort Avg: " << reversedQuickAvg << " Microseconds" << endl;
	resultFile << "Reversed Merge Sort Avg: " << reversedMergeAvg << " Microseconds" << endl << endl;

	resultFile << "10% Shuffled Array[" << SIZE << "]" << endl;
	resultFile << "----------------------------------";
	resultFile << endl << "10% Insertion Sort Avg: " << tenPercentInsertionAvg << " Microseconds" << endl;
	resultFile << "10% Selection Sort Avg: " << tenPercentSelectionAvg << " Microseconds" << endl;
	resultFile << "10% Bubble Sort Avg: " << tenPercentBubbleAvg << " Microseconds" << endl;
	resultFile << "10% Quick Sort Avg: " << tenPercentQuickAvg << " Microseconds" << endl;
	resultFile << "10% Merge Sort Avg: " << tenPercentMergeAvg << " Microseconds" << endl << endl;

	resultFile << "Overall Averages across all arrays[" << SIZE << "]" << endl;
	resultFile << "--------------------------------------------------" << endl;
	resultFile << "Overall Insertion Sort Avg: " << insertionSortAvg << " Microseconds" << endl;
	resultFile << "Overall Selection Sort Avg: " << selectionSortAvg << " Microseconds" << endl;
	resultFile << "Overall Bubble Sort Avg: " << bubbleSortAvg << " Microseconds" << endl;
	resultFile << "Overall Quick Sort Avg: " << quickSortAvg << " Microseconds" << endl;
	resultFile << "Overall Merge Sort Avg: " << mergeSortAvg << " Microseconds" << endl << endl;

	resultFile << "Standard Deviation across all arrays[" << SIZE << "]" << endl;
	resultFile << "---------------------------------------------------" << endl;
	resultFile << "Insertion Sort STD: " << insertionSortSTD << " Microseconds" << endl;
	resultFile << "Selection Sort STD: " << selectionSortSTD << " Microseconds" << endl;
	resultFile << "Bubble Sort STD: " << bubbleSortSTD << " Microseconds" << endl;
	resultFile << "Quick Sort STD: " << quickSortSTD << " Microseconds" << endl;
	resultFile << "Merge Sort STD: " << mergeSortSTD << " Microseconds" << endl << endl;

	resultFile << "--------------------------------------------------------------------------------------" << endl;

	resultFile.close();
}
//Function to display ALL sort times for each algorithm across EACH ARRAY.
template <class T>
void ARRAY_CLASS<T>::dispTimesByArrayType()
{

	//Display sort times of insertion sort on the sorted array
	cout << "Sorted Array[" << SIZE << "] - Insertion Sort Times" << endl;
	for (int i = 0; i < 100; i++)
	{
		cout << setw(8) << allInsertionSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << endl;
	//Display sort times of selection sort on the sorted array
	cout << "Sorted Array[" << SIZE << "] - Selection Sort Times" << endl;
	for (int i = 0; i < 100; i++)
	{
		cout << setw(8) << allSelectionSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << endl;
	//Display sort times of bubble sort on the sorted array
	cout << "Sorted Array[" << SIZE << "] - Bubble Sort Times" << endl;
	for (int i = 0; i < 100; i++)
	{
		cout << setw(8) << allBubbleSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << endl;
	//Display sort times of quick sort on the sorted array
	cout << "Sorted Array[" << SIZE << "] - Quick Sort Times" << endl;
	for (int i = 0; i < 100; i++)
	{
		cout << setw(8) << allQuickSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << endl;
	//Display sort times of merge sort on the sorted array
	cout << "Sorted Array[" << SIZE << "] - Merge Sort Times" << endl;
	for (int i = 0; i < 100; i++)
	{
		cout << setw(8) << allMergeSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << "------------------------------------------------------------------" << endl;
	//Display sort times of insertion sort on the Shuffled array
	cout << "Shuffled Array[" << SIZE << "] - Insertion Sort Times" << endl;
	for (int i = 100; i < 200; i++)
	{
		cout << setw(8) << allInsertionSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << endl;
	//Display sort times of selection sort on the Shuffled array
	cout << "Shuffled Array[" << SIZE << "] - Selection Sort Times" << endl;
	for (int i = 100; i < 200; i++)
	{
		cout << setw(8) << allSelectionSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << endl;
	//Display sort times of bubble sort on the Shuffled array
	cout << "Shuffled Array[" << SIZE << "] - Bubble Sort Times" << endl;
	for (int i = 100; i < 200; i++)
	{
		cout << setw(8) << allBubbleSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << endl;
	//Display sort times of quick sort on the Shuffled array
	cout << "Shuffled Array[" << SIZE << "] - Quick Sort Times" << endl;
	for (int i = 100; i < 200; i++)
	{
		cout << setw(8) << allQuickSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << endl;
	//Display sort times of merge sort on the Shuffled array
	cout << "Shuffled Array[" << SIZE << "] - Merge Sort Times" << endl;
	for (int i = 100; i < 200; i++)
	{
		cout << setw(8) << allMergeSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << "------------------------------------------------------------------" << endl;
	//Display sort times of insertion sort on the Reversed array
	cout << "Reversed Array[" << SIZE << "] - Insertion Sort Times" << endl;
	for (int i = 200; i < 300; i++)
	{
		cout << setw(8) << allInsertionSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << endl;
	//Display sort times of selection sort on the Reversed array
	cout << "Reversed Array[" << SIZE << "] - Selection Sort Times" << endl;
	for (int i = 200; i < 300; i++)
	{
		cout << setw(8) << allSelectionSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << endl;
	//Display sort times of bubble sort on the Reversed array
	cout << "Reversed Array[" << SIZE << "] - Bubble Sort Times" << endl;
	for (int i = 200; i < 300; i++)
	{
		cout << setw(8) << allBubbleSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << endl;
	//Display sort times of quick sort on the Reversed array
	cout << "Reversed Array[" << SIZE << "] - Quick Sort Times" << endl;
	for (int i = 200; i < 300; i++)
	{
		cout << setw(8) << allQuickSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << endl;
	//Display sort times of merge sort on the Reversed array
	cout << "Reversed Array[" << SIZE << "] - Merge Sort Times" << endl;
	for (int i = 200; i < 300; i++)
	{
		cout << setw(8) << allMergeSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << "------------------------------------------------------------------" << endl;
	//Display sort times of insertion sort on the 10% Shuffled array
	cout << "10% Shuffled Array[" << SIZE << "] - Insertion Sort Times" << endl;
	for (int i = 300; i < 400; i++)
	{
		cout << setw(8) << allInsertionSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << endl;
	//Display sort times of selection sort on the 10% Shuffled array
	cout << "10% Shuffled Array[" << SIZE << "] - Selection Sort Times" << endl;
	for (int i = 300; i < 400; i++)
	{
		cout << setw(8) << allSelectionSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << endl;
	//Display sort times of bubble sort on the 10% Shuffled array
	cout << "10% Shuffled Array[" << SIZE << "] - Bubble Sort Times" << endl;
	for (int i = 300; i < 400; i++)
	{
		cout << setw(8) << allBubbleSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << endl;
	//Display sort times of quick sort on the 10% Shuffled array
	cout << "10% Shuffled Array[" << SIZE << "] - Quick Sort Times" << endl;
	for (int i = 300; i < 400; i++)
	{
		cout << setw(8) << allQuickSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
	cout << endl;
	//Display sort times of merge sort on the 10% Shuffled array
	cout << "10% Shuffled Array[" << SIZE << "] - Merge Sort Times" << endl;
	for (int i = 300; i < 400; i++)
	{
		cout << setw(8) << allMergeSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
}
//Function to display ALL sort times for each sort algorithm across ALL ARRAYS
//index: 0-99 = sorted array sort times, 100-199 = shuffled array sort times,
//200-299 = reversed array sort times, 300-399 = 10% shuffled array sort times.
template <class T>
void ARRAY_CLASS<T>::dispTimesBySortAlgorithm()
{
	//Display ALL insertion sort times
	cout << "All Insertion Sort Times across ALL ARRAYS[" << SIZE << "]" << endl;
	for (int i = 0; i < 400; i++)
	{
		cout << setw(8) << allInsertionSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
		if (i == 399)
			cout << "-----------------------------------------------------------------" << endl;
	}
	//Display ALL selection sort times
	cout << "All Selection Sort Times across ALL ARRAYS[" << SIZE << "]" << endl;
	for (int i = 0; i < 400; i++)
	{
		cout << setw(8) << allSelectionSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
		if (i == 399)
			cout << "-----------------------------------------------------------------" << endl;
	}
	//Display ALL bubble sort times
	cout << "All Bubble Sort Times across ALL ARRAYS[" << SIZE << "]" << endl;
	for (int i = 0; i < 400; i++)
	{
		cout << setw(8) << allBubbleSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
		if (i == 399)
			cout << "-----------------------------------------------------------------" << endl;
	}
	//Display ALL quick sort times
	cout << "All Quick Sort Times across ALL ARRAYS[" << SIZE << "]" << endl;
	for (int i = 0; i < 400; i++)
	{
		cout << setw(8) << allQuickSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
		if (i == 399)
			cout << "-----------------------------------------------------------------" << endl;
	}
	//Display ALL merge sort times
	cout << "All Merge Sort Times across ALL ARRAYS[" << SIZE << "]" << endl;
	for (int i = 0; i < 400; i++)
	{
		cout << setw(8) << allMergeSortTimes[i] << ",";
		if ((i + 1) % 10 == 0)
			cout << endl;
		if (i == 399)
			cout << "-----------------------------------------------------------------" << endl;
	}

}












