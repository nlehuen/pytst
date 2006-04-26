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

const char* const TST_VERSION = "1.12";

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

template< typename S,typename T,typename M,typename RW > class tst;

#include "fundamentals.h"
#include "memory_storage.h"
#include "iterators.h"

template< typename S,typename T,typename M=memory_storage<S,T>,typename RW=null_reader_writer<T> > class tst {
public:
    friend class lexical_iterator<S,T,M,RW>;
    friend class match_iterator<S,T,M,RW>;

    typedef S character_type;
    typedef T value_type;
    typedef M storage_type;
    typedef RW serializer_type;

    tst();

    virtual ~tst() {
        delete storage;
    }

    void pack() {
        storage->pack(root);
    }
    
    T walk(filter<S,T>* filter,action<S,T>* to_perform) const;
    T walk(filter<S,T>* filter,action<S,T>* to_perform,const S* string, size_t string_length) const;
    T close_match(const S* string,size_t string_length,int maximum_distance,filter<S,T>* filter,action<S,T>* to_perform) const;
    T prefix_match(const S* string,size_t string_length,filter<S,T>* filter,action<S,T>* to_perform) const;
    T match(const S* string,size_t string_length,filter<S,T>* filter,action<S,T>* to_perform) const;

    T get(const S* string,size_t string_length) const;
    T get_or_build(const S* string,size_t string_length,filter<S,T>* factory);
    T put(const S* string,size_t string_length,T data);
    void remove(const S* string,size_t string_length);
    bool contains(const S* string,size_t string_length) const;
    int get_maximum_key_length() const { return maximum_key_length; }
    void write(std::ostream &file) const;
    void read(std::istream &file);

    lexical_iterator<S,T,M,RW> iterator() const {
        return lexical_iterator<S,T,M,RW>(this,std::basic_string<S>(""),root);
    }

    lexical_iterator<S,T,M,RW> iterator(const S* string,size_t string_length) const {
        int current_index=root,best_node=UNDEFINED_INDEX;
        find_node(&current_index,&best_node,string,string_length);
        return lexical_iterator<S,T,M,RW>(this,std::basic_string<S>(string,string_length-1),current_index);
    }

    match_iterator<S,T,M,RW> close_match_iterator(const S* string,size_t string_length,int distance) const {
        return match_iterator<S,T,M,RW>(this,std::basic_string<S>(string,string_length),distance,root);
    }
    
    int get_number_of_nodes() const {
        return storage->size();
    }

    T get_default_value() const {
        return default_value;
    }

#ifdef SCANNER
    T scan(const S* string,size_t string_length,action<S,T>* to_perform);
    T scan_with_stop_chars(const S* string,size_t string_length,const S* stop_chars,size_t stop_chars_length,action<S,T>* to_perform) const;
#endif


protected:
    void set_storage(M* new_storage) {
        delete storage;
        storage = new_storage;
    }

private:
    M* storage;
    T default_value;
    int root,maximum_key_length;

    void walk_recurse(tst_node<S,T>* current_node,S* current_key,size_t current_key_length,size_t current_key_limit,filter<S,T>* filter,action<S,T>* to_perform) const;
    void close_match_recurse(tst_node<S,T>* current_node,S* key, const size_t key_length,const S* string, const size_t string_length,const size_t position, const int distance, const int remaining_distance,filter<S,T>* filter,action<S,T>* to_perform) const;
    void match_recurse(tst_node<S,T>* current_node,S* key, const size_t key_length,const S* string, const size_t string_length,size_t position, filter<S,T>* filter,action<S,T>* to_perform,bool advance) const;
    void match_joker_recurse(tst_node<S,T>* current_node,S* key, const size_t key_length,const S* string, const size_t string_length,size_t position, filter<S,T>* filter,action<S,T>* to_perform,bool advance) const;
    void match_star_recurse(tst_node<S,T>* current_node,S* key, const size_t key_length,const S* string, const size_t string_length,size_t position, filter<S,T>* filter,action<S,T>* to_perform,bool advance) const;

    int build_node(node_info<S,T>* current_node,const S* string,size_t string_length,int current_position);
    void remove_node(int* current_index,const S* string,size_t string_length);
    tst_node<S,T>* find_node(int* current_index,int* best_node, const S* string,size_t string_length) const;

    void balance_node(node_info<S,T>* bal);
    void ll(node_info<S,T>* bal);
    void rr(node_info<S,T>* bal);
    void lr(node_info<S,T>* bal);
    void rl(node_info<S,T>* bal);
    void compute_height_and_balance(node_info<S,T>* current_node_info) const;

    void write_node(std::ostream& file,RW* writer,int index) const;
    int read_node(std::istream& file,RW* reader,int depth);

#ifdef SCANNER
    void compute_backtrack(tst_node<S,T> *current_node,const S* string,int si_match_start,int si_match_end);
#endif
};

