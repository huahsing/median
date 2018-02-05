#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

int main() {
  int TC;
  cin >> TC; 
  int check = 1;
  unsigned long long int answers[TC];
  int j=0;
  clock_t t = clock();
  
  while (check <= TC) {
    int num; 
    cin >> num; 
    long int arr[num];
    vector <long int> values;
    unsigned long long int sum=0;
    for (int i=0; i<num; i++) {
      cin >> arr[i];
      values.push_back(arr[i]);
      sort(values.begin(), values.end());
      if ((values.size() %2) == 0) {
        long int mid = values.size() / 2;  
        long int median = (values.at(mid) + values.at(mid-1)) / 2;
        sum = sum + median;
      } else {
        long int mid = values.size()/2;
        long int median = values.at(mid);
        sum = sum + median;
      }
    }
    answers[j++] = sum;
    check++;
  }
  t = clock() - t;
  double elapsed_secs = double(t) / CLOCKS_PER_SEC;
  for (int k=0; k<TC; k++) {
    cout << answers[k] << endl;
  }
  cout << "Number of ticks to execute loops = " << t << ", (" << elapsed_secs << " seconds)" << endl;
  
  return 0;
  
}