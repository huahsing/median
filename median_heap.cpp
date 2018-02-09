#include "median_list.h"


//////////////////////////////////////////////////////////////////////
//
//                   H E A P   M E T H O D S
//
//////////////////////////////////////////////////////////////////////

// ctor
Heap::Heap(int capacity, HEAP_ORDER_TYPE order)
{
    this->capacity = capacity + 1; // index 0 unused
    this->order = order;
    pHeapArr = new unsigned long int [capacity];
    this->size = 0;
}

// dtor
Heap::~Heap() { delete [] pHeapArr; }

// private helper to check whether we should swap, which will depend on the kind of heap we are, returns true if we should swap
bool Heap::checkSwap(unsigned long int childVal, unsigned long int parentVal)
{
    if(order == MAX_ORDER)
        return (childVal > parentVal);
    else
        return (childVal < parentVal);
}

// after root is deleted, 'value' is the lowest rightmost value to be re-inserted using top-down traversal 
// this is to maintain heap ordering property (ITERATIVE VERSION)
void Heap::fixHeapAfterRootDeleted(unsigned long int *pheapArr, unsigned long int value)
{
    int rootOfSubHeap=1, childOfSubHeap=2; // childOfSubHeap = 2 --> start with left child of root
    
    while(childOfSubHeap <= size)
    {
        if(order == MAX_ORDER)
        {
            if(childOfSubHeap < size && pheapArr[childOfSubHeap] < pheapArr[childOfSubHeap+1])
                ++childOfSubHeap;
        
            // we should insert value into current root (which is 'empty')
            if(value >= pheapArr[childOfSubHeap])
                break; 
        }
        else
        {
            if(childOfSubHeap < size && pheapArr[childOfSubHeap] > pheapArr[childOfSubHeap+1])
                ++childOfSubHeap;
            
            if(value <= pheapArr[childOfSubHeap])
                break; 
        }
            
        // move value of larger/smaller child into current root (so now, child is 'empty' and will become new root in next loop)
        pheapArr[rootOfSubHeap] = pheapArr[childOfSubHeap]; 
        
        // move down before looping again
        rootOfSubHeap = childOfSubHeap;
        childOfSubHeap = rootOfSubHeap * 2;
    }
    
    // we found the place to insert the new value
    pheapArr[rootOfSubHeap] = value;
}

// child is newly inserted index, swap upward until binary heap order is maintained (ITERATIVE VERSION)
void Heap::percolateUp(int child)
{
    unsigned long int swap;
    
    for(int parent = child/2; parent >= 1; child /= 2, parent /= 2)
    {
        if(checkSwap(pHeapArr[child], pHeapArr[parent]))
        {
            swap = pHeapArr[parent];
            pHeapArr[parent] = pHeapArr[child];
            pHeapArr[child] = swap;
        }
    }
}

void Heap::insert(unsigned long int value)
{
    pHeapArr[size+1] = value;
    percolateUp(size+1);
    ++size;
}

bool Heap::getRootValue(unsigned long int *rootValOut)
{
    if(size > 0 && rootValOut)
    {
        *rootValOut = pHeapArr[1];
        return true;
    }
    else return false;
}

bool Heap::deleteRoot(unsigned long int *rootValOut)
{
    if(size > 0 && rootValOut)
    {
        *rootValOut = pHeapArr[1]; 
        --size;
        // remove also lowest rightmost value and send it to fixHeap function to reinsert it (note we reduced the size in previous statement, thus +1 for offset
        fixHeapAfterRootDeleted(pHeapArr, pHeapArr[size+1]);
        
        return true;
    }
    else return false;
}

void Heap::clear() { size = 0; }

int Heap::getSize() { return size; }


/********************************************************************/

//////////////////////////////////////////////////////////////////////
//
//            M E D I A N   L I S T   M E T H O D S
//
//////////////////////////////////////////////////////////////////////

MedianList::MedianList(int maxN)
{
    int spaceNeededPerHeap = (maxN+1) / 2;
    pLowerHalfMaxHeap = new Heap(spaceNeededPerHeap, MAX_ORDER);
    pHigherHalfMinHeap = new Heap(spaceNeededPerHeap, MIN_ORDER);
    totalSize = 0;
}

MedianList::~MedianList()
{
    delete pLowerHalfMaxHeap;
    delete pHigherHalfMinHeap;
}

void MedianList::clear()
{
    pLowerHalfMaxHeap->clear();
    pHigherHalfMinHeap->clear();
    totalSize = 0;
}

// helper function to compute current median
// median(s) are located in root positions of heaps
unsigned long int MedianList::getMedian()
{
    unsigned long int curMedian;
    
    if(totalSize % 2 == 0)
    {
        unsigned long int rootVal;
        pLowerHalfMaxHeap->getRootValue(&rootVal);
        curMedian = rootVal;
        pHigherHalfMinHeap->getRootValue(&rootVal);
        curMedian += rootVal;
        curMedian /= 2;
    }
    else
    {
        if(pLowerHalfMaxHeap->getSize() > pHigherHalfMinHeap->getSize())
            pLowerHalfMaxHeap->getRootValue(&curMedian);
        else
            pHigherHalfMinHeap->getRootValue(&curMedian);
    }
    
#if ENABLE_DEBUG
    curMedianVal = curMedian;
#endif

    return curMedian;
}

unsigned long int MedianList::insert(unsigned long int value)
{
#if ENABLE_DEBUG
    cout << "====================\ndebug: inserting " << value << endl;
#endif

    unsigned long int rootVal;

    if(totalSize == 0) pLowerHalfMaxHeap->insert(value);
    else
    {
        // check which tree to insert into
        pLowerHalfMaxHeap->getRootValue(&rootVal);
        if(value > rootVal)
            pHigherHalfMinHeap->insert(value);
        else
            pLowerHalfMaxHeap->insert(value);
        
        // transfer nodes if unbalanced
        if(pLowerHalfMaxHeap->getSize() - pHigherHalfMinHeap->getSize() >= 2)
        {
            pLowerHalfMaxHeap->deleteRoot(&rootVal);
            pHigherHalfMinHeap->insert(rootVal);
        }
        if(pHigherHalfMinHeap->getSize() - pLowerHalfMaxHeap->getSize() >= 2)
        {
            pHigherHalfMinHeap->deleteRoot(&rootVal);
            pLowerHalfMaxHeap->insert(rootVal);
        }
    }
    
    ++totalSize;
    
    return getMedian();
}
