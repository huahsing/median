#include "median_list.h"
using namespace std;


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