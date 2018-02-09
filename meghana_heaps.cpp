#include <bits/stdc++.h>
using namespace std;

//ios_base::sync_with_stdio(false);
//cin.tie(0); 

class heaps {
  private:
    priority_queue <long long int> lowerHalfMaxHeap; // Declaring a Max Heap
    priority_queue < long long int, vector<long long int>, greater<long long int> > higherHalfMinHeap; // Declaring a Min Heap
  public: 
    void insertval(long long int num);
    long long int findMed();
};

void heaps::insertval(long long int num) {
  long long int temp;
  if (lowerHalfMaxHeap.empty() || num < lowerHalfMaxHeap.top()) 
    lowerHalfMaxHeap.push(num);
  else 
    higherHalfMinHeap.push(num); 
  
  if(lowerHalfMaxHeap.size() - higherHalfMinHeap.size() == 2) { 
      temp = lowerHalfMaxHeap.top();
      higherHalfMinHeap.push(temp);                 
      lowerHalfMaxHeap.pop();                     
    } else if (higherHalfMinHeap.size() - lowerHalfMaxHeap.size() == 2) {  
      temp = higherHalfMinHeap.top();
      lowerHalfMaxHeap.push(temp);                    
      higherHalfMinHeap.pop();                        
    }
}

long long int heaps::findMed () {
  if(lowerHalfMaxHeap.size() == higherHalfMinHeap.size())
    return ((lowerHalfMaxHeap.top() + higherHalfMinHeap.top()) / 2);
  else if (lowerHalfMaxHeap.size() > higherHalfMinHeap.size())
    return lowerHalfMaxHeap.top();
  else
    return higherHalfMinHeap.top();
}

int main() {

  short int TC; //Pre-conditions: TC >= 1 && <= 3
  cin >> TC; //Reading in the test cases
  
  int check = 1; 
  
  while (check <= TC) {
    short int num; 
    cin >> num; //Precondition: num (N) >= 1 && <= 100000
    
   
    long long int input; 
    long long int sum=0;
    long long int med;
    
    heaps interim;

    for (int i=0; i<num; i++) {
      cin >> input;
      //cout << "test" << endl;
      interim.insertval(input);
      //cout << "test1" << endl;
      med = interim.findMed();
      // cout << "med is " << med << endl;
      sum = sum + med; 
    }
    
    cout << sum << endl;
    check++;
  }

  return 0;
  
}



