#ifndef __DEBUG__
// #define DEBUG

#ifdef DEBUG
    #define LOG1(a,b) printf(a,b)
    #define LOG2(a,b,c) printf(a,b,c)
    #define LOG3(a,b,c,d) printf(a,b,c,d)
#else
    #define NDEBUG
    #define LOG1(a,b)
    #define LOG2(a,b,c)
    #define LOG3(a,b,c,d)
#endif

#include <assert.h>
#endif
