#ifndef __DEBUG_H_INCLUDED__
#define __DEBUG_H_INCLUDED__
// #define NDEBUG

#ifdef NDEBUG
    #define LOG1(a,b)
    #define LOG2(a,b,c)
    #define LOG3(a,b,c,d)
#else
    #define LOG1(a,b) printf(a,b)
    #define LOG2(a,b,c) printf(a,b,c)
    #define LOG3(a,b,c,d) printf(a,b,c,d)
#endif

#include <assert.h>
#endif