template <typename S, typename T, typename M=memory_storage<S,T>, typename RW=null_reader_writer<T> > class string_tst : public tst<S,T,M,RW> {
    public:
        T put(std::basic_string<S> string, T value) {
            return tst<S,T,M,RW>::put(string.c_str(),string.size(),value);
        }

        T get(std::basic_string<S> string) const {
            return tst<S,T,M,RW>::get(string.c_str(),string.size());
        }
        
        T get_or_build(std::basic_string<S> string,filter<S,T>* factory) {
            return tst<S,T,M,RW>::get_or_build(string.c_str(),string.size(),factory);
        }

        void remove(std::basic_string<S> string) {
            tst<S,T,M,RW>::remove(string.c_str(),string.size());
        }

        bool contains(std::basic_string<S> string) const {
            return tst<S,T,M,RW>::contains(string.c_str(),string.size());
        }

        T walk1(filter<S,T> *filter,action<S,T> *to_perform) const {
            return tst<S,T,M,RW>::walk(filter,to_perform);
        }

        T walk2(filter<S,T> *filter,action<S,T> *to_perform,std::basic_string<S> string) const {
            return tst<S,T,M,RW>::walk(filter,to_perform,string.c_str(),string.size());
        }
        
        T close_match(std::basic_string<S> string,int maximum_distance,filter<S,T> *filter,action<S,T> *to_perform) const {
            return tst<S,T,M,RW>::close_match(string.c_str(),string.size(),maximum_distance,filter,to_perform);
        }
        
        T prefix_match(std::basic_string<S> string,filter<S,T> *filter,action<S,T> *to_perform) const {
            return tst<S,T,M,RW>::prefix_match(string.c_str(),string.size(),filter,to_perform);
        }

        T match(std::basic_string<S> string,filter<S,T> *filter,action<S,T> *to_perform) const {
            return tst<S,T,M,RW>::match(string.c_str(),string.size(),filter,to_perform);
        }

#ifdef SCANNER
        T scan(std::basic_string<S> string,action<S,T>* to_perform) {
            return tst<S,T,M,RW>::scan(string.c_str(),string.size(),to_perform);
        }
        
        T scan_with_stop_chars(std::basic_string<S> string,std::basic_string<S> stop_chars,action<S,T>* to_perform) {
            return tst<S,T,M,RW>::scan_with_stop_chars(string.c_str(),string.size(),stop_chars.c_str(),stop_chars.size(),to_perform);
        }
#endif
};

template<typename S,typename T,typename M,typename RW> tst<S,T,M,RW>::tst() :
    storage(new storage_type(16)),
    default_value(),
    maximum_key_length(0) {
    node_info<S,T> root_info;
    storage->new_node(&root_info);
    root = root_info.index;
}

/*************************** high-level tree management ***********************/

template<typename S,typename T,typename M,typename RW> T tst<S,T,M,RW>::get(const S* string,size_t string_length) const {
    int current_index=root,best_node=UNDEFINED_INDEX;
    tst_node<S,T>* current_node=find_node(&current_index,&best_node,string,string_length);
    if(current_node) {
        return current_node->data;
    }
    else {
        return default_value;
    }
}

template<typename S,typename T,typename M,typename RW> bool tst<S,T,M,RW>::contains(const S* string,size_t string_length) const {
    int current_index=root,best_node=UNDEFINED_INDEX;
    tst_node<S,T>* current_node=find_node(&current_index,&best_node,string,string_length);
    if(current_node) {
        return true;
    }
    else {
        return false;
    }
}

