/* 
 # $Id: tst.h 1566 2006-01-03 14:23:03Z nlehuen $
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
#ifndef __ITERATORS__H_INCLUDED__
#define __ITERATORS__H_INCLUDED__

#include <stack>

enum state_enum {
    state_left, state_current, state_next, state_right, state_end    
};

template <typename S> class state_type {
    public:
        state_type<S>(std::basic_string<S> k,state_enum s,int n,int d) : key(k), state(s), node(n), distance(d) {
        }
    
        std::basic_string<S> key;
        state_enum state;
        int node;
        int distance;               
};

template< typename S,typename T,typename M,typename RW > class lexical_iterator {
    public:
        typedef std::pair< std::basic_string<S>, T* > valuetype;

        lexical_iterator(const tst<S,T,M,RW> *t,std::basic_string<S> key,int root) : tree(t), stack() {
            stack.push(state_type<S>(key,state_left,root,0));
        }

        valuetype next() {
            while(!stack.empty()) {
                state_type<S>& state = stack.top();

                if(state.node==UNDEFINED_INDEX) {
                    break;
                }

                tst_node<S,T>* node = tree->storage->get(state.node);
            
                switch(state.state) {
                    case state_left: {
                        state.state = state_current;
                        if(node->left!=UNDEFINED_INDEX) {
                            stack.push(state_type<S>(state.key,state_left,node->left,0));
                            break;
                        }
                    }
                    
                    case state_current: {
                        state.state = state_next;
                        if(node->data != tree->default_value) {
                            std::basic_string<S> new_key(state.key);
                            new_key += node->c;
                            return valuetype(
                                new_key,
                                &(node->data)
                            );
                        }
                    }
                    
                    case state_next: {
                        state.state = state_right;
                        if(node->next!=UNDEFINED_INDEX) {
                            state_type<S> new_state = state_type<S>(
                                state.key,
                                state_left,
                                node->next,
                                0
                            );
                            new_state.key += node->c;
                            stack.push(new_state);
                            break;
                        }
                    }
                    
                    case state_right: {
                        state.state = state_end;
                        if(node->right!=UNDEFINED_INDEX) {
                            stack.push(state_type<S>(state.key,state_left,node->right,0));
                            break;
                        }
                    }
                    
                    case state_end: {
                        stack.pop();
                        break;
                    }
                }
            }
            return valuetype("",NULL);
        }
                
    private:
        const tst<S,T,M,RW> *tree;
        std::stack< state_type<S> > stack;
};

template< typename S,typename T,typename M,typename RW > class distance_iterator {
    public:
        typedef std::pair< std::basic_string<S>, T* > valuetype;

        distance_iterator(const tst<S,T,M,RW> *t,std::basic_string<S> key,int root,int distance) : tree(t), stack() {
            stack.push(state_type<S>(key,state_left,root,distance));
        }

        valuetype next() {
            while(!stack.empty()) {
                state_type<S>& state = stack.top();

                if(state.node==UNDEFINED_INDEX) {
                    break;
                }

                tst_node<S,T>* node = tree->storage->get(state.node);
            
                switch(state.state) {
                    case state_left: {
                        state.state = state_current;
                        if(node->left!=UNDEFINED_INDEX) {
                            stack.push(state_type<S>(state.key,state_left,node->left,state.distance));
                            break;
                        }
                    }
                    
                    case state_current: {
                        state.state = state_next;
                        if(node->data != tree->default_value) {
                            std::basic_string<S> new_key(state.key);
                            new_key += node->c;
                            return valuetype(
                                new_key,
                                &(node->data)
                            );
                        }
                    }
                    
                    case state_next: {
                        state.state = state_right;
                        if(node->next!=UNDEFINED_INDEX) {
                            state_type<S> new_state = state_type<S>(
                                state.key,
                                state_left,
                                node->next,
                                state.distance
                            );
                            new_state.key += node->c;
                            stack.push(new_state);
                            break;
                        }
                    }
                    
                    case state_right: {
                        state.state = state_end;
                        if(node->right!=UNDEFINED_INDEX) {
                            stack.push(state_type<S>(state.key,state_left,node->right,0));
                            break;
                        }
                    }
                    
                    case state_end: {
                        stack.pop();
                        break;
                    }
                }
            }
            return valuetype("",NULL);
        }
                
    private:
        const tst<S,T,M,RW> *tree;
        std::stack< state_type<S> > stack;
};

#endif
