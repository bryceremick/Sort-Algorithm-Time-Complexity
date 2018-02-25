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
#include "ARRAY_CLASS.hpp"
#include "ARRAY_CLASS.cpp"
using namespace std;


int main() {
    
    
    ARRAY_CLASS<int> myArr(1000);
    //ARRAY_CLASS<int> myArr2(10000);
    
    myArr.performTests();
    myArr.writeResults();
    
    //myArr2.performTests();
    //myArr2.writeResults();
    
    cout << endl << endl;
    return 0;
}


