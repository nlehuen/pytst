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

#include <vector>

template<class S,class T> class memory_storage {
public:
    memory_storage(int initial_size) : array(initial_size), next(0), empty(UNDEFINED_INDEX) {
    }

    ~memory_storage() {
    }

    inline tst_node<S,T>* get(int index) {
        return &(array[index]);
    }

    inline void delete_node(int index) {
        get(index)->next = empty;
        empty = index;
    }

    void new_node(node_info<S,T>* info);
    void pack();
    
protected:
    std::vector< tst_node<S,T> > array;
    int next,empty;
};

template<class S,class T> void memory_storage<S,T>::new_node(node_info<S,T>* info) {
    if(empty!=UNDEFINED_INDEX) {
        // si on a un noeud vide on l'utilise.
        info->index=empty;
        info->node=get(empty);
        info->height=0;
        
        // on passe au noeud vide suivant.
        empty = get(empty)->next;
    }
    else {
        // on construit un noeud supplémentaire dans le tableau.
        info->index = next++;
        array.push_back(tst_node<S,T>());
        // array.resize(next); // moins rapide !
        info->node=get(info->index);
    }
}

template<class S,class T> void memory_storage<S,T>::pack() {
    std::vector< tst_node<S,T> >(array).swap(array);
}

#endif
