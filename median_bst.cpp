/*
Overview:
In this version I will use a Binary Search Tree since it is always sorted. It has good performance for insert, remove, search operations. There do not seem to be any BST containers in C++ STL except Maps, which require a unique key for sorting, and we know the values given by the Testcases of Arrays will not be unique, so we cannot easily use Maps.

Refer to here for the space and time complexity of BST: https://en.wikipedia.org/wiki/Binary_search_tree

Description of what is needed:
I need to support a getMedian operation in the Tree.
As I am going to populate a BST for TC times (which can be as many as 100 times), I shall allocate all of the worst case N nodes in advance in a pool to avoid memory allocation/deallocation overhead and use a static BST for the program.
*/
#include <iostream>
#include <cassert>

using namespace std;

struct Node
{
  int data;  
  struct Node* left;
  struct Node* right;
};

class BST
{
  struct Node **pool;
  int poolSize;
  struct Node* root;
  int depth;
  
  BST(int maxSize) 
  { 
    poolSize = maxSize;
    pool = new struct Node*[poolSize];
    assert(pool != NULL);
    for(int i = 0; i < poolSize; i++)
    {
      pool[i] = new struct Node;
      assert(pool[i] != NULL);
    }
    root = NULL; 
    depth = 0; 
  }
  
  ~BST()
  {
    for(int i = 0; i < poolSize; i++)
    {
      delete pool[i];
    }
    delete [] pool;
  }
  
  void insert(int i) {}
  int findMedian() {}
};


int main()
{
  
  
  return 0;
}
