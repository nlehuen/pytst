/* 
 # $Id$
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
#ifndef __FUNDAMENTALS__H_INCLUDED__
#define __FUNDAMENTALS__H_INCLUDED__

#include <exception>

const int UNDEFINED_INDEX=-1;

class TSTException : public std::exception {
public:
    TSTException(const char* _message) : message(_message) {
    }

    const char* what() {
        return message;
    }

private:
    const char* message;
};

template <typename charT,typename valueT>
class tst_node {
public:
    tst_node() :
        c(0)
        ,data()
        ,next(UNDEFINED_INDEX)
        ,right(UNDEFINED_INDEX)
        ,left(UNDEFINED_INDEX)
#ifdef SCANNER
        ,position(UNDEFINED_INDEX)
#endif
    {
    }

    charT c;
    valueT data;
    int next;
    int right;
    int left;
#ifdef SCANNER
    int position;
#endif

    valueT store(valueT value) {
        valueT old = data;
        data = value;
        return old;
    }
    
    void reset() {
        c = 0;
        data = valueT();
        next = UNDEFINED_INDEX;
        right = UNDEFINED_INDEX;
        left = UNDEFINED_INDEX;
#ifdef SCANNER
        position = UNDEFINED_INDEX;
#endif
    }
};

template <typename charT,typename valueT>
class node_info {
public:
    int index;
    tst_node<charT,valueT>* node;

    int height;
    int balance;
    int right_balance;
    int left_balance;
    int balance_performed;

    node_info() :
        index(UNDEFINED_INDEX)
        ,node(0)
        ,height(0)
        ,balance(0)
        ,right_balance(0)
        ,left_balance(0)
        ,balance_performed(0)
    {
    }
};

template <typename charT,typename valueT,typename stringT>
class tst_action {
public:
    tst_action() {}
    virtual ~tst_action() {}
    virtual void perform(const stringT & string,int remaining_distance,valueT data)=0;
    virtual valueT result()=0;
};

template <typename charT,typename valueT,typename stringT>
class tst_filter {
public:
    tst_filter() {}
    virtual ~tst_filter() {}
    virtual valueT perform(const stringT & string,int remaining_distance,valueT data)=0;
};

template <typename valueT>
class null_reader_writer {
    public:
        void write(FILE* file, valueT value) {
        }
        
        valueT read(FILE* file) {
            return valueT();
        }
};

#endif
