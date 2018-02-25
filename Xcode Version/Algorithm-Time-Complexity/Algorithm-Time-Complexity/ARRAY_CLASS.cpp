//
//  ARRAY_CLASS.cpp
//  Algorithm-Time-Complexity
//
//  Created by Bryce Remick on 2/25/18.
//  Copyright © 2018 Bryce Remick. All rights reserved.
//
#include "ARRAY_CLASS.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <ratio>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace chrono;


namespace Array_Helpers {
    
    template <class T>
    void dispArr2(T[], int);
    
    template <class T>
    void copyArr(T[], T[], int);
    
    template <class T>
    void insertionSort(T[], int);
    
    template <class T>
    void selectionSort(T[], int);
    
    template <class T>
    void bubbleSort(T[], int);
    
    template <class T>
    void quickSort(T[], int, int);
    
    template <class T>
    void mergeSort(T[], int, int);
    
    template <class T>
    void merge(T[], int, int, int);
    //--------------------------------------------------------------
    template <class T>
    void dispArr2(T arr[], int SIZE)
    {
        for (int i = 0; i < SIZE; i++){
            cout << setw(5) << arr[i] << " ";
            if ((i+1) % 10 ==0)
                cout << endl;
        }
    }
    template <class T>
    void copyArr(T arr[], T arrCopy[], int SIZE)
    {
        for(int i = 0; i < SIZE; i++)
            arrCopy[i] = arr[i];
    }
    template <class T>
    void insertionSort(T arr[], int SIZE)
    {
        int i, j;
        T key;
        for (i = 1; i < SIZE; i++)
        {
            key = arr[i];
            j = i-1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j+1] = arr[j];
                j = j-1;
            }
            arr[j+1] = key;
        }
    }
    template <class T>
    void selectionSort(T arr[], int SIZE)
    {
        int pos_min;
        T temp;
        for (int i=0; i < SIZE-1; i++)
        {
            pos_min = i;
            for (int j=i+1; j < SIZE; j++)
            {
                if (arr[j] < arr[pos_min])
                    pos_min=j;
            }
            if (pos_min != i)
            {
                temp = arr[i];
                arr[i] = arr[pos_min];
                arr[pos_min] = temp;
            }
        }
    }
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
    template <class T>
    void quickSort(T arr[], int left, int right)
    {
        int i = left, j = right;
        T tmp;
        T pivot = arr[(left + right) / 2];
        
        /* partition */
        while (i <= j) {
            
            while (arr[i] < pivot)
                i++;
            
            while (arr[j] > pivot)
                j--;
            
            if (i <= j) {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                i++;
                j--;
            }
        };
        
        /* recursion */
        if (left < j)
            quickSort(arr, left, j);
        
        if (i < right)
            quickSort(arr, i, right);
    }
    template <class T>
    void mergeSort(T arr[], int l, int r)
    {
        if (l < r)
        {
            // Same as (l+r)/2, but avoids overflow for
            // large l and h
            int m = l+(r-l)/2;
            
            // Sort first and second halves
            mergeSort(arr, l, m);
            mergeSort(arr, m+1, r);
            
            merge(arr, l, m, r);
        }
    }
    template <class T>
    void merge(T arr[], int l, int m, int r)
    {
        int i, j, k;
        int n1 = m - l + 1;
        int n2 =  r - m;
        
        /* create temp arrays */
        T L[n1], R[n2];
        
        /* Copy data to temp arrays L[] and R[] */
        for (i = 0; i < n1; i++)
            L[i] = arr[l + i];
        for (j = 0; j < n2; j++)
            R[j] = arr[m + 1+ j];
        
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
    }
}


template <class T>
ARRAY_CLASS<T>::ARRAY_CLASS(){}

