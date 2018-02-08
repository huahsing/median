#ifndef __MEDIAN_HEAP_H_
#define __MEDIAN_HEAP_H_

#include <iostream>

using namespace std;

class MedianList
{
private:
	unsigned long int *higherHeap; // min-ordered heap
    unsigned long int *lowerHeap; // max-ordered heap
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

#endif // __MEDIAN_HEAP_H_