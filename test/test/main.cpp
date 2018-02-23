//
//  main.cpp
//  test
//
//  Created by Bryce Remick on 1/28/18.
//  Copyright © 2018 Bryce Remick. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "ARRAY_CLASS.hpp"
#include "ARRAY_CLASS.cpp"
using namespace std;


int main() {
    
    srand(time(NULL));
    
    ARRAY_CLASS<int> myArr(1000);
    myArr.performTests();
    
    
    cout << endl << endl;
    return 0;
}

