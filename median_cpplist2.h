#ifndef __MEDIAN_CPPLIST2_H_
#define __MEDIAN_CPPLIST2_H_

#include <iostream>
#include <list>
#include <iterator>

using namespace std;

// This version of MedianList is nearly the same as Median_cpplist
// except that, it contains another preallocated list with 3000 elements
// to avoid memory alloc/dealloc overhead, we will transfer the elements between the lists during insertion / clear operations
// --> for the current number of elements, it is seems only slightly faster
class MedianList
{
private:
    list<unsigned long int> pool;
    list<unsigned long int> iList;
    list<unsigned long int>::iterator medianPos;

#if ENABLE_DEBUG
    unsigned long int curMedianVal;
#endif

public:
    MedianList(int maxN) { pool.assign(maxN, 0); }
    inline void clear() { pool.splice(pool.end(), iList); }
    
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