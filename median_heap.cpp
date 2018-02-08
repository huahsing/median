#include "median_list.h"
#include <cassert>

MedianList::MedianList(int maxN)
{
    capacity = maxN / 2 + 2; // 1 extra element (index 0 in array not used)
    heap = new unsigned long int [capacity];
    k = 0;
    inputCnt = 0;
    lastDiscardedSmallestValue = 0;
}

// helper function to compute current median
unsigned long int MedianList::MedianList::getMedian()
{
    unsigned long int curMedian;
    
    if(inputCnt % 2 == 0)
    {
        unsigned long int largerSubTree;
        if(inputCnt == 2 || heap[2] >= heap[3])
            largerSubTree = 2;
        else
            largerSubTree = 3;
        
        curMedian = (heap[1] + heap[largerSubTree]) / 2;
    }
    else
    {
        curMedian = heap[1];
    }
    
#if ENABLE_DEBUG
    curMedianVal = curMedian;
#endif

    return curMedian;
}


#if USE_RECURSION
// helper to reorderHeap after deletion of root (replacement)
void MedianList::reorderHeapAfterRootDiscarded(unsigned long int *Heap, int value)
{
}

// helper function to percolate up when we need to insert a new element into heap
void MedianList::percolateUp(int pos)
{
}
#else
// helper to reorderHeap after deletion of root (replacement)
void MedianList::reorderHeapAfterRootDiscarded(unsigned long int *Heap, int value)
{
    int rootOfSubTree=1, childOfSubTree=2; // childOfSubTree = 2 --> start with left child of root
    
    while(childOfSubTree <= k)
    {
        if(childOfSubTree < k && Heap[childOfSubTree] < Heap[childOfSubTree+1])
            ++childOfSubTree;
        if(value >= Heap[childOfSubTree])
            break; // we should insert value into current root (which is 'empty')
            
        // move value of larger child into current root (so now, child is 'empty' and will become new root in next loop)
        Heap[rootOfSubTree] = Heap[childOfSubTree]; 
        
        // move down before looping again
        rootOfSubTree = childOfSubTree;
        childOfSubTree = rootOfSubTree * 2;
    }
    
    // we found the place to insert the new value
    Heap[rootOfSubTree] = value;
}

// helper function to percolate up when we need to insert a new element into heap
void MedianList::percolateUp(int pos)
{
    unsigned long int swap;
    for(int parent = pos/2; parent >= 1; pos /= 2, parent /= 2)
    {
        if(heap[pos] > heap[parent])
        {
            swap = heap[parent];
            heap[parent] = heap[pos];
            heap[pos] = swap;
        }
    }
    
    // check for valid 'lastDiscardedSmallestValue' first before comparing with root
    if(lastDiscardedSmallestValue > 0 && heap[1] > lastDiscardedSmallestValue)
    {
        // this branch will only happen if the new value inserted percolates all the way up to the root
        // and is also larger than the lastDiscardedSmallestValue
        swap = lastDiscardedSmallestValue;
        lastDiscardedSmallestValue = heap[1];
        heap[1] = swap;
    }
}
#endif

unsigned long int MedianList::insert(unsigned long int value)
{
#if ENABLE_DEBUG
    cout << "====================\ndebug: inserting " << value << endl;
#endif

    int newK;
    
    ++inputCnt;
    newK = inputCnt/2 + 1;
    assert(newK <= capacity);
    
    if(newK == k) // no new element needed, so we need to discard largest
    {
        // note: to successfully enter this branch, k must be >= 2
        //   if k == 0; then inputCnt must be 1 and thus newK != k
        //   if k == 1; then inputCnt must be 2 and thus newK != k
        
        // if new value less than value at root
        if(value < heap[1])
        {
            // we can overwrite root (as root is largest currently, we need to discard it)
            lastDiscardedSmallestValue = heap[1];
            reorderHeapAfterRootDiscarded(heap, value);
        }
        else // new value goes into discard pile, but we need to always track lastDiscardedSmallestValue
        {
            // replace last discarded value if smaller
            if(value < lastDiscardedSmallestValue) lastDiscardedSmallestValue = value;
        }
    }
    else
    {
        // we need to insert a new element into the heap
        k = newK;
        heap[newK] = value;
        percolateUp(newK);
    }
    
    return getMedian();
}