#pragma once
#include <stdio.h>

template <class T>
class ARRAY_CLASS {
public:

	//Constructor that accepts an integer which determines size of arrays
	ARRAY_CLASS(int);
	//Destructor that deletes all dynamically created arrays
	~ARRAY_CLASS();

	//temporary arrays to store sort times of each sort algorithm on each type of array
	//size = 100 (for running the algorithm 100 times on each array)
	double *insertionSortTimes;
	double *selectionSortTimes;
	double *bubbleSortTimes;
	double *quickSortTimes;
	double *mergeSortTimes;

	//Arrays for ALL the sort times of each sorting algorithm
	//size = 400
	//(index)0-99: sorted array, 100-199: shuffled, 200-299:reversed, 300-399: 10% shuffled
	double *allInsertionSortTimes;
	double *allSelectionSortTimes;
	double *allBubbleSortTimes;
	double *allQuickSortTimes;
	double *allMergeSortTimes;

	//Average sort times of the sorted array
	double sortedInsertionAvg;
	double sortedSelectionAvg;
	double sortedBubbleAvg;
	double sortedQuickAvg;
	double sortedMergeAvg;

	//Average sort times of the shuffled array
	double shuffledInsertionAvg;
	double shuffledSelectionAvg;
	double shuffledBubbleAvg;
	double shuffledQuickAvg;
	double shuffledMergeAvg;

	//Average sort times of the reversed array
	double reversedInsertionAvg;
	double reversedSelectionAvg;
	double reversedBubbleAvg;
	double reversedQuickAvg;
	double reversedMergeAvg;

	//Average sort times of the 10% shuffled array
	double tenPercentInsertionAvg;
	double tenPercentSelectionAvg;
	double tenPercentBubbleAvg;
	double tenPercentQuickAvg;
	double tenPercentMergeAvg;

	//Overall average sort times across all arrays
	double insertionSortAvg;
	double selectionSortAvg;
	double bubbleSortAvg;
	double quickSortAvg;
	double mergeSortAvg;

	//Standard Deviations of all sort times for each algorithm
	double insertionSortSTD;
	double selectionSortSTD;
	double bubbleSortSTD;
	double quickSortSTD;
	double mergeSortSTD;

	//Function to display the pre-sorted arrays
	void dispArrays();

	//Function to perform sort algorithms and calculations
	void performTests();

	//Function to display average times of each sort algorithm on each array type.
	//Also displays the overall average and standard deviation of each sort algorithm.
	void dispResults();

	//Function to display all sort times based on array type
	void dispTimesByArrayType();

	//Function to display all sort times based on sort algorithm
	void dispTimesBySortAlgorithm();

	//Function to write results to external file
	void writeResults();



private:

	//Size of the arrays
	int SIZE;
	//Pointers to Arrays
	T *sortedArr;
	T *shuffledArr;
	T *reversedArr;
	T *tenPercentArr;
	//Pointer to temp array copy
	T *arrCopy;

};