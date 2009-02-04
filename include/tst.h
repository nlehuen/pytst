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
#ifndef __TST__H_INCLUDED__
#define __TST__H_INCLUDED__

const char* const TST_VERSION = "1.16RC";

#include "debug.h"

#include <iostream>

#ifdef __PYTHON__BUILD__
    #include "Python.h"
    #define tst_malloc PyMem_Malloc
    #define tst_realloc PyMem_Realloc
    #define tst_free PyMem_Free
    // Pour ajouter/supprimer les fonctions de scanning.
    // #define SCANNER
#else
    #include "stdlib.h"
    #define tst_malloc malloc
    #define tst_realloc realloc
    #define tst_free free
    // Pour ajouter/supprimer les fonctions de scanning.
    // #define SCANNER
#endif

template < typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
class tst;

#include "fundamentals.h"
#include "memory_storage.h"
#include "iterators.h"

template < typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
class tst {
public:
    friend class lexical_iterator<charT,valueT,storageT,serializerT,stringT>;
    friend class match_iterator<charT,valueT,storageT,serializerT,stringT>;

    typedef charT character_type;
    typedef valueT value_type;
    typedef storageT storage_type;
    typedef serializerT serializer_type;

    tst();

    virtual ~tst() {
        delete storage;
    }

    void pack() {
        storage->pack(root);
    }
    
    valueT walk(tst_filter<charT,valueT,stringT>* filter,tst_action<charT,valueT,stringT>* to_perform) const;
    valueT walk(tst_filter<charT,valueT,stringT>* filter,tst_action<charT,valueT,stringT>* to_perform,const stringT & string) const;
    valueT close_match(const stringT & string,int maximum_distance,tst_filter<charT,valueT,stringT>* filter,tst_action<charT,valueT,stringT>* to_perform) const;
    valueT prefix_match(const stringT & string,tst_filter<charT,valueT,stringT>* filter,tst_action<charT,valueT,stringT>* to_perform) const;
    valueT match(const stringT & string,tst_filter<charT,valueT,stringT>* filter,tst_action<charT,valueT,stringT>* to_perform) const;

    valueT get(const stringT & string) const;
    valueT get_or_build(const stringT & string,tst_filter<charT,valueT,stringT>* factory);
    valueT put(const stringT & string,valueT data);
    void remove(const stringT & string);
    bool contains(const stringT & string) const;
    void write(std::ostream &file) const;
    void read(std::istream &file);

    lexical_iterator<charT,valueT,storageT,serializerT,stringT> iterator() const {
        stringT key;
        return lexical_iterator<charT,valueT,storageT,serializerT,stringT>(this,key,root);
    }

    lexical_iterator<charT,valueT,storageT,serializerT,stringT> iterator(const stringT & string) const {
        int current_index=root,best_node=UNDEFINED_INDEX;
        find_node(&current_index,&best_node,string);
        return lexical_iterator<charT,valueT,storageT,serializerT,stringT>(this,string.substr(0,string.size()-1),current_index);
    }

    match_iterator<charT,valueT,storageT,serializerT,stringT> close_match_iterator(const stringT & string,int distance) const {
        return match_iterator<charT,valueT,storageT,serializerT,stringT>(this,string,distance,root);
    }
    
    int get_number_of_nodes() const {
        return storage->size();
    }

    valueT get_default_value() const {
        return default_value;
    }

#ifdef SCANNER
    valueT scan(const stringT & string,tst_action<charT,valueT,stringT>* to_perform);
    valueT scan_with_stop_chars(const stringT & string,const stringT& stop_chars,tst_action<charT,valueT,stringT>* to_perform) const;
#endif


protected:
    void set_storage(storageT* new_storage) {
        delete storage;
        storage = new_storage;
    }

private:
    storageT* storage;
    valueT default_value;
    int root;

    void walk_recurse(tst_node<charT,valueT>* current_node,stringT & current_key,tst_filter<charT,valueT,stringT>* filter,tst_action<charT,valueT,stringT>* to_perform) const;
    void close_match_recurse(tst_node<charT,valueT>* current_node,stringT & current_key,const stringT & string,const size_t position, const int distance, const int remaining_distance,tst_filter<charT,valueT,stringT>* filter,tst_action<charT,valueT,stringT>* to_perform) const;
    void match_recurse(tst_node<charT,valueT>* current_node,stringT & current_key,const stringT & string,size_t position, tst_filter<charT,valueT,stringT>* filter,tst_action<charT,valueT,stringT>* to_perform,bool advance) const;
    void match_joker_recurse(tst_node<charT,valueT>* current_node,stringT & current_key,const stringT & string,size_t position, tst_filter<charT,valueT,stringT>* filter,tst_action<charT,valueT,stringT>* to_perform,bool advance) const;
    void match_star_recurse(tst_node<charT,valueT>* current_node,stringT & current_key,const stringT & string,size_t position, tst_filter<charT,valueT,stringT>* filter,tst_action<charT,valueT,stringT>* to_perform,bool advance) const;

    int build_node(node_info<charT,valueT>* current_node,const stringT & string,size_t current_position);
    void remove_node(int* current_index,const stringT & string,const size_t position);
    tst_node<charT,valueT>* find_node(int* current_index,int* best_node, const stringT & string) const;

    void balance_node(node_info<charT,valueT>* bal);
    void ll(node_info<charT,valueT>* bal);
    void rr(node_info<charT,valueT>* bal);
    void lr(node_info<charT,valueT>* bal);
    void rl(node_info<charT,valueT>* bal);
    void compute_height_and_balance(node_info<charT,valueT>* current_node_info) const;

    void write_node(std::ostream& file,serializerT* writer,int index) const;
    int read_node(std::istream& file,serializerT* reader,int depth);

#ifdef SCANNER
    void compute_backtrack(tst_node<charT,valueT> *current_node,const stringT & string,int si_match_start,int si_match_end);
#endif
};

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 tst<charT,valueT,storageT,serializerT,stringT>::tst() :
    storage(new storage_type(16)),
    default_value() {
    node_info<charT,valueT> root_info;
    storage->new_node(&root_info);
    root = root_info.index;
}