template<typename S,typename T,typename M,typename RW> T tst<S,T,M,RW>::put(const S* string,size_t string_length,T data) {
    node_info<S,T> root_info;
    root_info.index=root;
    root_info.node=storage->get(root);
    int node_index=build_node(&root_info,string,string_length,0);
    root = root_info.index;
    return storage->get(node_index)->store(data);
}

template<typename S,typename T,typename M,typename RW> T tst<S,T,M,RW>::get_or_build(const S* string,size_t string_length,filter<S,T>* factory) {
    node_info<S,T> root_info;
    root_info.index=root;
    root_info.node=storage->get(root);
    int node_index=build_node(&root_info,string,string_length,0);
    root = root_info.index;

    tst_node<S,T>* current_node=storage->get(node_index);
    
    T data = current_node->data; 
    if(data==default_value) {
        data=factory->perform(string,string_length,0,current_node->data);
        current_node->store(data);
        return data;
    }
    else {
        return data;
    }
}

template<typename S,typename T,typename M,typename RW> void tst<S,T,M,RW>::remove(const S* string,size_t string_length) {
    remove_node(&root,string,string_length);
    if(root==UNDEFINED_INDEX) {
        node_info<S,T> root_info;
        storage->new_node(&root_info);
        root = root_info.index;
    }
}

/**************************** low-level tree management ***********************/

