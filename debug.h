#ifndef __DEBUG_H_INCLUDED__
#define __DEBUG_H_INCLUDED__

//#define NDEBUG
#define NDEBUG_LOG

#ifdef NDEBUG_LOG
    #define LOG0(a)
    #define LOG1(a,b)
    #define LOG2(a,b,c)
    #define LOG3(a,b,c,d)
#else
    #define LOG0(a) printf(a)
    #define LOG1(a,b) printf(a,b)
    #define LOG2(a,b,c) printf(a,b,c)
    #define LOG3(a,b,c,d) printf(a,b,c,d)
#endif

#include <assert.h>
#endif
