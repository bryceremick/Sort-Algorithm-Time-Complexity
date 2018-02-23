//
//  ARRAY_CLASS.hpp
//  test
//
//  Created by Bryce Remick on 1/29/18.
//  Copyright © 2018 Bryce Remick. All rights reserved.
//

#ifndef ARRAY_CLASS_hpp
#define ARRAY_CLASS_hpp

#include <stdio.h>

template <class T>
class ARRAY_CLASS{
public:
    ARRAY_CLASS();
    ARRAY_CLASS(int);
    ~ARRAY_CLASS();
    
    //reuse these for each array type (sorted/shuffled...etc)
    double *insertionSortTimes;
    double *selectionSortTimes;
    double *bubbleSortTimes;
    double *quickSortTimes;
    double *mergeSortTimes;
    
    double sortedInsertionAvg;
    double sortedSelectionAvg;
    double sortedBubbleAvg;
    double sortedQuickAvg;
    double sortedMergeAvg;
    
    double shuffledInsertionAvg;
    double shuffledSelectionAvg;
    double shuffledBubbleAvg;
    double shuffledQuickAvg;
    double shuffledMergeAvg;
    
    double reversedInsertionAvg;
    double reversedSelectionAvg;
    double reversedBubbleAvg;
    double reversedQuickAvg;
    double reversedMergeAvg;
    
    double tenPercentInsertionAvg;
    double tenPercentSelectionAvg;
    double tenPercentBubbleAvg;
    double tenPercentQuickAvg;
    double tenPercentMergeAvg;

    void dispArr();
    void performTests();
    void dispResults();
    
private:
    
    int SIZE;
    T *sortedArr;
    T *shuffledArr;
    T *reversedArr;
    T *tenPercentArr;
    
    T *arrCopy;
    
protected:
};



#endif /* ARRAY_CLASS_hpp */
