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

const int UNDEFINED_INDEX=-1;

class TSTException : public exception {
public:
    TSTException(const char* _message) {
        message=_message;
    }

    virtual const char* what() {
        return message;
    }

private:
    const char* message;
};

template<typename S,typename T> class tst_node {
public:
    tst_node() :
        c(0)
        ,data()
        ,next(UNDEFINED_INDEX)
        ,right(UNDEFINED_INDEX)
        ,left(UNDEFINED_INDEX)
#ifdef SCANNER
        ,position(UNDEFINED_INDEX)
        ,backtrack(UNDEFINED_INDEX)
        ,backtrack_match_index(UNDEFINED_INDEX)
#endif
    {
    }

    S c;
    T data;
    int next;
    int right;
    int left;
#ifdef SCANNER
    int position;
    int backtrack;
    int backtrack_match_index;
#endif

    T store(T value) {
        T old = data;
        data = value;
        return old;
    }
};

template<typename S,typename T> class node_info {
public:
    int index;
    tst_node<S,T>* node;

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

template<typename S,typename T> class action {
public:
    action() {}
    virtual ~action() {}
    virtual void perform(const S* string,size_t string_length,int remaining_distance,T data)=0;
    virtual T result()=0;
};

template<typename S,typename T> class filter {
public:
    filter() {}
    virtual ~filter() {}
    virtual T perform(const S* string,size_t string_length,int remaining_distance,T data)=0;
};

template<typename T> class null_reader_writer {
    public:
        void write(FILE* file, T value) {
        }
        
        T read(FILE* file) {
            return T();
        }
};

#endif