template <class T>
ARRAY_CLASS<T>::ARRAY_CLASS(int x)
{
    SIZE = x;
    int j = 0;
    
    srand(time(NULL));
    
    insertionSortTimes = new double[100];
    selectionSortTimes = new double[100];
    bubbleSortTimes = new double[100];
    quickSortTimes = new double[100];
    mergeSortTimes = new double[100];
    
    sortedArr = new T[SIZE];
    shuffledArr = new T[SIZE];
    reversedArr = new T[SIZE];
    tenPercentArr = new T[SIZE];
    arrCopy = new T[SIZE];
    
    cout << "Building Arrays["<< SIZE <<"]..." << endl;
    
    //sorted array
    for (int i = 0; i < SIZE; i++)
        sortedArr[i] = i;
    
    //shuffled array
    for (int i = 0; i < SIZE; i++)
        shuffledArr[i] = (rand() % SIZE) + 1;
    
    //reversed array
    for (int i = (SIZE - 1); i >= 0; i--)
    {
        reversedArr[j] = i;
        j++;
    }
    
    //ten percent shuffled/sorted array
    for (int i = 0; i < SIZE; i++)
    {
        if (i <= (SIZE * .10))
            tenPercentArr[i] = i;
        else
            tenPercentArr[i] = (rand() % SIZE) + 1;
    }
    
    
}
template <class T>
ARRAY_CLASS<T>::~ARRAY_CLASS()
{
    delete [] sortedArr;
    delete [] shuffledArr;
    delete [] reversedArr;
    delete [] tenPercentArr;
    delete [] arrCopy;
    
    delete [] insertionSortTimes;
    delete [] selectionSortTimes;
    delete [] bubbleSortTimes;
    delete [] quickSortTimes;
    delete [] mergeSortTimes;
    cout << "Memory Freed..." << endl;
}
template <class T>
void ARRAY_CLASS<T>::dispArr()
{
    cout << endl << "Sorted Array" << "[" << SIZE << "]:"<< endl;
    Array_Helpers::dispArr2(sortedArr, SIZE);
    cout << endl << "Shuffled Array" << "[" << SIZE << "]:" << endl;
    Array_Helpers::dispArr2(arrCopy, SIZE);
    cout << endl << "Reversed Array" << "[" << SIZE << "]:" << endl;
    Array_Helpers::dispArr2(reversedArr, SIZE);
    cout << endl << "Ten Percent Sorted/Shuffled Array" << "[" << SIZE << "]:" << endl;
    Array_Helpers::dispArr2(tenPercentArr, SIZE);
}
template <class T>
void ARRAY_CLASS<T>::performTests()
{
    //--------------------------------------Sorted Array----------------------------------------------
    //calculate sort times for the sorted array
    cout << "Sorting the Sorted Array[" << SIZE << "] x 100" << endl;
    for(int i = 0; i < 100; i++)
    {
        if (i % 2 == 0)
            cout << "#";
        //----------------------------Sorted Insertion Sort----------------------------------
        //copy original array
        Array_Helpers::copyArr(sortedArr, arrCopy, SIZE);
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
    //for-loop to loop through the sort-time arrays
    for(int i = 0; i < 100; i++)
    {
        //add each element of array to temp variables
        t1 += insertionSortTimes[i];
        t2 += selectionSortTimes[i];
        t3 += bubbleSortTimes[i];
        t4 += quickSortTimes[i];
        t5 += mergeSortTimes[i];
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
    //for-loop to loop through the sort-time arrays
    for(int i = 0; i < 100; i++)
    {
        //add each element of array to temp variables
        t1 += insertionSortTimes[i];
        t2 += selectionSortTimes[i];
        t3 += bubbleSortTimes[i];
        t4 += quickSortTimes[i];
        t5 += mergeSortTimes[i];
    }
    //calculate the average/mean of each sorting method for a sorted array
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
    //for-loop to loop through the sort-time arrays
    for(int i = 0; i < 100; i++)
    {
        //add each element of array to temp variables
        t1 += insertionSortTimes[i];
        t2 += selectionSortTimes[i];
        t3 += bubbleSortTimes[i];
        t4 += quickSortTimes[i];
        t5 += mergeSortTimes[i];
    }
    //calculate the average/mean of each sorting method for a sorted array
    reversedInsertionAvg = t1 / 100;
    reversedSelectionAvg = t2 / 100;
    reversedBubbleAvg = t3 / 100;
    reversedQuickAvg = t4 / 100;
    reversedMergeAvg = t5 / 100;
    
    
    //---------------------------------Ten Percent Sorted/90% Shuffled Array--------------------------
    //calculate sort times for the ten percent array
    cout << endl << "Sorting the 10% Sorted/Shuffled Array[" << SIZE << "] x 100" << endl;
    for (int i = 0; i < 100; i++)
    {
        if (i % 2 == 0)
            cout << "#";
        //----------------------------Ten Percent Insertion Sort----------------------------------
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
        
        //----------------------------Ten Percent Selection Sort----------------------------------
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
        
        //----------------------------Ten Percent Bubble Sort----------------------------------
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
        
        //----------------------------Ten Percent Quick Sort----------------------------------
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
        
        //----------------------------Ten Percent Merge Sort----------------------------------
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
    //for-loop to loop through the sort-time arrays
    for(int i = 0; i < 100; i++)
    {
        //add each element of array to temp variables
        t1 += insertionSortTimes[i];
        t2 += selectionSortTimes[i];
        t3 += bubbleSortTimes[i];
        t4 += quickSortTimes[i];
        t5 += mergeSortTimes[i];
    }
    //calculate the average/mean of each sorting method for a sorted array
    tenPercentInsertionAvg = t1 / 100;
    tenPercentSelectionAvg = t2 / 100;
    tenPercentBubbleAvg = t3 / 100;
    tenPercentQuickAvg = t4 / 100;
    tenPercentMergeAvg = t5 / 100;
    
    cout << "---------------------------------------------------------------" << endl;
    cout << endl;
    
}
template <class T>
void ARRAY_CLASS<T>::dispResults()
{
    cout << "Sorted Array[" << SIZE << "]" << endl;
    cout << "----------------";
    cout << endl << "Sorted Insertion Sort Avg: " << sortedInsertionAvg << " Microseconds" << endl;
    cout << "Sorted Selection Sort Avg: " << sortedSelectionAvg  << " Microseconds" << endl;
    cout << "Sorted Bubble Sort Avg: " << sortedBubbleAvg  << " Microseconds" << endl;
    cout << "Sorted Quick Sort Avg: " << sortedQuickAvg  << " Microseconds" << endl;
    cout << "Sorted Merge Sort Avg: " << sortedMergeAvg  << " Microseconds" << endl << endl;
    
    cout << "Shuffled Array[" << SIZE << "]" << endl;
    cout << "------------------";
    cout << endl << "Shuffled Insertion Sort Avg: " << shuffledInsertionAvg  << " Microseconds" << endl;
    cout << "Shuffled Selection Sort Avg: " << shuffledSelectionAvg  << " Microseconds" << endl;
    cout << "Shuffled Bubble Sort Avg: " << shuffledBubbleAvg  << " Microseconds" << endl;
    cout << "Shuffled Quick Sort Avg: " << shuffledQuickAvg  << " Microseconds" << endl;
    cout << "Shuffled Merge Sort Avg: " << shuffledMergeAvg  << " Microseconds" << endl << endl;
    
    cout << "Reversed Array[" << SIZE << "]" << endl;
    cout << "-------------------";
    cout << endl << "Reversed Insertion Sort Avg: " << reversedInsertionAvg  << " Microseconds" << endl;
    cout << "Reversed Selection Sort Avg: " << reversedSelectionAvg  << " Microseconds" << endl;
    cout << "Reversed Bubble Sort Avg: " << reversedBubbleAvg  << " Microseconds" << endl;
    cout << "Reversed Quick Sort Avg: " << reversedQuickAvg  << " Microseconds" << endl;
    cout << "Reversed Merge Sort Avg: " << reversedMergeAvg  << " Microseconds" << endl << endl;
    
    cout << "10% Sorted/Shuffled Array[" << SIZE << "]" << endl;
    cout << "------------------------------";
    cout << endl << "10% Insertion Sort Avg: " << tenPercentInsertionAvg  << " Microseconds" << endl;
    cout << "10% Selection Sort Avg: " << tenPercentSelectionAvg  << " Microseconds" << endl;
    cout << "10% Bubble Sort Avg: " << tenPercentBubbleAvg  << " Microseconds" << endl;
    cout << "10% Quick Sort Avg: " << tenPercentQuickAvg  << " Microseconds" << endl;
    cout << "10% Merge Sort Avg: " << tenPercentMergeAvg  << " Microseconds" << endl << endl;
    
    cout << "---------------------------------------------------------------" << endl;
}
template <class T>
void ARRAY_CLASS<T>::writeResults()
{
    cout << "Writing results to 'results.txt'" << endl;
    ofstream resultFile;
    resultFile.open("results.txt", ios::app);
    
    resultFile << "Sorted Array[" << SIZE << "]" << endl;
    resultFile << "----------------";
    resultFile << endl << "Sorted Insertion Sort Avg: " << sortedInsertionAvg << " Microseconds" << endl;
    resultFile << "Sorted Selection Sort Avg: " << sortedSelectionAvg  << " Microseconds" << endl;
    resultFile << "Sorted Bubble Sort Avg: " << sortedBubbleAvg  << " Microseconds" << endl;
    resultFile << "Sorted Quick Sort Avg: " << sortedQuickAvg  << " Microseconds" << endl;
    resultFile << "Sorted Merge Sort Avg: " << sortedMergeAvg  << " Microseconds" << endl << endl;
    
    resultFile << "Shuffled Array[" << SIZE << "]" << endl;
    resultFile << "------------------";
    resultFile << endl << "Shuffled Insertion Sort Avg: " << shuffledInsertionAvg  << " Microseconds" << endl;
    resultFile << "Shuffled Selection Sort Avg: " << shuffledSelectionAvg  << " Microseconds" << endl;
    resultFile << "Shuffled Bubble Sort Avg: " << shuffledBubbleAvg  << " Microseconds" << endl;
    resultFile << "Shuffled Quick Sort Avg: " << shuffledQuickAvg  << " Microseconds" << endl;
    resultFile << "Shuffled Merge Sort Avg: " << shuffledMergeAvg  << " Microseconds" << endl << endl;
    
    resultFile << "Reversed Array[" << SIZE << "]" << endl;
    resultFile << "-------------------";
    resultFile << endl << "Reversed Insertion Sort Avg: " << reversedInsertionAvg  << " Microseconds" << endl;
    resultFile << "Reversed Selection Sort Avg: " << reversedSelectionAvg  << " Microseconds" << endl;
    resultFile << "Reversed Bubble Sort Avg: " << reversedBubbleAvg  << " Microseconds" << endl;
    resultFile << "Reversed Quick Sort Avg: " << reversedQuickAvg  << " Microseconds" << endl;
    resultFile << "Reversed Merge Sort Avg: " << reversedMergeAvg  << " Microseconds" << endl << endl;
    
    resultFile << "10% Sorted/Shuffled Array[" << SIZE << "]" << endl;
    resultFile << "------------------------------";
    resultFile << endl << "10% Insertion Sort Avg: " << tenPercentInsertionAvg  << " Microseconds" << endl;
    resultFile << "10% Selection Sort Avg: " << tenPercentSelectionAvg  << " Microseconds" << endl;
    resultFile << "10% Bubble Sort Avg: " << tenPercentBubbleAvg  << " Microseconds" << endl;
    resultFile << "10% Quick Sort Avg: " << tenPercentQuickAvg  << " Microseconds" << endl;
    resultFile << "10% Merge Sort Avg: " << tenPercentMergeAvg  << " Microseconds" << endl << endl;
    
    resultFile << "---------------------------------------------------------------" << endl;
    
    resultFile.close();
}











