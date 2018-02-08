#ifndef __MEDIAN_PARTIALHEAP_H_
#define __MEDIAN_PARTIALHEAP_H_

#include <iostream>

using namespace std;

// This version of MedianList abstracts the following data structure
// -> a max-(ordering)-(binary)-heap of k elements where k = i/2 + 1 (1=<i=<N, i is the number of elements in each iteration as a value gets read until N values are read)
// The heap will be implemented using an array of (max(k) + 1) capacity for (max(k) = N/2 + 1), the first element (index=0) will not be used
//    thus: 
//      if N = 7, the FULL heap will have 4 elements (ie. the heap has a capacity of 4, while the array has a capacity of 5)
//      if N = 10, the FULL heap will have 6 elements (ie. the heap has a capacity of 6, while the array has a capacity of 7)
// if space complexity is a concern, then use the STL vector without reserving any capacity 
//  (note that there is usually space-time trade off in complexity, fastest execution usually use the most amount of space, 
//      but sometimes the gains are very little when we sacrifice more space so in real-world we try to find the optimal balance)
//
// if i is odd, the root of the heap stores the 'current median'
// if i is even, the current median = floor of the average of the {'larger subtree of the root (ie. the child node of the root that has a larger value)' + 'the root'}
//
// Principle:
// 1. First understand the rules of the Heap data structure (find videos, web sites and refer to the slides given)
// 2. Partial sort is used to get the smallest k number of items or biggest k number of items from N number of items, and ignoring the rest;
//    for a heap-based implementation, generic algorithm is as follows:
//      - given a list of items
//      - make a heap of any k number of items from the list
//      - for each element AFTER k,
//          - insert the element into heap
//          - discard the largest (or smallest) element (essentially it is the root item after reordering following the insertion)
//              --> if it is a max-ordered heap, root is largest, if it is min-ordered heap, root is smallest
//      - at the end of the 'for' loop, a max-ordered heap will have the smallest k items, while a min-ordered heap will have the largest k items
//
// we need to base our implementation on this idea in heap-based partial sort algorithm and make some adjustments to suit our needs

class MedianList
{
private:
    unsigned long int *heap; // max-ordered heap
    int k; // size, ie. number of elements
    int inputCnt; // track number of inputs so far, max = N
    int capacity; // (max(size) + 1) where max(size)=maxN/2 + 1 --> = maxN/2 + 2
    unsigned long int lastDiscardedSmallestValue;

#if ENABLE_DEBUG
    unsigned long int curMedianVal;
#endif

    unsigned long int getMedian();
    
    // helper to reorderHeap after deletion of root (replacement)
    void reorderHeapAfterRootDiscarded(unsigned long int *Heap, int value);
    
    // helper function to percolate up when we need to insert a new element into heap
    void percolateUp(int pos);

public:
    MedianList(int maxN);
    virtual ~MedianList() { delete [] heap; }
    inline void clear() { k = 0; inputCnt = 0; lastDiscardedSmallestValue = 0; }
    
    unsigned long int insert(unsigned long int value);
    
#if ENABLE_DEBUG
    // printList for debug
    void printList()
    {
        cout << "heap capacity=" << capacity << ", size=" << k << ", current input count=" << inputCnt << ", discarded=" << lastDiscardedSmallestValue << endl;
        if(k > 0)
        {
            for(int i = 0; i <= k; i++)
                cout << heap[i] << " ";
            cout << "\nCurrent Median = " << curMedianVal << endl;
        }
        else
            cout << "List is empty" << endl;
    }
#endif
};

#endif // __MEDIAN_CPPVECTOR_H_