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
#ifndef __MEMORY_STORAGE__H_INCLUDED__
#define __MEMORY_STORAGE__H_INCLUDED__

template<class S,class T> class memory_storage {
public:
    memory_storage(int initial_size) {
        array = new tst_node<S,T>[initial_size];
        next = 0;
        size = initial_size;
        empty=UNDEFINED_INDEX;
    }

    ~memory_storage() {
        delete[] array;
    }

    inline tst_node<S,T>* get(int index) {
        return array+index;
    }

    void new_node(node_info<S,T>* info) {
        if(empty!=UNDEFINED_INDEX) {
            // si on a un noeud vide on l'utilise.
            info->index=empty;
            info->node=get(empty);
            info->height=0;
            
            // on passe au noeud vide suivant.
            empty = get(empty)->next;
        }
        else {
            if(next==size) {
                int new_size = 1 + (size << 1);
                tst_node<S,T>* new_array = new tst_node<S,T>[new_size];
                for(int i=0;i<size;i++) {
                    new_array[i] = array[i];
                }
                delete[] array;
                size = new_size;
                array = new_array;
            }

            info->index = next++;
            info->node=get(info->index);
        }
    }

    void delete_node(int index) {
        get(index)->next = empty;
        empty = index;
    }

    void pack() {
    }    

protected:
    tst_node<S,T>* array;
    int next,size,empty;
};

#endif