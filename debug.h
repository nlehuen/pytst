/* 
 # Copyright (C) 2004-2005 Nicolas Lehuen <nicolas@lehuen.com>
 #
 # This library is free software; you can redistribute it and/or
 # modify it under the terms of the GNU Lesser General Public
 # License as published by the Free Software Foundation; either
 # version 2.1 of the License, or (at your option) any later version.
 #
 # This library is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 # Lesser General Public License for more details.
 #
 # You should have received a copy of the GNU Lesser General Public
 # License along with this library; if not, write to the Free Software
 # Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef __DEBUG_H_INCLUDED__
#define __DEBUG_H_INCLUDED__

#define NDEBUG
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