/*************************** high-level tree management ***********************/

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 valueT tst<charT,valueT,storageT,serializerT,stringT>::get(const stringT & string) const {
    int current_index=root,best_node=UNDEFINED_INDEX;
    tst_node<charT,valueT>* current_node=find_node(&current_index,&best_node,string);
    if(current_node) {
        return current_node->data;
    }
    else {
        return default_value;
    }
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 bool tst<charT,valueT,storageT,serializerT,stringT>::contains(const stringT & string) const {
    int current_index=root,best_node=UNDEFINED_INDEX;
    tst_node<charT,valueT>* current_node=find_node(&current_index,&best_node,string);
    if(current_node) {
        return true;
    }
    else {
        return false;
    }
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 valueT tst<charT,valueT,storageT,serializerT,stringT>::put(const stringT & string,valueT data) {
    node_info<charT,valueT> root_info;
    root_info.index=root;
    root_info.node=storage->get(root);
    int node_index=build_node(&root_info,string,0);
    root = root_info.index;
    return storage->get(node_index)->store(data);
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 valueT tst<charT,valueT,storageT,serializerT,stringT>::get_or_build(const stringT & string,tst_filter<charT,valueT,stringT>* factory) {
    node_info<charT,valueT> root_info;
    root_info.index=root;
    root_info.node=storage->get(root);
    int node_index=build_node(&root_info,string,0);
    root = root_info.index;

    tst_node<charT,valueT>* current_node=storage->get(node_index);
    
    valueT data = current_node->data; 
    if(data==default_value) {
        data=factory->perform(string,0,current_node->data);
        current_node->store(data);
        return data;
    }
    else {
        return data;
    }
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 void tst<charT,valueT,storageT,serializerT,stringT>::remove(const stringT & string) {
    remove_node(&root,string,0);
    if(root==UNDEFINED_INDEX) {
        node_info<charT,valueT> root_info;
        storage->new_node(&root_info);
        root = root_info.index;
    }
}

/**************************** low-level tree management ***********************/

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 tst_node<charT,valueT>* tst<charT,valueT,storageT,serializerT,stringT>::find_node(int* current_index,int* best_node,const stringT & string) const {
    tst_node<charT,valueT>* current_node;
    int diff;
    size_t pos=0;

    while(*current_index!=UNDEFINED_INDEX) {
        current_node=storage->get(*current_index);

        if(current_node->c==0) {
            *current_index=UNDEFINED_INDEX;
            return 0;
        }
        else {
            diff=string[pos]-(current_node->c);
        }

        if(diff==0) {
            if(current_node->data!=default_value) {
                *best_node=*current_index;
            }

            ++pos;
            if(pos<string.size()) {
                *current_index = current_node->next;
            }
            else {
                return current_node;
            }
        }
        else if(diff>0) {
            *current_index=current_node->right;
        }
        else {
            *current_index=current_node->left;
        }
    }

    return 0;
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 int tst<charT,valueT,storageT,serializerT,stringT>::build_node(node_info<charT,valueT>* current_node_info,const stringT & string,size_t current_position) {
    int diff,result;

    if(current_node_info->node->c==0) {
        current_node_info->node->c=string[current_position];
#ifdef SCANNER
        current_node_info->node->position=current_position;
#endif
        diff=0;
    }
    else {
        diff=string[current_position]-(current_node_info->node->c);
    }

    current_node_info->height=-1;
    current_node_info->balance_performed=0;

    if(diff==0) {
        ++current_position;

        compute_height_and_balance(current_node_info); // TODO : est-ce bien necessaire ?

        if(current_position<string.size()) {
            node_info<charT,valueT> next_node_info;
            next_node_info.index = current_node_info->node->next;
            if(next_node_info.index==UNDEFINED_INDEX) {
                storage->new_node(&next_node_info);
            }
            else {
                next_node_info.node = storage->get(next_node_info.index);
            }
            result=build_node(&next_node_info,string,current_position);
            current_node_info->node = storage->get(current_node_info->index);
            current_node_info->node->next = next_node_info.index;
            return result;
        }
        else {
            return current_node_info->index;
        }
    }
    else if(diff>0) {
        node_info<charT,valueT> next_node_info;
        next_node_info.index = current_node_info->node->right;
        if(next_node_info.index==UNDEFINED_INDEX) {
            storage->new_node(&next_node_info);
        }
        else {
            next_node_info.node = storage->get(next_node_info.index);
        }
        result=build_node(&next_node_info,string,current_position);
        current_node_info->node = storage->get(current_node_info->index);
        current_node_info->node->right = next_node_info.index;

        if(next_node_info.balance_performed) {
            current_node_info->balance_performed=1;
        }
        else {
            if(current_node_info->node->left==UNDEFINED_INDEX) {
                current_node_info->height = next_node_info.height + 1;
                current_node_info->balance = next_node_info.height;
                current_node_info->left_balance = 0;
                current_node_info->right_balance = next_node_info.balance;
            }
            else {
                node_info<charT,valueT> other_node_info;
                other_node_info.index = current_node_info->node->left;    
                other_node_info.node = storage->get(other_node_info.index);
                compute_height_and_balance(&other_node_info);
                if(other_node_info.height>next_node_info.height) {
                    current_node_info->height=other_node_info.height+1;
                }
                else {
                    current_node_info->height=next_node_info.height+1;
                }
                current_node_info->balance = next_node_info.height-other_node_info.height;
                current_node_info->left_balance = other_node_info.balance;
                current_node_info->right_balance = next_node_info.balance;
            }
            balance_node(current_node_info);
        }

        return result;
    }
    else {
        node_info<charT,valueT> next_node_info;
        next_node_info.index = current_node_info->node->left;
        if(next_node_info.index==UNDEFINED_INDEX) {
            storage->new_node(&next_node_info);
        }
        else {
            next_node_info.node = storage->get(next_node_info.index);
        }
        result=build_node(&next_node_info,string,current_position);
        current_node_info->node = storage->get(current_node_info->index);
        current_node_info->node->left = next_node_info.index;

        if(next_node_info.balance_performed) {
            current_node_info->balance_performed=1;
        }
        else {
            if(current_node_info->node->right==UNDEFINED_INDEX) {
                current_node_info->height = next_node_info.height + 1;
                current_node_info->balance = -next_node_info.height;
                current_node_info->right_balance = 0;
                current_node_info->left_balance = next_node_info.balance;
            }
            else {
                node_info<charT,valueT> other_node_info;
                other_node_info.index = current_node_info->node->right;    
                other_node_info.node = storage->get(other_node_info.index);
                compute_height_and_balance(&other_node_info);
                if(other_node_info.height>next_node_info.height) {
                    current_node_info->height=other_node_info.height+1;
                }
                else {
                    current_node_info->height=next_node_info.height+1;
                }
                current_node_info->balance = other_node_info.height-next_node_info.height;
                current_node_info->right_balance = other_node_info.balance;
                current_node_info->left_balance = next_node_info.balance;
            }

            balance_node(current_node_info);
        }

        return result;
    }
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 void tst<charT,valueT,storageT,serializerT,stringT>::remove_node(int* current_index,const stringT & string,const size_t current_position) {
    tst_node<charT,valueT>* current_node = storage->get(*current_index);
    int diff,*next_index;

    if(current_node->c==0) {
        return;
    }
    else {
        diff=string[current_position]-(current_node->c);
    }

    if(diff==0) {
        if(current_position+1<string.size()) {
            next_index = &(current_node->next);
            if(*next_index!=UNDEFINED_INDEX) {
                remove_node(next_index,string,current_position+1);
            }
        }
        else {
            current_node->store(default_value);
        }
    }
    else if(diff>0) {
        next_index = &(current_node->right);
        if(*next_index!=UNDEFINED_INDEX) {
            remove_node(next_index,string,current_position);
        }
    }
    else {
        next_index = &(current_node->left);
        if(*next_index!=UNDEFINED_INDEX) {
            remove_node(next_index,string,current_position);
        }
    }

    current_node=storage->get(*current_index);

    if(   current_node->data==default_value
        && current_node->next==UNDEFINED_INDEX
        && current_node->right==UNDEFINED_INDEX
        && current_node->left==UNDEFINED_INDEX) {
            storage->delete_node(*current_index);
            *current_index=UNDEFINED_INDEX;
        }
    else {
        node_info<charT,valueT> current_node_info;
        current_node_info.index=*current_index;
        current_node_info.node=current_node;
        current_node_info.height=-1;
        balance_node(&current_node_info);
        *current_index = current_node_info.index;
    }
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 void tst<charT,valueT,storageT,serializerT,stringT>::balance_node(node_info<charT,valueT>* bal) {
    if(bal->height==-1) {
        compute_height_and_balance(bal);
    }
    bal->balance_performed=0;
    if(bal->balance>1) {
        if(bal->right_balance>0) {
            rr(bal);
        }
        else {
            rl(bal);
        }
        bal->balance_performed=1;
    }
    else if(bal->balance<-1) {
        if(bal->left_balance<0) {
            ll(bal);
        }
        else {
            lr(bal);
        }
        bal->balance_performed=1;
    }
    
    assert(abs(bal->balance)<2);
    assert(abs(bal->right_balance)<2);
    assert(abs(bal->left_balance)<2);
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 void tst<charT,valueT,storageT,serializerT,stringT>::ll(node_info<charT,valueT>* bal) {
    int left_index=bal->node->left;
    tst_node<charT,valueT>* left_node=storage->get(left_index);
    int left_right_index=left_node->right;
    bal->node->left=left_right_index;
    left_node->right=bal->index;
    
    bal->index=left_index;
    bal->node=storage->get(left_index);
    bal->height=bal->height-1;
    bal->balance=0;
    bal->right_balance=0;
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 void tst<charT,valueT,storageT,serializerT,stringT>::rr(node_info<charT,valueT>* bal) {
    int right_index=bal->node->right;
    tst_node<charT,valueT>* right_node=storage->get(right_index);
    int right_left_index=right_node->left;
    bal->node->right=right_left_index;
    right_node->left=bal->index;
    
    bal->index=right_index;
    bal->node=storage->get(right_index);
    bal->height=bal->height-1;
    bal->balance=0;
    bal->left_balance=0;
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 void tst<charT,valueT,storageT,serializerT,stringT>::lr(node_info<charT,valueT>* bal) {
    node_info<charT,valueT> left;
    left.index = bal->node->left;
    left.node = storage->get(left.index);
    rr(&left);
    bal->node->left=left.index;
    ll(bal);
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 void tst<charT,valueT,storageT,serializerT,stringT>::rl(node_info<charT,valueT>* bal) {
    node_info<charT,valueT> right;
    right.index = bal->node->right;
    right.node = storage->get(right.index);
    ll(&right);
    bal->node->right=right.index;
    rr(bal);
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 void tst<charT,valueT,storageT,serializerT,stringT>::compute_height_and_balance(node_info<charT,valueT>* current_node_info) const {
    int left = current_node_info->node->left;
    int right = current_node_info->node->right;

    if(right!=UNDEFINED_INDEX) {
        node_info<charT,valueT> right_balance;
        right_balance.index=right;
        right_balance.node=storage->get(right);
        compute_height_and_balance(&right_balance);

        if(left!=UNDEFINED_INDEX) {
            node_info<charT,valueT> left_balance;
            left_balance.index=left;
            left_balance.node=storage->get(left);
            compute_height_and_balance(&left_balance);

            if(left_balance.height > right_balance.height) {
                current_node_info->height = left_balance.height+1;
            }
            else {
                current_node_info->height = right_balance.height+1;
            }
            current_node_info->balance = right_balance.height-left_balance.height;
            current_node_info->right_balance = right_balance.balance;
            current_node_info->left_balance = left_balance.balance;
        }
        else {
            current_node_info->height = right_balance.height + 1;
            current_node_info->balance = right_balance.height;
            current_node_info->right_balance = right_balance.balance;
            current_node_info->left_balance = 0;
        }
    }
    else {
        if(left!=UNDEFINED_INDEX) {
            node_info<charT,valueT> left_balance;
            left_balance.index=left;
            left_balance.node=storage->get(left);
            compute_height_and_balance(&left_balance);

            current_node_info->height = left_balance.height + 1;
            current_node_info->balance = -left_balance.height;
            current_node_info->right_balance = 0;
            current_node_info->left_balance = left_balance.balance;
        }
        else {
            current_node_info->height = 0;
            current_node_info->balance = 0;
            current_node_info->right_balance = 0;
            current_node_info->left_balance = 0;
        }
    }
}

/**************************** close_match *************************************/

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 valueT tst<charT,valueT,storageT,serializerT,stringT>::close_match(const stringT & string, int maximum_distance,tst_filter<charT,valueT,stringT>* filter,tst_action<charT,valueT,stringT>* to_perform) const {
    stringT key;
    close_match_recurse(storage->get(root),key,string,0,maximum_distance,maximum_distance,filter,to_perform);
    if(to_perform) {
        return to_perform->result();
    }
    else {
        return default_value;
    }
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 void tst<charT,valueT,storageT,serializerT,stringT>::close_match_recurse(tst_node<charT,valueT>* current_node,stringT& current_key,const stringT & string, const size_t position, const int distance, const int remaining_distance,tst_filter<charT,valueT,stringT>* filter, tst_action<charT,valueT,stringT>* to_perform) const {

    // LEFT
    int other_index=current_node->left;
    if (other_index!=UNDEFINED_INDEX) {
        close_match_recurse(storage->get(other_index),current_key,string,position,distance,remaining_distance,filter,to_perform);
    }

    int diff=1;
    if(position<string.size() && string[position]==current_node->c) {
        diff=0;
    }

    // ++KEY
    current_key.push_back(current_node->c);

    // CURRENT
    valueT data = current_node->data;
    if(data!=default_value) {
        int new_remaining_distance=string.size() - position - 1;
        if(new_remaining_distance<0) {
            new_remaining_distance = 0;
        }
        new_remaining_distance = remaining_distance - diff - new_remaining_distance;

        if(new_remaining_distance>=0) {
            if(filter) {
                data = filter->perform(current_key,distance-new_remaining_distance,data);
            }
            if(data!=default_value && to_perform) {
                to_perform->perform(current_key,distance-new_remaining_distance,data);
            }
        }
    }

    // CURRENT, NEXT
    other_index=current_node->next;
    if (other_index!=UNDEFINED_INDEX) {
        int new_remaining_distance = remaining_distance - diff;
        if (new_remaining_distance>=0) {
            close_match_recurse(storage->get(other_index),current_key,string,position+1,distance,new_remaining_distance,filter,to_perform);
        }
    }

    // SKIP_INPUT
    if(other_index!=UNDEFINED_INDEX && remaining_distance>0) {
        close_match_recurse(storage->get(other_index),current_key,string,position,distance,remaining_distance-1,filter,to_perform);
    }
    
    // --KEY
    current_key.resize(current_key.size()-1);
    
    // SKIP_BASE
    if(position<string.size() && remaining_distance>0) {
        close_match_recurse(current_node,current_key,string,position+1,distance,remaining_distance-1,filter,to_perform);
    }

    // RIGHT
    other_index = current_node->right;
    if(other_index!=UNDEFINED_INDEX) {
        close_match_recurse(storage->get(other_index),current_key,string,position,distance,remaining_distance,filter,to_perform);
    }
}

/**************************** match *************************************/

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 valueT tst<charT,valueT,storageT,serializerT,stringT>::match(const stringT & string,tst_filter<charT,valueT,stringT>* filter,tst_action<charT,valueT,stringT>* to_perform) const {
    stringT key;
    match_recurse(storage->get(root),key,string,0,filter,to_perform,false);
    if(to_perform) {
        return to_perform->result();
    }
    else {
        return default_value;
    }
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 void tst<charT,valueT,storageT,serializerT,stringT>::match_recurse(tst_node<charT,valueT>* current_node,stringT& current_key,const stringT & string, size_t position,tst_filter<charT,valueT,stringT>* filter, tst_action<charT,valueT,stringT>* to_perform, bool advance) const {
    stringT this_key(current_key);

    while(true) {
        charT c = string[position];
        switch(c) {
            case static_cast<charT>('?'): {
                match_joker_recurse(current_node,this_key,string,position,filter,to_perform,advance);
                return;
            }
                
            case static_cast<charT>('*'): {
                match_star_recurse(current_node,this_key,string,position,filter,to_perform,advance);
                return;
            }
    
            default: {
                int other_index;
                if(advance) {
                    other_index = current_node->next;
                    if(other_index!=UNDEFINED_INDEX) {
                        current_node = storage->get(other_index);
                        advance = false;
                    }
                    else {
                        return;
                    }
                }

                while(true) {
                    if(c == current_node->c) {
                        this_key.push_back(current_node->c); 

                        if(position==(string.size()-1)) {
                            valueT data = current_node->data;
                            if(data!=default_value) {
                                if(filter) {
                                    data = filter->perform(this_key,0,data);
                                }
                                if(to_perform) {
                                    to_perform->perform(this_key,0,data);
                                }
                            }
                            return;
                        }
                        else {
                            ++position;
                            advance = true;
                            break;
                        }
                    }
                    else if(c > current_node->c) {
                        other_index = current_node->right;
                        if(other_index!=UNDEFINED_INDEX) {
                            current_node = storage->get(other_index);
                        }
                        else {
                            return;
                        }
                    }
                    else {
                        other_index = current_node->left;
                        if(other_index!=UNDEFINED_INDEX) {
                            current_node = storage->get(other_index);
                        }
                        else {
                            return;
                        }
                    }
                }
            }
        }
    }
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 void tst<charT,valueT,storageT,serializerT,stringT>::match_joker_recurse(tst_node<charT,valueT>* current_node,stringT& current_key,const stringT & string, size_t position,tst_filter<charT,valueT,stringT>* filter, tst_action<charT,valueT,stringT>* to_perform,bool advance) const {
    int other_index;

    if(advance) {
        other_index=current_node->next;
        if(other_index!=UNDEFINED_INDEX) {
            current_node = storage->get(other_index);
        }
        else {
            return;
        }
    }

    // LEFT    
    other_index=current_node->left;
    if(other_index!=UNDEFINED_INDEX) {
        match_joker_recurse(storage->get(other_index),current_key,string,position,filter,to_perform,false);
    }

    // MATCH_CURRENT
    // ++KEY
    current_key.push_back(current_node->c);
    
    if(position==(string.size()-1)) {
        valueT data = current_node->data;
        if(data!=default_value) {
            if(filter) {
                data = filter->perform(current_key,0,data);
            }
            if(to_perform) {
                to_perform->perform(current_key,0,data);
            }
        }
    }
    else {
        match_recurse(current_node,current_key,string,position+1,filter,to_perform,true);
    }
    
    // --KEY
    current_key.resize(current_key.size()-1);

    // RIGHT
    other_index=current_node->right;
    if(other_index!=UNDEFINED_INDEX) {
        match_joker_recurse(storage->get(other_index),current_key,string,position,filter,to_perform,false);
    }
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 void tst<charT,valueT,storageT,serializerT,stringT>::match_star_recurse(tst_node<charT,valueT>* current_node,stringT& current_key,const stringT & string, size_t position,tst_filter<charT,valueT,stringT>* filter, tst_action<charT,valueT,stringT>* to_perform,bool advance) const {
    int other_index;

    if(advance) {
        // PREVIOUS_MATCH
        if(position==(string.size()-1)) {
            valueT data = current_node->data;
            if(data!=default_value) {
                if(filter) {
                    data = filter->perform(current_key,0,data);
                }
                if(to_perform) {
                    to_perform->perform(current_key,0,data);
                }
            }
        }

        other_index=current_node->next;
        if(other_index!=UNDEFINED_INDEX) {
            current_node = storage->get(other_index);
        }
        else {
            return;
        }
    }

    // MATCH_WITHOUT_ME
    match_recurse(current_node,current_key,string,position+1,filter,to_perform,false);

    // MATCH_CURRENT
    current_key.push_back(current_node->c);
    
    if(position==(string.size()-1)) {
        valueT data = current_node->data;
        if(data!=default_value) {
            if(filter) {
                data = filter->perform(current_key,0,data);
            }
            if(to_perform) {
                to_perform->perform(current_key,0,data);
            }
        }
    }

    // MATCH_SAME
    match_star_recurse(current_node,current_key,string,position,filter,to_perform,true);
    
    // MATCH_NEXT
    match_recurse(current_node,current_key,string,position+1,filter,to_perform,true);

    // --KEY
    current_key.resize(current_key.size()-1);

    // LEFT    
    other_index=current_node->left;
    if(other_index!=UNDEFINED_INDEX) {
        match_star_recurse(storage->get(other_index),current_key,string,position,filter,to_perform,false);
    }

    // RIGHT
    other_index=current_node->right;
    if(other_index!=UNDEFINED_INDEX) {
        match_star_recurse(storage->get(other_index),current_key,string,position,filter,to_perform,false);
    }
}

/**************************** walk *************************************/

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 valueT tst<charT,valueT,storageT,serializerT,stringT>::walk(tst_filter<charT,valueT,stringT>* filter,tst_action<charT,valueT,stringT>* to_perform) const {
    stringT key;
    walk_recurse(storage->get(root),key,filter,to_perform);
    if(to_perform) {
        return to_perform->result();
    }
    else {
        return default_value;
    }
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 valueT tst<charT,valueT,storageT,serializerT,stringT>::walk(tst_filter<charT,valueT,stringT>* filter,tst_action<charT,valueT,stringT>* to_perform,const stringT & string) const {
    int index = root;
    int best_node = UNDEFINED_INDEX;
    tst_node<charT,valueT>* start = find_node(&index,&best_node,string);

    if(start) {
        valueT data = start->data;
        if(data!=default_value) {
            if(filter) {
                data = filter->perform(string,0,data);
            }
            if(to_perform) {
                to_perform->perform(string,0,data);
            }
        }
        
        index = start->next; 
        if(index!=UNDEFINED_INDEX) {
            stringT key(string);
            walk_recurse(storage->get(index),key,filter,to_perform);
        }
    }

    if(to_perform) {
        return to_perform->result();
    }
    else {
        return default_value;
    }
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 void tst<charT,valueT,storageT,serializerT,stringT>::walk_recurse(tst_node<charT,valueT>* current_node,stringT& current_key,tst_filter<charT,valueT,stringT>* filter,tst_action<charT,valueT,stringT>* to_perform) const {
    int other_index;

    other_index=current_node->left;
    if(other_index!=UNDEFINED_INDEX) {
        walk_recurse(storage->get(other_index),current_key,filter,to_perform);
    }

    // ++KEY
    current_key.push_back(current_node->c);

    valueT data = current_node->data;
    if(data!=default_value) {
        if(filter) {
            data = filter->perform(current_key,0,data);
        }
        if(to_perform) {
            to_perform->perform(current_key,0,data);
        }
    }

    other_index=current_node->next;
    if(other_index!=UNDEFINED_INDEX) {
        walk_recurse(storage->get(other_index),current_key,filter,to_perform);
    }

    // --KEY
    current_key.resize(current_key.size()-1);

    other_index=current_node->right;
    if(other_index!=UNDEFINED_INDEX) {
        walk_recurse(storage->get(other_index),current_key,filter,to_perform);
    }
}

/**************************** prefix_match *************************************/

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 valueT tst<charT,valueT,storageT,serializerT,stringT>::prefix_match(const stringT & string,tst_filter<charT,valueT,stringT>* filter,tst_action<charT,valueT,stringT>* to_perform) const {
    stringT current_key;
    size_t position=0;

    valueT biggest=default_value;
    int biggest_length=0;
    int current_index=root;
    tst_node<charT,valueT>* current_node;
    int diff;
    charT c;

    while(position<string.size()) {
        c = string[position];
        ++position;

        current_key.push_back(c);

        while(current_index!=UNDEFINED_INDEX) {
            current_node=storage->get(current_index);
            diff=c-current_node->c;
            if(diff==0) {
                if(current_node->data!=default_value) {
                    biggest=current_node->data;
                    biggest_length=current_key.size();
                    if(filter) {
                        biggest=filter->perform(current_key.substr(0,biggest_length),0,biggest);
                    }
                }
                if(position<string.size()) {
                    current_index=current_node->next;
                    break;
                }
                else {
                    if(biggest!=default_value && to_perform) {
                        to_perform->perform(current_key.substr(0,biggest_length),0,biggest);
                    }
                    current_index=current_node->next;
                    if(current_index!=UNDEFINED_INDEX) {
                        walk_recurse(storage->get(current_index),current_key,filter,to_perform);
                    }
                    return to_perform->result();
                }
            }
            else if(diff>0) {
                current_index=current_node->right;
            }
            else {
                current_index=current_node->left;
            }
        }
        if(current_index==UNDEFINED_INDEX) {
            break;
        }
    }

    if(biggest!=default_value && to_perform) {
        to_perform->perform(current_key.substr(0,biggest_length),0,biggest);
    }

    return to_perform->result();
}

/**************************** scan *************************************/

#ifdef SCANNER
template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 valueT tst<charT,valueT,storageT,serializerT,stringT>::scan(const stringT & string,tst_action<charT,valueT,stringT>* to_perform) {
    // Le premier caractère de la chaine ne correspondant pas à un match
    size_t si_non_match_start=0;
    // Le noeud pour lequel on a enregistré un match (noeud avec un objet associé)
    int ni_best_match=UNDEFINED_INDEX;
    // Le premier caractère de la chaine correspondant à un match
    int si_match_start=UNDEFINED_INDEX;
    // La position actuelle dans la chaîne (index)
    size_t si_current=0;
    // Le numéro du noeud actuel de l'arbre
    int ni_current=root;
    // Le noeud actuel de l'arbre
    tst_node<charT,valueT> *n_current;
    // Boucle principale
    while(1) {
        n_current = storage->get(ni_current);

        // On avance dans l'arbre d'un cran
        if(si_current<string.size()) {
            int diff=string[si_current]-n_current->c;
            if(diff>0) {
                ni_current=n_current->right;
            }
            else if(diff<0) {
                ni_current=n_current->left;
            }
            else {
                // ok, le caractère courant est accepté
                if(si_match_start==UNDEFINED_INDEX) {
                    // Si on n'a pas encore enregistré un début de match
                    // on le fait
                    si_match_start=si_current;
                }
                
                if(n_current->data!=default_value) {
                    // Si le noeud en cours contient une valeur
                    // on l'enregistre
                    ni_best_match=ni_current;
                }

                ++si_current;
                if(si_current<string.size()) {
                    // Si on peut avancer, on avance
                    ni_current=n_current->next;
                }
                else {
                    // Fin de chaine ==> pas de match possible
                    ni_current=UNDEFINED_INDEX;
                }
            }
        }
        else {
            // On est toujours en fin de chaine ==> pas de match possible
            ni_current=UNDEFINED_INDEX;
        }

        if(ni_current==UNDEFINED_INDEX) {
            // Le caractère courant n'est pas accepté
            if(ni_best_match!=UNDEFINED_INDEX) {
                // Si on a un match réussi en cours

                // Si le match en cours démarre après la zone de non-match
                // C'est qu'on a bien une zone de non-match
                int non_match_length = si_match_start-si_non_match_start;
                if(non_match_length>0) {
                    // On l'envoie.
                    to_perform->perform(string.substr(si_non_match_start,non_match_length),-non_match_length,default_value);
                }

                // On envoie maintenant le match
                // On connait sa longueur grâce à la position dans l'arbre
                // TODO: voir si on ne pourrait pas de passer de ça
                tst_node<charT,valueT> *match_node=storage->get(ni_best_match);
                int match_length = match_node->position+1;
                // On envoie le match
                to_perform->perform(string.substr(si_match_start,match_length),match_length,match_node->data);
                // On repositionne la zone de non-match juste après la fin du match
                si_non_match_start=si_match_start+match_length;

                // Annulation du match
                ni_best_match=UNDEFINED_INDEX;

                // On backtracke
                compute_backtrack(n_current,string,si_non_match_start,si_current);
                // Le backtrack nous donne là où on se trouve dans le noeud juste après le match...
                ni_current = n_current->backtrack;
                // ... et là où on avait notre meilleur match
                ni_best_match = n_current->backtrack_match_index;

                if(ni_current==root) {
                    // quand on a un retour à la racine, on n'a aucun match en cours
                    si_match_start=UNDEFINED_INDEX;
                }
                else {
                    // sinon c'est qu'un match est en cours, on va recalculer son point de démarrage
                    // grâce à la position du noeud
                    n_current=storage->get(ni_current);
                    si_match_start=si_current-n_current->position;
                }
            }
            else if(si_match_start!=UNDEFINED_INDEX) {
                if(si_current<string.size()) {
                    // Si on n'est pas en fin de chaîne...
                    // Si le caractère courant n'est pas accepté, qu'on avait commencé
                    // un match mais que celui-ci n'avait pas réussi, on va backtracker.
                    compute_backtrack(n_current,string,si_match_start+1,si_current);
                    ni_current = n_current->backtrack;
                    ni_best_match=n_current->backtrack_match_index;

                    if(ni_current==root) {
                        // Quand on a un retour à la racine, on n'a aucun match en cours
                        si_match_start=UNDEFINED_INDEX;
                    }
                    else {
                        // sinon c'est qu'un match est en cours, on va recalculer son point de démarrage
                        // grâce à la position du noeud
                        n_current=storage->get(ni_current);
                        si_match_start=si_current-n_current->position;
                    }
                }
                else {
                    // Si on est en fin de chaîne, on sort.
                    break;
                }
            }
            else {
                // le caractère courant n'est pas accepté et on n'avait pas de match en cours
                if(si_current<string.size()) {
                    // si on peut avancer d'un caractère on le fait
                    ++si_current;
                    // on revient à la racine
                    ni_current = root;
                }
                else {
                    // si on est à la fin de la chaîne on sort de la boucle pour la fin.
                    break;
                }
            }
        }
        else {
            // on avance tranquillement dans l'arbre...
        }
    }

    // on n'arrive ici que si on est arrivé à la fin de la chaine en entrée
    if((si_current - si_non_match_start)>0) {
        // charT'il y avait un non-match en cours
        // on l'envoie
        to_perform->perform(string.substr(si_non_match_start,si_current - si_non_match_start),-static_cast<int>(si_current - si_non_match_start),default_value);
    }

    return to_perform->result();
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 void tst<charT,valueT,storageT,serializerT,stringT>::compute_backtrack(tst_node<charT,valueT> *current_node,const stringT & string, int si_match_start, int si_match_end) {
    if(current_node->backtrack==UNDEFINED_INDEX) {
        while(si_match_start<si_match_end) {
            current_node->backtrack=root;
            current_node->backtrack_match_index=UNDEFINED_INDEX;
            find_node(&(current_node->backtrack),&(current_node->backtrack_match_index),string.substr(si_match_start,si_match_end-si_match_start));
            if(current_node->backtrack==UNDEFINED_INDEX) {
                ++si_match_start;
            }
            else {
                current_node->backtrack=(storage->get(current_node->backtrack))->next;
                break;
            }
        }
        if(current_node->backtrack==UNDEFINED_INDEX) {
            current_node->backtrack=root;
            current_node->backtrack_match_index=UNDEFINED_INDEX;
        }
    }
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 valueT tst<charT,valueT,storageT,serializerT,stringT>::scan_with_stop_chars(const stringT & string,const stringT& stop_chars,tst_action<charT,valueT,stringT>* to_perform) const {
    // Le premier caractère de la chaine ne correspondant pas à un match
    size_t si_non_match_start=0;
    // Le noeud pour lequel on a enregistré un match (noeud avec un objet associé)
    int ni_best_match=UNDEFINED_INDEX;
    // Le premier caractère de la chaine correspondant à un match
    int si_match_start=UNDEFINED_INDEX;
    // La position actuelle dans la chaîne (index)
    size_t si_current=0;
    // Le numéro du noeud actuel de l'arbre
    int ni_current=root;
    // Le noeud actuel de l'arbre
    tst_node<charT,valueT> *n_current;
    // Boucle principale

    while(1) {
        n_current=storage->get(ni_current);

        // On avance dans l'arbre d'un cran
        if(si_current<string.size()) {
            int diff = string[si_current]-n_current->c;
            if(diff>0) {
                ni_current = n_current->right;
            }
            else if(diff<0) {
                ni_current = n_current->left;
            }
            else {
                // ok, le caractère courant est accepté
                if(si_match_start==UNDEFINED_INDEX) {
                    // On teste si le début de match est le début de chaine ou après un stop_char
                    if(si_current==0 || stop_chars.find(string[si_current-1])<stop_chars.size()) {
                        // oui, on enregistre le début
                        si_match_start=si_current;
                    }
                    else {
                        // non, on passe à la suite
                        ++si_current;
                    }
                }
                
                if(si_match_start!=UNDEFINED_INDEX) {
                    // si le démarrage a bien pris

                    if(n_current->data!=default_value && (si_current==(string.size()-1) || stop_chars.find(string[si_current+1])<stop_chars.size())) {
                        // on a une donnée dans le noeud courant
                        // et on est en fin de chaîne ou le caractère précédent est un stop_char
                        ni_best_match = ni_current;
                    }

                    ++si_current;
                    if(si_current<string.size()) {
                        // Si on peut avancer, on avance
                        ni_current = n_current->next;
                    }
                    else {
                        // Fin de chaine ==> pas de match possible
                        ni_current = UNDEFINED_INDEX;
                    }
                }
            }
        }
        else {
            // On est toujours en fin de chaine ==> pas de match possible
            ni_current = UNDEFINED_INDEX;
        }

        if(ni_current==UNDEFINED_INDEX) {
            // Le caractère courant n'est pas accepté
            if(ni_best_match!=UNDEFINED_INDEX) {
                // Si on a un match réussi en cours

                // Si le match en cours démarre après la zone de non-match
                // C'est qu'on a bien une zone de non-match
                int non_match_length = si_match_start-si_non_match_start;
                if(non_match_length>0) {
                    // On l'envoie.
                    to_perform->perform(string.substr(si_non_match_start,non_match_length),-non_match_length,default_value);
                }

                // On envoie maintenant le match
                // On connait sa longueur grâce à la position dans l'arbre
                // TODO: voir si on ne pourrait pas de passer de ça
                tst_node<charT,valueT> *match_node=storage->get(ni_best_match);
                int match_length = match_node->position+1;
                // On envoie le match
                to_perform->perform(string.substr(si_match_start,match_length),match_length,match_node->data);
                // On repositionne la zone de non-match juste après la fin du match
                si_non_match_start=si_match_start+match_length;

                // Annulation du match
                ni_best_match=UNDEFINED_INDEX;

                // On backtracke
                // backtrack de naze parce qu'on ne peut pas utiliser
                // les infos de backtrack à cause des séparateurs.
                si_current = si_non_match_start;
                ni_current = root;
                ni_best_match=UNDEFINED_INDEX;
                si_match_start=UNDEFINED_INDEX;
            }
            else if(si_match_start!=UNDEFINED_INDEX) {
                // Si le caractère courant n'est pas accepté, qu'on avait commencé
                // un match mais que celui-ci n'avait pas réussi, on va backtracker.
                // backtrack de naze parce qu'on ne peut pas utiliser
                // les infos de backtrack à cause des séparateurs.
                si_current=si_match_start+1;
                ni_current = root;
                ni_best_match=UNDEFINED_INDEX;
                si_match_start=UNDEFINED_INDEX;
            }
            else {
                // le caractère courant n'est pas accepté et on n'avait pas de match en cours
                if(si_current<string.size()) {
                    // si on peut avancer d'un caractère on le fait
                    ++si_current;
                    // on revient à la racine
                    ni_current = root;
                }
                else {
                    // si on est à la fin de la chaîne on sort de la boucle pour la fin.
                    break;
                }
            }
        }
        else {
            // on avance tranquillement dans l'arbre...
        }
    }

    // on n'arrive ici que si on est arrivé à la fin de la chaine en entrée
    if((si_current - si_non_match_start)>0) {
        // charT'il y avait un non-match en cours
        // on l'envoie
        to_perform->perform(string.substr(si_non_match_start,si_current - si_non_match_start),-static_cast<int>(si_current - si_non_match_start),default_value);
    }

    return to_perform->result();
}
#endif

/**************************** file I/O *************************************/

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 void tst<charT,valueT,storageT,serializerT,stringT>::read(std::istream& file) {
    // We check the version number
    int version_length;
    file.read((char*)(&version_length),sizeof(size_t));
    char* version=(char*)tst_malloc(version_length+1);
    version[version_length]=0;
    assert(version);
    file.read(version,version_length);

    if(strcmp(TST_VERSION,version)!=0) {
        tst_free(version);
        throw TSTException("Invalid version number");
    }
    else {
        tst_free(version);
    }

    serializerT reader;
    default_value = reader.read(file);

    // On efface le stockage
    storage->erase();

    if(file.get()) {
        root = read_node(file,&reader,0);
    }
    else {
        node_info<charT,valueT> root_info;
        storage->new_node(&root_info);
        root = root_info.index;
    }
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 int tst<charT,valueT,storageT,serializerT,stringT>::read_node(std::istream& file,serializerT* reader,int depth) {
    char bitmask = file.get();

    node_info<charT,valueT> node_info;
    storage->new_node(&node_info);
    
    file.read((char*)(&(node_info.node->c)),sizeof(charT));

    if(bitmask & 16) {
        node_info.node->store(reader->read(file));
    }
    else {
        node_info.node->store(default_value);
    }

#ifdef SCANNER
    // TODO : inutile, peut être recalculé ?
    file.read((char*)(&(node_info.node->position)),sizeof(int));
    file.read((char*)(&(node_info.node->backtrack)),sizeof(int));
    file.read((char*)(&(node_info.node->backtrack_match_index)),sizeof(int));
#endif

    int other_index;

    if(bitmask & 1) {
        // En deux étapes car le noeud peut bouger physiquement.
        // Normalement tout se passe bien mais c'est plus rassurant ainsi.
        other_index = read_node(file,reader,depth+1);
        storage->get(node_info.index)->next = other_index;
    }
    else {
        storage->get(node_info.index)->next = UNDEFINED_INDEX;
    }

    if(bitmask & 2) {
        other_index = read_node(file,reader,depth+1);
        storage->get(node_info.index)->left = other_index;
    }
    else {
        storage->get(node_info.index)->left = UNDEFINED_INDEX;
    }

    if(bitmask & 4) {
        other_index = read_node(file,reader,depth+1);
        storage->get(node_info.index)->right = other_index;
    }
    else {
        storage->get(node_info.index)->right = UNDEFINED_INDEX;
    }

    return node_info.index;
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 void tst<charT,valueT,storageT,serializerT,stringT>::write(std::ostream& file) const {
    // We save the version number
    size_t version_length = strlen(TST_VERSION);
    file.write((char*)(&version_length),sizeof(size_t));
	file.write(TST_VERSION,(std::streamsize)version_length);

    serializerT writer;
    writer.write(file,default_value);

    if(root!=UNDEFINED_INDEX) {
        file.put(1);
        write_node(file,&writer,root);
    }
    else {
        file.put(0);
    }
}

template<typename charT,typename valueT,typename storageT,typename serializerT, typename stringT>
 void tst<charT,valueT,storageT,serializerT,stringT>::write_node(std::ostream& file,serializerT* writer,int index) const {
    tst_node<charT,valueT>* node = storage->get(index);

    char bitmask=0;
    if(node->next!=UNDEFINED_INDEX)  bitmask |= 1;
    if(node->left!=UNDEFINED_INDEX)  bitmask |= 2;
    if(node->right!=UNDEFINED_INDEX) bitmask |= 4;
    if(node->data!=default_value)    bitmask |=16;
    file.put(bitmask);

    file.write((char*)(&(node->c)),sizeof(charT));

    if(bitmask & 16) {
        writer->write(file,node->data);
    }

#ifdef SCANNER
    file.write((char*)(&(node->position)),sizeof(int));
    file.write((char*)(&(node->backtrack)),sizeof(int));
    file.write((char*)(&(node->backtrack_match_index)),sizeof(int));
#endif

    if(bitmask & 1) write_node(file,writer,node->next);
    if(bitmask & 2) write_node(file,writer,node->left);
    if(bitmask & 4) write_node(file,writer,node->right);
}

#endif
