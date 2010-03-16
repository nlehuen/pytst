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
#include <map>
#include <algorithm>

template <typename charT,typename valueT>
class memory_storage {
public:
    typedef typename std::vector< tst_node<charT,valueT> > array_type;
    typedef typename array_type::iterator iterator_type;
    typedef typename array_type::reverse_iterator reverse_iterator_type;
    typedef typename array_type::size_type size_type;

    memory_storage(int initial_size) : array(), empty(UNDEFINED_INDEX) {
        array.reserve(initial_size);
    }

    ~memory_storage() {
    }

    inline tst_node<charT,valueT>* get(int index) {
      return index==UNDEFINED_INDEX ? NULL : &(array[index]);
    }

    inline void delete_node(int index) {
        get(index)->next = empty;
        empty = index;
    }

    void new_node(node_info<charT,valueT>* info);
    void pack(int& root);

    void erase() {
        array_type().swap(array);
    };

    typename array_type::size_type size() {
        return array.size();
    }

protected:
    array_type array;
    int empty;
};

template <typename charT,typename valueT>
void memory_storage<charT,valueT>::new_node(node_info<charT,valueT>* info) {
    if(empty!=UNDEFINED_INDEX) {
        // si on a un noeud vide on l'utilise.
        info->index=empty;
        info->node=get(empty);
        info->node->reset();
        
        // on passe au noeud vide suivant.
        empty = get(empty)->next;
    }
    else {
        // on construit un noeud supplémentaire dans le tableau.
        info->index = (int)array.size();
        array.resize(array.size()+1);
        // array.push_back(tst_node<charT,valueT>()); // Plus ou moins rapide ?
        info->node=get(info->index);
    }
}

template <typename charT,typename valueT>
void memory_storage<charT,valueT>::pack(int& root) {
    if(empty == UNDEFINED_INDEX) {
        return;
    }

    // Etape 1 : on construit un vector des numéros de noeuds vide
    std::vector<int> empty_nodes;
    while(empty!=UNDEFINED_INDEX) {
        empty_nodes.push_back(empty);
        empty = get(empty)->next;
    }

    // Etape 2 : on trie ce vecteur
    std::sort(empty_nodes.begin(),empty_nodes.end());

    // Etape 3 : on remplit les noeuds vides avec des noeuds pleins pris en
    // fin du storage
    std::map<int,int> mapping; // sera utile en étape 4
    int current_empty_node=0, last_empty_node = static_cast<int>(empty_nodes.size())-1;
    int last_node_index = static_cast<int>(array.size())-1 ;

    while(current_empty_node<=last_empty_node) {
        int last_empty_node_index = empty_nodes[last_empty_node];
        if(last_empty_node_index<last_node_index) {
            // le dernier noeud est plein
            // on l'échange avec le premier noeud vide
            int current_empty_node_index = empty_nodes[current_empty_node];
            mapping[last_node_index] = current_empty_node_index;
            array[current_empty_node_index] = array[last_node_index];
            --last_node_index;
            ++current_empty_node;
        }
        else {
            // le dernier noeud est vide
            // on le supprime
            --last_node_index;
            --last_empty_node;
        }
    }

    // Etape 4 : on réécrit les indices
    std::map<int,int>::const_iterator item,end(mapping.end());

    // La racine a peut-être bougé ?
    item = mapping.find(root);
    if(item!=end) {
        root = item->second;
    }

    last_empty_node = 0;
    while(last_empty_node <= last_node_index) {
        tst_node<charT,valueT>* node = get(last_empty_node);
        if(node->left!=UNDEFINED_INDEX) {
            item = mapping.find(node->left);
            if(item!=end) {
                node->left = item->second;
            }
        }
        if(node->right!=UNDEFINED_INDEX) {
            item = mapping.find(node->right);
            if(item!=end) {
                node->right = item->second;
            }
        }
        if(node->next!=UNDEFINED_INDEX) {
            item = mapping.find(node->next);
            if(item!=end) {
                node->next = item->second;
            }
        }

        ++last_empty_node;
    }

    // Etape 5 : on redimensionne le tableau
    array.resize(last_node_index+1);
    array_type(array).swap(array);
}

#endif
