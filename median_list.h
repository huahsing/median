#ifndef __MEDIAN_LIST_H_
#define __MEDIAN_LIST_H_

#include <iostream>
#include <ctime>

// turn on debug ("#define ENABLE_DEBUG 0" to turn off)
#define ENABLE_DEBUG 0

#if ENABLE_DEBUG
    #define PRINT_LIST(x) x.printList()
#else
    #define PRINT_LIST(x)
#endif

#ifdef CPP_LIST
#include "median_cpplist.h"
#endif



#endif // __MEDIAN_LIST_H_