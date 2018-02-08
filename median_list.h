#ifndef __MEDIAN_LIST_H_
#define __MEDIAN_LIST_H_

#include <iostream>
#include <ctime>

// turn on debug ("#define ENABLE_DEBUG 0" to turn off)
#define ENABLE_DEBUG 1

#if ENABLE_DEBUG
    #define PRINT_LIST(x) x.printList()
#else
    #define PRINT_LIST(x)
#endif

#ifdef CPP_LIST
#include "median_cpplist.h"
#endif

#ifdef CPP_LIST2
#include "median_cpplist2.h"
#endif

#ifdef CPP_VECTOR
#include "median_cppvector.h"
#endif

#ifdef PARTIAL_HEAP
#include "median_partialheap.h"
#endif

#endif // __MEDIAN_LIST_H_