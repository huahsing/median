#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

int main()
{
    int TC, N, i_resolution;
    char choice;
    bool done = false;
    string filename = "test";
    ofstream testfile;

TC_prompt:
    cout << "Enter value for TC (1=<TC=<100)" << endl;
    cin >> TC;
    if(TC < 1 || TC > 100) { cout << "value not in range" << endl; goto TC_prompt; }
N_prompt:
	cout << "Enter value for N (1=<TC=<3000)" << endl;
	cin >> N;
	if(N < 1 || N > 3000) { cout << "value not in range" << endl; goto N_prompt; }
I_prompt:
    cout << "Enter largest value for each integer (10=<i=<10^9) (enter '0' for default=10^9)" << endl;
    cin >> i_resolution;
    if(i_resolution == 0) i_resolution = 1000000000; 
    if(i_resolution < 10 || i_resolution > 1000000000) { cout << "value not in range" << endl; goto I_prompt; }
    
    // create filename
    stringstream strstream;
    strstream << filename << "_TC" << TC << "_N" << N << "_I" << i_resolution << ".txt";
    filename = strstream.str();
    
    // try open file for reading
    ifstream fin(filename.c_str());
    
    // check file existence
    if(fin)
    {
        cout << "Test file already exists, overwrite file? (y/n) ";
        cin >> choice;
        if(choice == 'y' || choice == 'Y')
        {
            fin.close();
            // open file for writing, discard previous contents
            testfile.open(filename.c_str(), ios_base::trunc);
            done = true;
        }
    }
    else
    {
        // open new file for writing
        testfile.open(filename.c_str());
        done = true;
    }
    
    if(!done)
    {
        cout << "Retry? (y/n): ";
        cin >> choice;
        if(choice == 'y' || choice == 'Y') goto TC_prompt;
        else goto EXIT;
    }
	
	// generate test file, if rand48 libraries exist, use them as RAND_MAX is up till 2^31-1
#ifdef _RAND48_H_
    srand48(time(NULL)); cout << "hahaha" << endl;
#else
    srand(time(NULL));
#endif
    testfile << TC << endl;
    for(int i = 0; i < TC; i++)
    {
        long int randomInt;
        if( i == 0 ) testfile << N << endl;
        else testfile << "\n" << N << endl;
#ifdef _RAND48_H_
        randomInt = lrand48() % i_resolution + 1;
#else
        randomInt = rand() % i_resolution + 1;
#endif
        testfile << randomInt;
        for(int j = 1; j < N; j++)
        {
#ifdef _RAND48_H_
            randomInt = lrand48() % i_resolution + 1;
#else
            randomInt = rand() % i_resolution + 1;
#endif
            testfile << " " << randomInt;
        }
    }

EXIT:
    if(testfile.is_open()) testfile.close();
	
    return 0;
}