#include "median_list.h"

#ifdef CPP_LIST

unsigned long int MedianList::insert(unsigned long int value)
{
#if ENABLE_DEBUG
    cout << "debug: inserting " << value << endl;
#endif

    if(iList.size() > 0)
    {
        // we need to determine the insertion position
        // the logic is as follows:
        //   - if value >= current median, forward-iterate to find insertion point
        //     else backward-iterate to find insertion point
        list<unsigned long int>::iterator iter = medianPos;
        if(value >= *iter)
        {
            // traversal
            while(iter != iList.end() && value >= *iter) 
                ++iter;
            
            // if we have reached the end and value is still greater, push back
            if(iter == iList.end() && value >= *iter) 
                iList.push_back(value);
            else // else insert at current position (displacing the rest of elements forward)
                iList.insert(iter, value);
            
            // shift median position right if new size is odd
            if(iList.size() % 2 == 1) 
                ++medianPos;
        }
        else
        {
            while(iter != iList.begin() && value < *iter) 
                --iter;
            
            // if we have reached the front and value is still smaller, push front
            if(iter == iList.begin() && value < *iter) 
                iList.push_front(value);
            else
            {
                // else value is greater or equal to *iter and iter is at the front
                // OR
                // iter is not at the front and value is greater or equal to *iter (re-look 'while' loop)
                // hence we must insert after this element
                iList.insert(++iter, value);
            }
            
            // shift median position left if new size is even
            if(iList.size() % 2 == 0) 
                --medianPos;
        }
    }
    else
    {
        // list is empty, just insert value and set median position to start of list
        iList.push_back(value);
        medianPos = iList.begin();
    }
    
    // list size is now guaranteed to be 1 or more
    if(iList.size() % 2 == 1)
    {
#if ENABLE_DEBUG
        curMedianVal = *medianPos;
#endif
        return *medianPos;
    }
    else
    {
        list<unsigned long int>::iterator medianPlusOne = medianPos;
        ++medianPlusOne;
#if ENABLE_DEBUG
        curMedianVal = ((*medianPos + *medianPlusOne) / 2);
#endif
        return ((*medianPos + *medianPlusOne) / 2);
    }
}


#endif