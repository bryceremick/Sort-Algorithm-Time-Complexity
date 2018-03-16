//
//  main.cpp
//  Algorithm-Time-Complexity
//
//  Created by Bryce Remick on 2/25/18.
//  Copyright © 2018 Bryce Remick. All rights reserved.
//
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "ARRAY_CLASS.h"
#include "ARRAY_CLASS.cpp"
using namespace std;


int main() {

	/************************************QUICK START***************************************
	|1.    Delcare a ARRAY_CLASS Object(s). Must include an integer as a parameter,
	|       which will be the size of the arrays.
	|          EXAMPLE:
	|          ARRAY_CLASS<int> myArr(1000);
	|
	|2.    Run the function performTests() on your ARRAY_CLASS object(s).
	|          EXAMPLE:
	|          myArr.performTests();
	|
	|3.    Run dispResults(); on your ARRAY_CLASS object(s) to print results to the terminal.
	|          EXAMPLE:
	|          myArr.dispResults();
	**************************************************************************************/

	/***********************************OPTIONAL FUNCTIONS*********************************
	|1.     dispArrays(); This will display the pre-sorted arrays.
	|          EXAMPLE:
	|          myArr.dispArrays();
	|
	|2.    dispTimesByArrayType(); This will display ALL sort times across EACH array.
	|          EXAMPLE:
	|          myArr.dispTimesByArrayType();
	|
	|3.    dispTimesBySortAlgorithm(); This will display all sort times across ALL arrays.
	|          EXAMPLE:
	|          myArr.dispTimesBySortAlgorithm();
	|
	|4.    writeResults(); This will write results to external file named "results.txt".
	|                      Be sure to delete file after every compilation to avoid
	|                      mixing results.
	|          EXAMPLE:
	|          myArr.writeResults();
	**************************************************************************************/

	//******Use this block to test program*******
	ARRAY_CLASS<int> myArr(10);
	ARRAY_CLASS<int> myArr2(100);
	ARRAY_CLASS<int> myArr3(1000);
	//ARRAY_CLASS<int> myArr4(10000);

	myArr.performTests();
	myArr2.performTests();
	myArr3.performTests();
	//myArr4.performTests();

	myArr.dispResults();
	myArr2.dispResults();
	myArr3.dispResults();
	//myArr4.dispResults();

	//*****Use this block to run official project benchmarks*****
	//!!!This will take many hours, if not days!!!
	/*ARRAY_CLASS<int> myArr(10);
	ARRAY_CLASS<int> myArr2(1000);
	ARRAY_CLASS<int> myArr3(10000);
	ARRAY_CLASS<int> myArr4(100000);
	ARRAY_CLASS<int> myArr5(1000000);

	myArr.performTests();
	myArr.writeResults();

	myArr2.performTests();
	myArr2.writeResults();

	myArr3.performTests();
	myArr3.writeResults();

	myArr4.performTests();
	myArr4.writeResults();

	myArr5.performTests();
	myArr5.writeResults();*/



	cout << endl << endl;
	system("pause");
	return 0;
}


