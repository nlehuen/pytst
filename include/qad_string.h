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
 * Building a qad_string from an external backing array won't ever delete the array.
 * Conversely, if the qad_string needs a dynamic backing array (namely, when using push_back), then
 * the class handles its allocation and deallocation automatically through a reference counting scheme.
 */
template <typename charT>
class qad_string {
    public:
        /**
         * Build a qad_string from an array of a given size.
         */
        qad_string(charT* array, size_t size) :
            _array(array),
            _start(0),
            _size(size),
            _shared(0) {
        }

        /**
         * Builds a shallow copy of the given qad_string.
         */
        qad_string(const qad_string<charT> & other) :
            _array(other._array),
            _start(other._start),
            _size(other._size),
            _shared(other._shared) {
            if(_shared) {
                ++(*_shared);
            }
        }

        /**
         * Builds a shallow substring of the given qad_string.
         */
        qad_string(const qad_string<charT> & other,size_t start, size_t size) :
            _array(other._array),
            _start(start),
            _size(size),
            _shared(other._shared) {
            if(_shared) {
                ++(*_shared);
            }
        }

        /**
         * Creates a new, empty string.
         */
        qad_string() : _array(new charT[0]), _start(0), _size(0), _shared(new size_t(1)) {
        }

        ~qad_string() {
            if(_shared) {
                if((--(*_shared))==0) {
                    delete[] _array;
                    delete _shared;
                }
            }
        }

        /**
         * Gets a substring.
         */
        qad_string substr(size_t start,size_t size) const {
            return qad_string(*this,_start+start,size);
        }

        /**
         * Adds a character at the end of the string.
         */
        void push_back(charT c);

        /**
         * Truncates the string. The new size must be lower than the old size.
         */
        void resize(size_t size) {
            if(!_shared) {
                throw std::exception();
            }
            if(size>_size) {
                throw std::exception();
            }
            _size=size;
        }

        /**
         * Finds a character in the string. If the character is not found,
         * then the result value will be equal to size().
         */
        size_t find(charT c) const {
            size_t iP = _start;
            size_t endP = _start+_size;
            for(;iP<endP;iP++) {
                if(_array[iP]==c) {
                    return iP;
                }
            }
            return iP;
        }

        /**
         * Returns the length of the string.
         */
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
        charT* _array;
        size_t _start;
        size_t _size;
        size_t* _shared;
};


template <typename charT>
void qad_string<charT>::push_back(charT c) {
    // When I need a dynamic array, I implicitely use capacities of power of twos (0,1,2,4,8,etc.).
    // This saves me from having to store a capacity field.
    int testP = _size+1;
    int test2P = testP&-testP;
    if(_shared==0 || test2P==testP) {
        if(test2P!=testP) {
            // We come here because we got an array of size not equal to a power of 2.
            // We find the next highest power of 2
            // See http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
            test2P = _size - 1;
            test2P |= test2P >> 1;
            test2P |= test2P >> 2;
            test2P |= test2P >> 4;
            test2P |= test2P >> 8;
            test2P |= test2P >> 16;
            test2P++;
        }
        else {
            // _size+1 is a power of 2, which means we will reach the upper limit
            // So we double the size of the array.
            test2P = testP<<1;
        }

        // We ensure the array size is a power of 2.
        if((test2P&-test2P)!=test2P) throw std::exception();

        // Creates a new array and copy it.
        charT* new_array = new charT[test2P];
        memcpy(new_array,_array,_size*sizeof(charT));

        // If the old array is shared, check whether we need to delete it.
        if(_shared) {
            if((--(*_shared))==0) {
                delete[] _array;
                delete _shared;
            }
        }

        // Use the new array
        _array = new_array;
        _shared = new size_t(1);
    }

    // Store the character in the array
    _array[_size++] = c;
}

#endif