template<typename S,typename T,typename M,typename RW> tst_node<S,T>* tst<S,T,M,RW>::find_node(int* current_index,int* best_node,const S* string,size_t string_length) const {
    tst_node<S,T>* current_node;
    int diff;

    while(*current_index!=UNDEFINED_INDEX) {
        current_node=storage->get(*current_index);

        if(current_node->c==0) {
            *current_index=UNDEFINED_INDEX;
            return 0;
        }
        else {
            diff=(*string)-(current_node->c);
        }

        if(diff==0) {
            if(current_node->data!=default_value) {
                *best_node=*current_index;
            }

            ++string;
            --string_length;
            if(string_length>0) {
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

template<typename S,typename T,typename M,typename RW> int tst<S,T,M,RW>::build_node(node_info<S,T>* current_node_info,const S* string,size_t string_length,int current_position) {
    int diff,result;

    if(current_node_info->node->c==0) {
        current_node_info->node->c=(*string);
#ifdef SCANNER
        current_node_info->node->position=current_position;
#endif
        diff=0;
    }
    else {
        diff=(*string)-(current_node_info->node->c);
    }

    current_node_info->height=-1;
    current_node_info->balance_performed=0;

    if(diff==0) {
        ++string;
        ++current_position;
        --string_length;

        if(current_position>maximum_key_length) {
            maximum_key_length=current_position;
        }

        compute_height_and_balance(current_node_info); // TODO : est-ce bien necessaire ?

        if(string_length>0) {
            node_info<S,T> next_node_info;
            next_node_info.index = current_node_info->node->next;
            if(next_node_info.index==UNDEFINED_INDEX) {
                storage->new_node(&next_node_info);
            }
            else {
                next_node_info.node = storage->get(next_node_info.index);
            }
            result=build_node(&next_node_info,string,string_length,current_position);
            current_node_info->node = storage->get(current_node_info->index);
            current_node_info->node->next = next_node_info.index;
            return result;
        }
        else {
            return current_node_info->index;
        }
    }
    else if(diff>0) {
        node_info<S,T> next_node_info;
        next_node_info.index = current_node_info->node->right;
        if(next_node_info.index==UNDEFINED_INDEX) {
            storage->new_node(&next_node_info);
        }
        else {
            next_node_info.node = storage->get(next_node_info.index);
        }
        result=build_node(&next_node_info,string,string_length,current_position);
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
                node_info<S,T> other_node_info;
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
        node_info<S,T> next_node_info;
        next_node_info.index = current_node_info->node->left;
        if(next_node_info.index==UNDEFINED_INDEX) {
            storage->new_node(&next_node_info);
        }
        else {
            next_node_info.node = storage->get(next_node_info.index);
        }
        result=build_node(&next_node_info,string,string_length,current_position);
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
                node_info<S,T> other_node_info;
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

template<typename S,typename T,typename M,typename RW> void tst<S,T,M,RW>::remove_node(int* current_index,const S* string,size_t string_length) {
    tst_node<S,T>* current_node = storage->get(*current_index);
    int diff,*next_index;

    if(current_node->c==0) {
        return;
    }
    else {
        diff=(*string)-(current_node->c);
    }

    if(diff==0) {
        ++string;
        --string_length;
        if(string_length>0) {
            next_index = &(current_node->next);
            if(*next_index!=UNDEFINED_INDEX) {
                remove_node(next_index,string,string_length);
            }
        }
        else {
            current_node->store(default_value);
        }
    }
    else if(diff>0) {
        next_index = &(current_node->right);
        if(*next_index!=UNDEFINED_INDEX) {
            remove_node(next_index,string,string_length);
        }
    }
    else {
        next_index = &(current_node->left);
        if(*next_index!=UNDEFINED_INDEX) {
            remove_node(next_index,string,string_length);
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
        node_info<S,T> current_node_info;
        current_node_info.index=*current_index;
        current_node_info.node=current_node;
        current_node_info.height=-1;
        balance_node(&current_node_info);
        *current_index = current_node_info.index;
    }
}

template<typename S,typename T,typename M,typename RW> void tst<S,T,M,RW>::balance_node(node_info<S,T>* bal) {
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

template<typename S,typename T,typename M,typename RW> void tst<S,T,M,RW>::ll(node_info<S,T>* bal) {
    int left_index=bal->node->left;
    tst_node<S,T>* left_node=storage->get(left_index);
    int left_right_index=left_node->right;
    bal->node->left=left_right_index;
    left_node->right=bal->index;
    
    bal->index=left_index;
    bal->node=storage->get(left_index);
    bal->height=bal->height-1;
    bal->balance=0;
    bal->right_balance=0;
}

template<typename S,typename T,typename M,typename RW> void tst<S,T,M,RW>::rr(node_info<S,T>* bal) {
    int right_index=bal->node->right;
    tst_node<S,T>* right_node=storage->get(right_index);
    int right_left_index=right_node->left;
    bal->node->right=right_left_index;
    right_node->left=bal->index;
    
    bal->index=right_index;
    bal->node=storage->get(right_index);
    bal->height=bal->height-1;
    bal->balance=0;
    bal->left_balance=0;
}

template<typename S,typename T,typename M,typename RW> void tst<S,T,M,RW>::lr(node_info<S,T>* bal) {
    node_info<S,T> left;
    left.index = bal->node->left;
    left.node = storage->get(left.index);
    rr(&left);
    bal->node->left=left.index;
    ll(bal);
}

template<typename S,typename T,typename M,typename RW> void tst<S,T,M,RW>::rl(node_info<S,T>* bal) {
    node_info<S,T> right;
    right.index = bal->node->right;
    right.node = storage->get(right.index);
    ll(&right);
    bal->node->right=right.index;
    rr(bal);
}

template<typename S,typename T,typename M,typename RW> void tst<S,T,M,RW>::compute_height_and_balance(node_info<S,T>* current_node_info) const {
    int left = current_node_info->node->left;
    int right = current_node_info->node->right;

    if(right!=UNDEFINED_INDEX) {
        node_info<S,T> right_balance;
        right_balance.index=right;
        right_balance.node=storage->get(right);
        compute_height_and_balance(&right_balance);

        if(left!=UNDEFINED_INDEX) {
            node_info<S,T> left_balance;
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
            node_info<S,T> left_balance;
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

template<typename S,typename T,typename M,typename RW> T tst<S,T,M,RW>::close_match(const S* string, size_t string_length, int maximum_distance,filter<S,T>* filter,action<S,T>* to_perform) const {
    S* current_key=(S*)tst_malloc((string_length+maximum_distance+2)*sizeof(S));
    *current_key='\0';
    close_match_recurse(storage->get(root),current_key,0,string,string_length,0,maximum_distance,maximum_distance,filter,to_perform);
    tst_free(current_key);
    if(to_perform) {
        return to_perform->result();
    }
    else {
        return default_value;
    }
}

template<typename S,typename T,typename M,typename RW> void tst<S,T,M,RW>::close_match_recurse(tst_node<S,T>* current_node,S* key,size_t key_length,const S* string,const size_t string_length, const size_t position, const int distance, const int remaining_distance,filter<S,T>* filter, action<S,T>* to_perform) const {

    // LEFT
    int other_index=current_node->left;
    if (other_index!=UNDEFINED_INDEX) {
        close_match_recurse(storage->get(other_index),key,key_length,string,string_length,position,distance,remaining_distance,filter,to_perform);
    }

    int diff=1;
    if(position<string_length && string[position]==current_node->c) {
        diff=0;
    }

    // ++KEY
    key[key_length]=current_node->c;
    ++key_length;

    // CURRENT
    T data = current_node->data;
    if(data!=default_value) {
        int new_remaining_distance=string_length - position - 1;
        if(new_remaining_distance<0) {
            new_remaining_distance = 0;
        }
        new_remaining_distance = remaining_distance - diff - new_remaining_distance;

        if(new_remaining_distance>=0) {
            if(filter) {
                data = filter->perform(key,key_length,distance-new_remaining_distance,data);
            }
            if(data!=default_value && to_perform) {
                to_perform->perform(key,key_length,distance-new_remaining_distance,data);
            }
        }
    }

    // CURRENT, NEXT
    other_index=current_node->next;
    if (other_index!=UNDEFINED_INDEX) {
        int new_remaining_distance = remaining_distance - diff;
        if (new_remaining_distance>=0) {
            close_match_recurse(storage->get(other_index),key,key_length,string,string_length,position+1,distance,new_remaining_distance,filter,to_perform);
        }
    }

    // SKIP_INPUT
    if(other_index!=UNDEFINED_INDEX && remaining_distance>0) {
        close_match_recurse(storage->get(other_index),key,key_length,string,string_length,position,distance,remaining_distance-1,filter,to_perform);
    }
    
    // KEY--
    key_length--;

    // SKIP_BASE
    if(position<string_length && remaining_distance>0) {
        close_match_recurse(current_node,key,key_length,string,string_length,position+1,distance,remaining_distance-1,filter,to_perform);
    }

    // RIGHT
    other_index = current_node->right;
    if(other_index!=UNDEFINED_INDEX) {
        close_match_recurse(storage->get(other_index),key,key_length,string,string_length,position,distance,remaining_distance,filter,to_perform);
    }
}

/**************************** match *************************************/

template<typename S,typename T,typename M,typename RW> T tst<S,T,M,RW>::match(const S* string, size_t string_length,filter<S,T>* filter,action<S,T>* to_perform) const {
    S* current_key=(S*)tst_malloc((string_length+maximum_key_length+2)*sizeof(S));
    match_recurse(storage->get(root),current_key,0,string,string_length,0,filter,to_perform,false);
    tst_free(current_key);
    if(to_perform) {
        return to_perform->result();
    }
    else {
        return default_value;
    }
}

template<typename S,typename T,typename M,typename RW> void tst<S,T,M,RW>::match_recurse(tst_node<S,T>* current_node,S* key,size_t key_length,const S* string,const size_t string_length, size_t position,filter<S,T>* filter, action<S,T>* to_perform, bool advance) const {
    while(true) {
        S c = string[position];
        switch(c) {
            case static_cast<S>('?'): {
                match_joker_recurse(current_node,key,key_length,string,string_length,position,filter,to_perform,advance);
                return;
            }
                
            case static_cast<S>('*'): {
                match_star_recurse(current_node,key,key_length,string,string_length,position,filter,to_perform,advance);
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
                        key[key_length]=current_node->c;
                        ++key_length;

                        if(position==(string_length-1)) {
                            T data = current_node->data;
                            if(data!=default_value) {
                                if(filter) {
                                    data = filter->perform(key,key_length,0,data);
                                }
                                if(to_perform) {
                                    to_perform->perform(key,key_length,0,data);
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

template<typename S,typename T,typename M,typename RW> void tst<S,T,M,RW>::match_joker_recurse(tst_node<S,T>* current_node,S* key,size_t key_length,const S* string,const size_t string_length, size_t position,filter<S,T>* filter, action<S,T>* to_perform,bool advance) const {
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
        match_joker_recurse(storage->get(other_index),key,key_length,string,string_length,position,filter,to_perform,false);
    }

    // MATCH_CURRENT
    key[key_length]=current_node->c;
    ++key_length;
    
    if(position==(string_length-1)) {
        T data = current_node->data;
        if(data!=default_value) {
            if(filter) {
                data = filter->perform(key,key_length,0,data);
            }
            if(to_perform) {
                to_perform->perform(key,key_length,0,data);
            }
        }
    }
    else {
        match_recurse(current_node,key,key_length,string,string_length,position+1,filter,to_perform,true);
    }

    key_length--;
    
    // RIGHT
    other_index=current_node->right;
    if(other_index!=UNDEFINED_INDEX) {
        match_joker_recurse(storage->get(other_index),key,key_length,string,string_length,position,filter,to_perform,false);
    }
}

template<typename S,typename T,typename M,typename RW> void tst<S,T,M,RW>::match_star_recurse(tst_node<S,T>* current_node,S* key,size_t key_length,const S* string,const size_t string_length, size_t position,filter<S,T>* filter, action<S,T>* to_perform,bool advance) const {
    int other_index;

    if(advance) {
        // PREVIOUS_MATCH
        if(position==(string_length-1)) {
            T data = current_node->data;
            if(data!=default_value) {
                if(filter) {
                    data = filter->perform(key,key_length,0,data);
                }
                if(to_perform) {
                    to_perform->perform(key,key_length,0,data);
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
    match_recurse(current_node,key,key_length,string,string_length,position+1,filter,to_perform,false);

    // MATCH_CURRENT
    key[key_length]=current_node->c;
    ++key_length;
    
    if(position==(string_length-1)) {
        T data = current_node->data;
        if(data!=default_value) {
            if(filter) {
                data = filter->perform(key,key_length,0,data);
            }
            if(to_perform) {
                to_perform->perform(key,key_length,0,data);
            }
        }
    }

    // MATCH_SAME
    match_star_recurse(current_node,key,key_length,string,string_length,position,filter,to_perform,true);
    
    // MATCH_NEXT
    match_recurse(current_node,key,key_length,string,string_length,position+1,filter,to_perform,true);

    key_length--;

    // LEFT    
    other_index=current_node->left;
    if(other_index!=UNDEFINED_INDEX) {
        match_star_recurse(storage->get(other_index),key,key_length,string,string_length,position,filter,to_perform,false);
    }

    // RIGHT
    other_index=current_node->right;
    if(other_index!=UNDEFINED_INDEX) {
        match_star_recurse(storage->get(other_index),key,key_length,string,string_length,position,filter,to_perform,false);
    }
}

/**************************** walk *************************************/

template<typename S,typename T,typename M,typename RW> T tst<S,T,M,RW>::walk(filter<S,T>* filter,action<S,T>* to_perform) const {
    S* key=(S*)tst_malloc((maximum_key_length+2)*sizeof(S));
    *key='\0';
    walk_recurse(storage->get(root),key,0,maximum_key_length+1,filter,to_perform);
    tst_free(key);
    if(to_perform) {
        return to_perform->result();
    }
    else {
        return default_value;
    }
}

template<typename S,typename T,typename M,typename RW> T tst<S,T,M,RW>::walk(filter<S,T>* filter,action<S,T>* to_perform,const S* string, size_t string_length) const {
    int index = root;
    int best_node = UNDEFINED_INDEX;
    tst_node<S,T>* start = find_node(&index,&best_node,string,string_length);

    if(start) {
        T data = start->data;
        if(data!=default_value) {
            if(filter) {
                data = filter->perform(string,string_length,0,data);
            }
            if(to_perform) {
                to_perform->perform(string,string_length,0,data);
            }
        }
        
        index = start->next; 
        if(index!=UNDEFINED_INDEX) {
            S* key=(S*)tst_malloc((maximum_key_length+2)*sizeof(S));
            memcpy(key,string,string_length*sizeof(S));
            walk_recurse(storage->get(index),key,string_length,maximum_key_length+1,filter,to_perform);
            tst_free(key);
        }
    }

    if(to_perform) {
        return to_perform->result();
    }
    else {
        return default_value;
    }
}

template<typename S,typename T,typename M,typename RW> void tst<S,T,M,RW>::walk_recurse(tst_node<S,T>* current_node,S* current_key,size_t current_key_length,size_t current_key_limit,filter<S,T>* filter,action<S,T>* to_perform) const {
    int other_index;

    other_index=current_node->left;
    if(other_index!=UNDEFINED_INDEX) {
        walk_recurse(storage->get(other_index),current_key,current_key_length,current_key_limit,filter,to_perform);
    }

    assert(current_key_length < current_key_limit);
    current_key[current_key_length]=current_node->c;
    ++current_key_length;

    T data = current_node->data;
    if(data!=default_value) {
        if(filter) {
            data = filter->perform(current_key,current_key_length,0,data);
        }
        if(to_perform) {
            to_perform->perform(current_key,current_key_length,0,data);
        }
    }

    other_index=current_node->next;
    if(other_index!=UNDEFINED_INDEX) {
        walk_recurse(storage->get(other_index),current_key,current_key_length,current_key_limit,filter,to_perform);
    }

    current_key_length--;

    other_index=current_node->right;
    if(other_index!=UNDEFINED_INDEX) {
        walk_recurse(storage->get(other_index),current_key,current_key_length,current_key_limit,filter,to_perform);
    }
}

/**************************** prefix_match *************************************/

template<typename S,typename T,typename M,typename RW> T tst<S,T,M,RW>::prefix_match(const S* string,size_t string_length,filter<S,T>* filter,action<S,T>* to_perform) const {
    S* current_key=(S*)tst_malloc((maximum_key_length+2)*sizeof(S));
    int current_key_length=0;

    T biggest=default_value;
    int biggest_length=0;
    int current_index=root;
    tst_node<S,T>* current_node;
    int diff;
    S c;

    while(string_length>0) {
        c = *string;
        ++string;
        --string_length;

        assert(current_key_length<=maximum_key_length);
        current_key[current_key_length]=c;
        ++current_key_length;

        while(current_index!=UNDEFINED_INDEX) {
            current_node=storage->get(current_index);
            diff=c-current_node->c;
            if(diff==0) {
                if(current_node->data!=default_value) {
                    biggest=current_node->data;
                    biggest_length=current_key_length;
                    if(filter) {
                        biggest=filter->perform(current_key,biggest_length,0,biggest);
                    }
                }
                if(*string) {
                    current_index=current_node->next;
                    break;
                }
                else {
                    if(biggest!=default_value && to_perform) {
                        to_perform->perform(current_key,biggest_length,0,biggest);
                    }
                    current_index=current_node->next;
                    if(current_index!=UNDEFINED_INDEX) {
                        walk_recurse(storage->get(current_index),current_key,current_key_length,maximum_key_length+2,filter,to_perform);
                    }
                    tst_free(current_key);
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
        to_perform->perform(current_key,biggest_length,0,biggest);
    }

    tst_free(current_key);
    return to_perform->result();
}

/**************************** scan *************************************/

#ifdef SCANNER
template<typename S,typename T,typename M,typename RW> T tst<S,T,M,RW>::scan(const S* string,size_t string_length,action<S,T>* to_perform) {
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
    tst_node<S,T> *n_current;
    // Boucle principale
    while(1) {
        n_current = storage->get(ni_current);

        // On avance dans l'arbre d'un cran
        if(si_current<string_length) {
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
                if(si_current<string_length) {
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
                    to_perform->perform(string+si_non_match_start,non_match_length,-non_match_length,default_value);
                }

                // On envoie maintenant le match
                // On connait sa longueur grâce à la position dans l'arbre
                // TODO: voir si on ne pourrait pas de passer de ça
                tst_node<S,T> *match_node=storage->get(ni_best_match);
                int match_length = match_node->position+1;
                // On envoie le match
                to_perform->perform(string+si_match_start,match_length,match_length,match_node->data);
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
                if(si_current<string_length) {
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
                if(si_current<string_length) {
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
    string_length = si_current - si_non_match_start;
    if(string_length>0) {
        // s'il y avait un non-match en cours
        // on l'envoie
        to_perform->perform(string+si_non_match_start,string_length,-static_cast<int>(string_length),default_value);
    }

    return to_perform->result();
}

template<typename S,typename T,typename M,typename RW> void tst<S,T,M,RW>::compute_backtrack(tst_node<S,T> *current_node,const S* string, int si_match_start, int si_match_end) {
    if(current_node->backtrack==UNDEFINED_INDEX) {
        while(si_match_start<si_match_end) {
            current_node->backtrack=root;
            current_node->backtrack_match_index=UNDEFINED_INDEX;
            find_node(&(current_node->backtrack),&(current_node->backtrack_match_index),string+si_match_start,si_match_end-si_match_start);
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

template<typename S> inline int is_in(S c,const S* stop_chars,size_t stop_chars_length) {
    for(size_t i=0;i<stop_chars_length;++i,++stop_chars) {
        if(c==*stop_chars) {
            return 1;
        }
    }
    return 0;
}

template<typename S,typename T,typename M,typename RW> T tst<S,T,M,RW>::scan_with_stop_chars(const S* string,size_t string_length,const S* stop_chars,size_t stop_chars_length,action<S,T>* to_perform) const {
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
    tst_node<S,T> *n_current;
    // Boucle principale

    while(1) {
        n_current=storage->get(ni_current);

        // On avance dans l'arbre d'un cran
        if(si_current<string_length) {
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
                    if(si_current==0 || is_in(string[si_current-1],stop_chars,stop_chars_length)) {
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

                    if(n_current->data!=default_value && (si_current==(string_length-1) || is_in(string[si_current+1],stop_chars,stop_chars_length))) {
                        // on a une donnée dans le noeud courant
                        // et on est en fin de chaîne ou le caractère précédent est un stop_char
                        ni_best_match = ni_current;
                    }

                    ++si_current;
                    if(si_current<string_length) {
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
                    to_perform->perform(string+si_non_match_start,non_match_length,-non_match_length,default_value);
                }

                // On envoie maintenant le match
                // On connait sa longueur grâce à la position dans l'arbre
                // TODO: voir si on ne pourrait pas de passer de ça
                tst_node<S,T> *match_node=storage->get(ni_best_match);
                int match_length = match_node->position+1;
                // On envoie le match
                to_perform->perform(string+si_match_start,match_length,match_length,match_node->data);
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
                if(si_current<string_length) {
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
    string_length = si_current - si_non_match_start;
    if(string_length>0) {
        // s'il y avait un non-match en cours
        // on l'envoie
        to_perform->perform(string+si_non_match_start,string_length,-static_cast<int>(string_length),default_value);
    }

    return to_perform->result();
}
#endif

/**************************** file I/O *************************************/

template<typename S,typename T,typename M,typename RW> void tst<S,T,M,RW>::read(std::istream& file) {
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

    RW reader;
    file.read((char*)(&maximum_key_length),sizeof(int));
    default_value = reader.read(file);

    // On efface le stockage
    storage->erase();

    if(file.get()) {
        root = read_node(file,&reader,0);
    }
    else {
        node_info<S,T> root_info;
        storage->new_node(&root_info);
        root = root_info.index;
    }
}

template<typename S,typename T,typename M,typename RW> int tst<S,T,M,RW>::read_node(std::istream& file,RW* reader,int depth) {
    char bitmask = file.get();

    node_info<S,T> node_info;
    storage->new_node(&node_info);
    
    file.read((char*)(&(node_info.node->c)),sizeof(S));

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

template<typename S,typename T,typename M,typename RW> void tst<S,T,M,RW>::write(std::ostream& file) const {
    // We save the version number
    size_t version_length = strlen(TST_VERSION);
    file.write((char*)(&version_length),sizeof(size_t));
    file.write(TST_VERSION,version_length);
    file.write(const_cast<char*>(reinterpret_cast<const char*>(&maximum_key_length)),sizeof(int));

    RW writer;
    writer.write(file,default_value);

    if(root!=UNDEFINED_INDEX) {
        file.put(1);
        write_node(file,&writer,root);
    }
    else {
        file.put(0);
    }
}

template<typename S,typename T,typename M,typename RW> void tst<S,T,M,RW>::write_node(std::ostream& file,RW* writer,int index) const {
    tst_node<S,T>* node = storage->get(index);

    char bitmask=0;
    if(node->next!=UNDEFINED_INDEX)  bitmask |= 1;
    if(node->left!=UNDEFINED_INDEX)  bitmask |= 2;
    if(node->right!=UNDEFINED_INDEX) bitmask |= 4;
    if(node->data!=default_value)    bitmask |=16;
    file.put(bitmask);

    file.write((char*)(&(node->c)),sizeof(S));

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
