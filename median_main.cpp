/*
    Simplified version
*/

#include <iostream>
#include <ctime>
#include <list>
#include <iterator>

using namespace std;

// turn on debug ("#define ENABLE_DEBUG 0" to turn off)
#define ENABLE_DEBUG 0

#if ENABLE_DEBUG
    #define PRINT_LIST(x) x.printList()
#else
    #define PRINT_LIST(x)
#endif


// MedianList abstracts a C++ list and contains 2 custom behaviour
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

int main()
{
    int TC, N;
    cin >> TC;
    
    // allocate array for answers
    /*
        Note: 
            please read this site for minimum limits: http://www.cplusplus.com/reference/climits/
            if integer is stored in 4 bytes (usually the case), then current median will not overflow, but continuous median might overflow
            (since problem states that largest integer is 10^9 = 1000000000)
            but the standard states integer can be as small as 2 bytes, so there is no guarantee
            To prevent overflow, we should use 'unsigned long long int' to store continuous median, 
                and 'unsigned long int' or 'long int' to store the values and current median (I've opted to use 'unsigned' for all to avoid potential error-prone code)
     */
    unsigned long long int *answers = new unsigned long long int[TC];
    
    MedianList mList;
    unsigned long long int continuousMedian;
    unsigned long int ith_input;
    
    // get current tick number
    clock_t t = clock();
    
    for(int i = 0; i < TC; i++)
    {
        cin >> N;
        
        // reset list and continuousMedianfor each test case
        mList.clear();
        continuousMedian = 0;
        for(int j = 0; j < N; j++)
        {
            cin >> ith_input;
            // after insert i-th input, accumulate the current median into the continuous median for this test case
            continuousMedian += mList.insert(ith_input); // it's ok to store/add smaller type into bigger type
            PRINT_LIST(mList);
        }
        
        // test case is done
        answers[i] = continuousMedian;
    }
    
    t = clock() - t;
    double elapsed_secs = double(t) / CLOCKS_PER_SEC;
    for(int i = 0; i < TC; i++) cout << answers[i] << endl;
    cout << "Number of ticks to execute loops = " << t << ", (" << elapsed_secs << " seconds)" << endl;
    
    // cleanup
    delete [] answers;
    
    return 0;
}