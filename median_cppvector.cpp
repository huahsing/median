#include "median_list.h"

#ifdef CPP_VECTOR

int MedianList::findPos(unsigned long int value)
{    
    // use binary search
    int left, right, m;
    m = left = 0;
    right = iVec.size() - 1;
    
    while(left <= right)
    {
        m = (left + right) / 2;
        if(iVec[m] < value)
            left = m + 1;
        else if(iVec[m] > value)
            right = m - 1;
        else
            break;
    }
    
    if(iVec.size() > 0 && iVec[m] < value) m += 1;
    return m;
}


#if USE_PARTIAL_SORT
#include <algorithm>

// this version performs partial sort after every insertion
unsigned long int MedianList::insert(unsigned long int value)
{
#if ENABLE_DEBUG
    cout << "====================\ndebug: inserting " << value << endl;
#endif
    
    iVec.push_back(value);
    int k = iVec.size() / 2 + 1;
    partial_sort(iVec.begin(), iVec.begin()+k, iVec.end());
    
    return getMedian();
}

#else

// this version uses binary search to find the index for insertion
unsigned long int MedianList::insert(unsigned long int value)
{
#if ENABLE_DEBUG
    cout << "====================\ndebug: inserting " << value << endl;
#endif

    int insertPos = findPos(value);
    vector<unsigned long int>::iterator insertIter = iVec.begin();
    advance(insertIter, insertPos);
    iVec.insert(insertIter, value);
    
    return getMedian();
}

#endif

unsigned long int MedianList::getMedian()
{
    int medianIdx = iVec.size() / 2;
    
    if(iVec.size() % 2 == 0) 
    {
#if ENABLE_DEBUG
        curMedianVal = (iVec.at(medianIdx) + iVec.at(medianIdx - 1)) / 2;
#endif
        return ((iVec.at(medianIdx) + iVec.at(medianIdx - 1)) / 2);

    }
    else 
    {
#if ENABLE_DEBUG
        curMedianVal = iVec.at(medianIdx);
#endif
        return iVec.at(medianIdx);
    }
}



#endif