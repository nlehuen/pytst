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
#ifndef __QAD_STRING__H_INCLUDED__
#define __QAD_STRING__H_INCLUDED__

/**
 * This is a Quick And Dirty string class.
 * Yes, I'm reinventing the wheel. But by doing so, I get a 25% performance improvement.
 * To check the performance difference, just replace qad_string<> by std::basic_string<> in pythonTST.h.
 */
template <typename charT>
class qad_string {
    public:
        /**
         * Build a qad_string from an array of a given size. The string will be read-only. The array won't be deallocated.
         */
        qad_string(charT* array, size_t size) :
            _array(array),
            _start(0),
            _size(size),
            _capacity(size),
            _shared(0) {
        }
    
        /**
         * Builds a shallow  the given qad_string. Read-only strings remain read-only, read-write strings remain read-write.
         */
        qad_string(const qad_string<charT> & other) :
            _array(other._array),
            _start(other._start),
            _size(other._size),
            _capacity(other._capacity),
            _shared(other._shared) {
            if(_shared) {
                ++(*_shared);
            }
        }

        /**
         * Copies a qad_string, with the possibility of making a deep, read-write copy.
         */
        qad_string(const qad_string<charT> & other, bool copy) :
            _size(other._size),
            _shared(other._shared) {
            if(copy && _shared==0) {
                _capacity = _size;
                if(_capacity==0) {
                    _capacity=2;
                }
                _array = new charT[_capacity];
                _start = 0;
                memcpy(_array,other._array+other._start,_size);
                _shared = new size_t(1);
            }
            else {
                _array = other._array;
                _start = other._start;
                _capacity = other._capacity;
                if(_shared) {
                    ++(*_shared);
                }
            }
        }

        /**
         * Creates a new, empty, read-write string.
         */
        qad_string() : _array(new charT[2]), _start(0), _size(0), _capacity(2), _shared(new size_t(1)) {
        }

        ~qad_string() {
            if(_shared) {
                if((--(*_shared))==0) {
                    delete[] _array;
                    delete _shared;
                }
            }
        }

        qad_string substr(size_t start,size_t size) const {
            return qad_string(*this,_start+start,size);
        }

        void push_back(charT c);

        void resize(size_t size) {
            if(!_shared) {
                throw std::exception("This string is not mutable");
            }
            if(size>_size) {
                throw std::exception("This string cannot be expanded");
            }
            _size=size;
        }
        
        size_t find(charT c) const {
            size_t endP = _start+_size;
            for(size_t iP=_start;iP<endP;iP++) {
                if(_array[iP]==c) {
                    return iP;
                }
            }
            return iP;
        }

        size_t size() const {
            return _size;
        }
    
        charT& operator[](size_t indexP) {
            return _array[_start+indexP];
        }

        const charT& operator[](size_t indexP) const {
            return _array[_start+indexP];
        }

        const charT* data() const {
            return _array+_start;
        }

    private:
        qad_string(const qad_string<charT> & other,size_t start, size_t size) : _array(other._array), _start(start), _size(size), _capacity(size), _shared(0) {
            if(_shared) {
                ++(*_shared);
            }
        }

        charT* _array;
        size_t _start;
        size_t _size;
        size_t _capacity;
        size_t* _shared;
};

template <typename charT>
void qad_string<charT>::push_back(charT c) {
    if(!_shared) {
        throw std::exception("This string is immutable");
    }
    
    if(_size>=_capacity) {
        // Creates a new array and copy it.
        size_t new_capacity = _capacity + (_capacity>>1) + 1;
        charT* new_array = new charT[new_capacity];
        memcpy(new_array,_array,_capacity*sizeof(charT));
        
        if(_shared) {
            if((--(*_shared))==0) {
                delete[] _array;
                delete _shared;
            }
        }
        
        _capacity = new_capacity;
        _array = new_array;
        _shared = new size_t(1);
    }

    _array[_size++] = c;
}

#endif
