#ifndef __MEDIAN_CPPVECTOR_H_
#define __MEDIAN_CPPVECTOR_H_

#include <iostream>
#include <vector>

using namespace std;

// This version of MedianList abstracts a C++ vector and contains custom behaviour
// 1. always keep the list sorted during insertion (using binary search)
class MedianList
{
private:
    vector<unsigned long int> iVec;

#if ENABLE_DEBUG
    unsigned long int curMedianVal;
#endif

    int findPos(unsigned long int value);
    unsigned long int getMedian();

public:
    MedianList() { iVec.reserve(3000); } // preallocate the vector
    inline void clear() { iVec.clear(); }
    
    // insert a value while keeping the list sorted and return the current median after the operation
    unsigned long int insert(unsigned long int value);
    
#if ENABLE_DEBUG
    // printList for debug
    void printList()
    {
        if(iVec.size() > 0)
        {
            for(vector<unsigned long int>::iterator iter = iVec.begin() ; iter != iVec.end(); iter++)
                cout << *iter << " ";
            cout << "\nCurrent Median = " << curMedianVal << endl;
        }
        else
            cout << "List is empty" << endl;
    }
#endif
};

#endif // __MEDIAN_CPPVECTOR_H_