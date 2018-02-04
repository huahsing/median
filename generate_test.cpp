#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

int main()
{
	int TC=100, N, choice;
	bool done = false;
	string filename = "test";
	ofstream testfile;

	cout << "TC has been set to worst case = 100, choose worst case value for N" << endl;
	do
	{
		cout << "1. 500\n2. 3000\nChoice? ";
		cin >> choice;
		switch(choice)
		{
			case 1:
				N = 500;
				break;
				
			case 2:
				N = 3000;
				break;
				
			default:
				cout << "invalid choice" << endl;
				N = 0;
		}
		if(N != 0)
		{
			stringstream strstream;
			strstream << filename << N << ".txt";
			filename = strstream.str();
            ifstream fin(filename.c_str());
			if(fin)
			{
				char choice2;
				cout << "Test file for N=" << N << " already exists, overwrite file? (y/n) ";
				cin >> choice2;
				if(choice2 == 'y' || choice2 == 'Y')
				{
					fin.close();
					testfile.open(filename.c_str(), ios_base::trunc); // discard previous contents;
					done = true;
				}
			}
			else
			{
				testfile.open(filename.c_str());
				done = true;
			}
		}
	} while (!done);
	
	// generate test file
#ifdef _RAND48_H_
	srand48(time(NULL));
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
		randomInt = lrand48() % 1000000000 + 1;
#else
		randomInt = rand() % 1000000000 + 1;
#endif
		testfile << randomInt;
		for(int j = 1; j < N; j++)
		{
#ifdef _RAND48_H_
			randomInt = lrand48() % 1000000000 + 1;
#else
			randomInt = rand() % 1000000000 + 1;
#endif
			testfile << " " << randomInt;
		}
	}
	testfile.close();
	
	return 0;
}