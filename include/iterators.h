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

#include <string>
#include <stack>

template< typename S,typename T,typename M,typename RW > class lexical_iterator {
    public:
        enum state_enum {
            state_left, state_current, state_next, state_right, state_end    
        };

        class state_type {
            public:
                state_type(std::basic_string<S> k,state_enum s,int n) : key(k), state(s), node(n) {
                }
            
                std::basic_string<S> key;
                state_enum state;
                int node;
        };

        typedef std::pair< std::basic_string<S>, T* > value_type;

        lexical_iterator(const tst<S,T,M,RW> *t,std::basic_string<S> key,int root) : tree(t), stack() {
            stack.push(state_type(key,state_left,root));
        }

        value_type next() {
            while(!stack.empty()) {
                state_type& state = stack.top();

                if(state.node==UNDEFINED_INDEX) {
                    break;
                }

                tst_node<S,T>* node = tree->storage->get(state.node);
            
                switch(state.state) {
                    case state_left: {
                        state.state = state_current;
                        if(node->left!=UNDEFINED_INDEX) {
                            stack.push(state_type(state.key,state_left,node->left));
                            break;
                        }
                    }
                    
                    case state_current: {
                        state.state = state_next;
                        if(node->data != tree->default_value) {
                            std::basic_string<S> new_key(state.key);
                            new_key += node->c;
                            return value_type(
                                new_key,
                                &(node->data)
                            );
                        }
                    }
                    
                    case state_next: {
                        state.state = state_right;
                        if(node->next!=UNDEFINED_INDEX) {
                            state_type new_state = state_type(
                                state.key,
                                state_left,
                                node->next
                            );
                            new_state.key += node->c;
                            stack.push(new_state);
                            break;
                        }
                    }
                    
                    case state_right: {
                        state.state = state_end;
                        if(node->right!=UNDEFINED_INDEX) {
                            stack.push(state_type(state.key,state_left,node->right));
                            break;
                        }
                    }
                    
                    case state_end: {
                        stack.pop();
                        break;
                    }
                }
            }
            return value_type("",NULL);
        }
                
    private:
        const tst<S,T,M,RW> *tree;
        std::stack< state_type > stack;
};

#endif
