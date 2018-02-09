#ifndef __MEDIAN_HEAP_H_
#define __MEDIAN_HEAP_H_

#include <iostream>

using namespace std;

typedef enum
{
    MAX_ORDER,
    MIN_ORDER
} HEAP_ORDER_TYPE;

class Heap
{
private:
    unsigned long int *pHeapArr;
    int size;
    int capacity;
    HEAP_ORDER_TYPE order;
    
    // private helpers
    bool checkSwap(unsigned long int childVal, unsigned long int parentVal);
    void percolateUp(int child);
    void fixHeapAfterRootDeleted(unsigned long int *pheapArr, unsigned long int value);
    
public:
    Heap(int capacity, HEAP_ORDER_TYPE order);
    virtual ~Heap();
    
    void insert(unsigned long int value);
    bool getRootValue(unsigned long int *rootValOut);
    bool deleteRoot(unsigned long int *rootValOut);
    void clear();
    int getSize();
    
#if ENABLE_DEBUG
    // print for debug
    void printHeap()
    {
        cout << "heap capacity(including +1)=" << capacity << ", size=" << size << ", order=" << (order == MAX_ORDER ? "max" : "min") << endl;
        if(size > 0)
        {
            // remember index 0 is not used so upper bound is <=size, but we will print index 0 anyway
            for(int i = 0; i <= size; i++)
                cout << pHeapArr[i] << " ";
            cout << endl;
        }
        else
            cout << "Heap is empty" << endl;
    }
#endif
};

class MedianList
{
private:
	Heap *pLowerHalfMaxHeap; // root is the maximum of the lower half of the list
    Heap *pHigherHalfMinHeap;  // root is the minimum of the upper half of the list
    int totalSize; // total number of elements (ie. number of inputs scanned so far

#if ENABLE_DEBUG
    unsigned long int curMedianVal;
#endif

    unsigned long int getMedian();
    
public:
    MedianList(int maxN);
    virtual ~MedianList();
    
    void clear();
    unsigned long int insert(unsigned long int value);
    
#if ENABLE_DEBUG
    // printList for debug
    void printList()
    {
        cout << "//////////////////////////////\nMEDIAN HEAP: totalSize=" << totalSize << endl;
        cout << "*** Lower half: ***" << endl;
        pLowerHalfMaxHeap->printHeap();
        cout << "*** Upper half: ***" << endl;
        pHigherHalfMinHeap->printHeap();
        cout << "\nCurrent Median = " << curMedianVal << endl;
    }
#endif
};

#endif // __MEDIAN_HEAP_H_