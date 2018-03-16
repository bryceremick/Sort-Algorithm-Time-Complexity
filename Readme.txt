---------------------------------------------------------------------
Program Name
---------------------------------------------------------------------
Sort-Algorithm Time Complexity Benchmark


---------------------------------------------------------------------
Authors
---------------------------------------------------------------------
Bryce Remick
Adrian Lopez


---------------------------------------------------------------------
Files of Interest
---------------------------------------------------------------------
ARRAY_CLASS.h
	-Header file for ARRAY_CLASS

ARRAY_CLASS.cpp
	-Implementation file for ARRAY_CLASS

source.cpp
	-The source/main driver file

results.txt
	-A text file containing results of the benchmark, 
	if the user chooses to include it in the program.


---------------------------------------------------------------------
Program Features
--------------------------------------------------------------------- 
Template ARRAY_CLASS that must accept an integer(size) in its constructor
	Examples:
	ARRAY_CLASS<int> myArr(1000);
	ARRAY_CLASS<double> myArr(1000);

dispArrays() 
	A function to display pre-sorted arrays.

performTests()
	A function to measure the times of each sort algorithm on each array, and then perform
	 calculations to find the averages/means and standard deviations. Sorting algorithms
	used:
		-Insertion Sort
		-Selection Sort
		-Bubble Sort
		-Quick Sort
		-Merge Sort
	
dispResults()
	A function to display the average sort times of each algorithm for each array type.
	Also displays the overall average sort times and standard deviations of each sort
	algorithm across ALL arrays.

dispTimesByArrayType()
	A function to display ALL sort times for EACH array type.

dispTimesBySortAlgorithm()
	A function to display ALL sort times of EACH sort algorithm across all arrays.

writeResults()
	A function that mimics the dispResults() function, only instead of printing to the
	terminal, it writes the results to an external file named "results.txt".




---------------------------------------------------------------------
Program Abstract
---------------------------------------------------------------------
The program has only one class: ARRAY_CLASS. This class contains the four arrays to be sorted: 
sorted array, shuffled array, reversed array, and 10% shuffled array, and various class methods
to calculate the elapsed time of each sort algorithm on each array type. After the elapsed time
is determined, the program calculates the average/mean of each sort algorithm on each array type,
the overall average/mean of each sort algorithm across ALL array types, and the standard deviations
of each sort algorithm across ALL array types. A user can then implement a function to either
display the results to the terminal, or write the results to an external file, or both. There is
no interface or menu. All changes/options in the program can be done my implementing the desired
ARRAY_CLASS methods or accessing the public variables and arrays.

!Important!
When a user creates an ARRAY_CLASS object(s), they must pass an integer containing the desired
size of the arrays into the ARRAY_CLASS constructor. 