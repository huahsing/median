#ifndef __MEDIAN_CPPLIST_H_
#define __MEDIAN_CPPLIST_H_

#include <iostream>
#include <list>
#include <iterator>

using namespace std;

// This version of MedianList abstracts a C++ list and contains 2 custom behaviour
// 1. always keep the list sorted during insertion
// 2. always track the position of current median
class MedianList
{
private:
    list<unsigned long int> iList;
    list<unsigned long int>::iterator medianPos;

#if ENABLE_DEBUG
    unsigned long int curMedianVal;
#endif

public:
    MedianList(int maxN) {}
    inline void clear() { iList.clear(); }
    
    // insert a value while keeping the list sorted and return the current median after the operation
    unsigned long int insert(unsigned long int value);
    
#if ENABLE_DEBUG
    // printList for debug
    void printList()
    {
        if(iList.size() > 0)
        {
            for(list<unsigned long int>::iterator iter = iList.begin(); iter != iList.end(); iter++)
                cout << *iter << " ";
            cout << "\nCurrent Median = " << curMedianVal << endl;
        }
        else
            cout << "List is empty" << endl;
    }
#endif
};

#endif // __MEDIAN_CPPLIST_H_