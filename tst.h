#ifndef __TST__H_INCLUDED__
#define __TST__H_INCLUDED__

#include <stdlib.h>
#include <stdio.h>

#ifdef __PYTHON__BUILD__
    #include "Python.h"
    #define malloc PyMem_Malloc
    #define realloc PyMem_Realloc
    #define free PyMem_Free
#else
    #include <malloc.h>
    #include <memory.h>
#endif

#include "debug.h"

template<class T> class tst_node {
public:
    char c;
    int next;
    int right;
    int left;
    int height;
    T data;
};

template<class T> class action {
    public:
        action() {
            LOG0("action()\n");
        }

        virtual ~action() { LOG0("~action\n"); }

        virtual void perform(char* key,int remaining_distance,T data) {
            LOG0("default action \n");
        };
};

template<class T> class filter {
    public:
        filter() {
            LOG0("filter()\n");
        }

        virtual ~filter() { LOG0("~filter\n"); }

        virtual T perform(char* key,int remaining_distance,T data) {
            LOG0("default filter \n");
            return data;
        };
};

template<class T> class tst {
    public:
        tst(int initial_size,T default_value);
        ~tst();

        void adjust();
        void walk(filter<T>* filter,action<T>* to_perform);
        void almost(char* string,int string_length,int maximum_distance,filter<T>* filter,action<T>* to_perform);
        void common_prefix(char* string,filter<T>* filter,action<T>* to_perform);
        T get(char* string);
        T __getitem__(char* string);
        T put(char* string,T data);
        T __setitem__(char* string,T data);
        void debug();
        int get_maximum_key_length();
        size_t bytes_allocated();

    protected:
        tst_node<T>* array;
        T default_value;
        int root,next,size,maximum_key_length;

        void walk_recurse(tst_node<T>* current_node,char* current_key,int current_key_length,int current_key_limit,filter<T>* filter,action<T>* to_perform);
        void almost_recurse(tst_node<T>* current_node,char* current_key, int current_key_length, char* current_char,int current_index, int real_string_length, int string_length, int remaining_distance,filter<T>* filter,action<T>* to_perform,int current_key_limit);

        int create_node(tst_node<T>** current_node,int current_index);

        int build_node(tst_node<T>** current_node,int* current_index,char* current_char,int current_key_length);
        tst_node<T>* find_node(int* current_index,char* current_char);

        void balance_node(tst_node<T>** current_node,int* current_index);
        void ll(tst_node<T>** current_node,int* current_index);
        void rr(tst_node<T>** current_node,int* current_index);
        void lr(tst_node<T>** current_node,int* current_index);
        void rl(tst_node<T>** current_node,int* current_index);
        int compute_height_and_balance(tst_node<T>* current_node);

        void debug(tst_node<T>* current_node);
};

template<class T> tst<T>::tst(int size,T default_value) {
    this->size=size;
    this->default_value=default_value;
    array=(tst_node<T>*)malloc(size*sizeof(tst_node<T>));
    next=0;
    root=create_node(&array,0);
    maximum_key_length=0;
}

template<class T> tst<T>::~tst() {
    LOG1("tst::~tst() : Removing array of %i elements\n",size);
    free(array);
}

template<class T> void tst<T>::adjust() {
    if(next<size) {
        size=next;
        array=(tst_node<T>*)realloc(array,size*sizeof(tst_node<T>));
    }
}

template<class T> T tst<T>::get(char* string) {
    LOG1("get(%s)\n",string);

    int current_index=root;
    tst_node<T>* current_node=find_node(&current_index,string);
    if(current_node) {
        return current_node->data;
    }
    else {
        return default_value;
    }
}

template<class T> T tst<T>::__getitem__(char* string) {
    return get(string);
}

template<class T> T tst<T>::put(char* string,T data) {
    LOG2("put(%s,%i)\n",string,(int)data);

    tst_node<T>* current_node=array+root;
    int node_index=build_node(&current_node,&root,string,0);
    T result;

    current_node=array+node_index;
    result = current_node->data;
    current_node->data=data;
    return result;
}

template<class T> T tst<T>::__setitem__(char* string,T data) {
    return put(string,data);
}

template<class T> void tst<T>::almost(char* string, int string_length, int maximum_distance,filter<T>* filter,action<T>* to_perform) {
    LOG1("malloc de %i\n",string_length+maximum_distance+1);
    char* current_key=(char*)malloc((string_length+maximum_distance+1)*sizeof(char));
    *current_key='\0';
    LOG1("malloc : %x\n",(int)current_key);
    almost_recurse(array+root,current_key,0,string,0,string_length,string_length,maximum_distance,filter,to_perform,string_length+maximum_distance);
    free(current_key);
}

template<class T> void tst<T>::walk(filter<T>* filter,action<T>* to_perform) {
    char* key=(char*)malloc((maximum_key_length+2)*sizeof(char));
    *key='\0';
    walk_recurse(array+root,key,0,maximum_key_length+1,filter,to_perform);
    free(key);
}

template<class T> void tst<T>::walk_recurse(tst_node<T>* current_node,char* current_key,int current_key_length,int current_key_limit,filter<T>* filter,action<T>* to_perform) {
    int other_index;

    other_index=current_node->left;
    if(other_index>=0) {
        walk_recurse(array+other_index,current_key,current_key_length,current_key_limit,filter,to_perform);
    }

    T data = current_node->data;
    if(filter) {
        data = filter->perform(current_key,0,data);
    }
    if(data!=default_value && to_perform) {
        assert(current_key[current_key_length]=='\0');
        assert(current_key_length < current_key_limit);
        current_key[current_key_length]=current_node->c;
        current_key[current_key_length+1]='\0';
        to_perform->perform(current_key,0,data);
        current_key[current_key_length]='\0';
    }

    other_index=current_node->next;
    if(other_index>=0) {
        assert(current_key[current_key_length]=='\0');
        assert(current_key_length < current_key_limit);
        current_key[current_key_length]=current_node->c;
        current_key[current_key_length+1]='\0';
        walk_recurse(array+other_index,current_key,current_key_length+1,current_key_limit,filter,to_perform);
        current_key[current_key_length]='\0';
    }

    other_index=current_node->right;
    if(other_index>=0) {
        walk_recurse(array+other_index,current_key,current_key_length,current_key_limit,filter,to_perform);
    }
}

template<class T> void tst<T>::almost_recurse(tst_node<T>* current_node,char* current_key,int current_key_length,char* string, int current_index, int real_string_length, int string_length, int remaining_distance,filter<T>* filter, action<T>* to_perform,int current_key_limit) {
    int other_index;
    int diff,diff2;

    other_index=current_node->left;
    if (other_index>=0) {
        almost_recurse(array+other_index,current_key,current_key_length,string,current_index,real_string_length,string_length,remaining_distance,filter,to_perform,current_key_limit);
    }

    diff=0;
    if(current_index<real_string_length) {
        if((string[current_index]-current_node->c)!=0) {
            diff=1;
        }
    }
    else {
        diff=1;
    }

    T data = current_node->data;
    if(filter) {
        data = filter->perform(current_key,0,data);
    }
    if(data!=default_value && to_perform) {
        diff2=(remaining_distance-abs(current_key_length+1-string_length))-diff;
        if(diff2>=0) {
            assert(current_key[current_key_length]=='\0');
            assert(current_key_length < current_key_limit);
            current_key[current_key_length]=current_node->c;
            current_key[current_key_length+1]='\0';
            to_perform->perform(current_key,diff2,data);
            current_key[current_key_length]='\0';
        }
    }

    other_index=current_node->next;
    if (other_index>=0) {
        diff2 = remaining_distance - diff;
        if (diff2>=0) {
            assert(current_key[current_key_length]=='\0');
            assert(current_key_length < current_key_limit);
            current_key[current_key_length]=current_node->c;
            current_key[current_key_length+1]='\0';
            almost_recurse(array+other_index,current_key,current_key_length+1,string,current_index+1,real_string_length,string_length,diff2,filter,to_perform,current_key_limit);
            current_key[current_key_length]='\0';
        }
    }

    if(current_index<string_length && remaining_distance>0) {
        assert(current_key[current_key_length]=='\0');
        almost_recurse(current_node,current_key,current_key_length,string,current_index+1,real_string_length,string_length-1,remaining_distance-1,filter,to_perform,current_key_limit);
    }

    if(other_index>=0 && remaining_distance>0) {
        assert(current_key[current_key_length]=='\0');
        assert(current_key_length < current_key_limit);
        current_key[current_key_length]=current_node->c;
        current_key[current_key_length+1]='\0';
        almost_recurse(array+other_index,current_key,current_key_length+1,string,current_index,real_string_length,string_length+1,remaining_distance-1,filter,to_perform,current_key_limit);
        current_key[current_key_length]='\0';
    }

    other_index = current_node->right;
    if(other_index>=0) {
        assert(current_key[current_key_length]=='\0');
        almost_recurse(array+other_index,current_key,current_key_length,string,current_index,real_string_length,string_length,remaining_distance,filter,to_perform,current_key_limit);
    }
}

template<class T> void tst<T>::common_prefix(char* string,filter<T>* filter,action<T>* to_perform) {
    char* current_key=(char*)malloc((maximum_key_length+2)*sizeof(char));
    int current_key_length=0,current_key_limit=maximum_key_length+1;
    *current_key='\0';

    T biggest=default_value;
    int current_index=root;
    tst_node<T>* current_node;
    int diff;
    char c;

    while(c=*(string++)) {
        current_key[current_key_length]=c;
        current_key[current_key_length+1]='\0';
        current_key_length++;
        while(current_index>=0) {
            current_node=array+current_index;
            diff=c-current_node->c;
            if(diff==0) {
                if(current_node->data!=default_value) {
                    biggest=current_node->data;
                    if(filter) {
                        biggest=filter->perform(current_key,0,biggest);
                    }
                }
                if(*string) {
                    current_index=current_node->next;
                    break;
                }
                else {
                    if(biggest!=default_value && to_perform) {
                        to_perform->perform(current_key,current_key_length,biggest);
                    }
                    current_index=current_node->next;
                    if(current_index>=0) {
                        walk_recurse(array+current_index,current_key,current_key_length,current_key_limit,filter,to_perform);
                    }
                    free(current_key);
                    return;
                }
            }
            else if(diff>0) {
                current_index=current_node->right;
            }
            else {
                current_index=current_node->left;
            }
        }
        if(current_index==0) {
            break;
        }
    }

    if(biggest!=default_value && to_perform) {
        to_perform->perform(current_key,current_key_length,biggest);
    }
    free(current_key);
}

template<class T> int tst<T>::create_node(tst_node<T>** current_node,int current_index) {
    int id;
    tst_node<T>* new_node;

    if(next==size) {
        size+=(size>>1);
        LOG1("===> Resize to %i\n",size);
        array=(tst_node<T>*)realloc(array,size*sizeof(tst_node<T>));
        *current_node = array+current_index;
    }

    id=next++;
    new_node=array+id;
    new_node->c=0;
    new_node->next=-1;
    new_node->right=-1;
    new_node->left=-1;
    new_node->height=0;
    new_node->data=default_value;

    return id;
}

template<class T> int tst<T>::build_node(tst_node<T>** current_node,int* current_index,char* current_char,int current_key_length) {
    int diff,result,next_index;

    if((*current_node)->c==0) {
        LOG1("%c !!!\n",*current_char);
        (*current_node)->c=(*current_char);
        diff=0;
    }
    else {
        diff=(*current_char)-((*current_node)->c);
    }

    if(diff==0) {
        LOG2("%c = %c\n",*current_char,(*current_node)->c);
        current_char++;
        current_key_length++;
        if(*current_char) {
            if(current_key_length>maximum_key_length) {
                maximum_key_length=current_key_length;
            }
            next_index = (*current_node)->next;
            if(next_index<0) {
                /* attention cela doit FORCEMENT se faire en deux ligne
                   car current_node peut être modifié par tst_create_node. */
                next_index=create_node(current_node,*current_index);
                (*current_node)->next=next_index;
            }
            *current_node = array + next_index;
            result=build_node(current_node,&next_index,current_char,current_key_length);
            *current_node = array+*current_index;
            (*current_node)->next=next_index;
            balance_node(current_node,current_index);
            return result;
        }
        else {
            return *current_index;
        }
    }
    else if(diff>0) {
        LOG2("%c > %c\n",*current_char,(*current_node)->c);
        next_index = (*current_node)->right;
        if(next_index<0) {
            next_index=create_node(current_node,*current_index);
            (*current_node)->right=next_index;
        }
        *current_node = array + next_index;
        result=build_node(current_node,&next_index,current_char,current_key_length);
        *current_node = array+*current_index;
        (*current_node)->right=next_index;
        balance_node(current_node,current_index);
        return result;
    }
    else {
        LOG2("%c < %c\n",*current_char,(*current_node)->c);
        next_index = (*current_node)->left;
        if(next_index<0) {
            next_index=create_node(current_node,*current_index);
            (*current_node)->left=next_index;
        }
        *current_node = array + next_index;
        result=build_node(current_node,&next_index,current_char,current_key_length);
        *current_node = array+*current_index;
        (*current_node)->left=next_index;
        balance_node(current_node,current_index);
        return result;
    }
}

template<class T> tst_node<T>* tst<T>::find_node(int* current_index,char* current_char) {
    tst_node<T>* _array=array;
    tst_node<T>* current_node;
    int diff;

    while(*current_index>=0) {
        current_node=_array+*current_index;

        if(current_node->c==0) {
            *current_index=-1;
            return NULL;
        }
        else {
            diff=(*current_char)-(current_node->c);
        }

        if(diff==0) {
            LOG2("%c = %c\n",*current_char,current_node->c);
            current_char++;
            if(*current_char) {
                *current_index = current_node->next;
            }
            else {
                return current_node;
            }
        }
        else if(diff>0) {
            LOG2("%c > %c\n",*current_char,current_node->c);
            *current_index=current_node->right;
        }
        else {
            LOG2("%c < %c\n",*current_char,current_node->c);
            *current_index=current_node->left;
        }
    }

    return NULL;
}

template<class T> void tst<T>::balance_node(tst_node<T>** current_node,int* current_index) {
    int current_balance;
    current_balance=compute_height_and_balance(*current_node);
    if(current_balance>1) {
        current_balance=compute_height_and_balance(array+(*current_node)->right);
        if(current_balance>0) {
            rr(current_node,current_index);
        }
        else {
            rl(current_node,current_index);
        }
    }
    else if(current_balance<-1) {
       current_balance=compute_height_and_balance(array+(*current_node)->left);
       if(current_balance<0) {
            ll(current_node,current_index);
        }
        else {
            lr(current_node,current_index);
        }
    }
}

template<class T> void tst<T>::ll(tst_node<T>** current_node,int* current_index) {
    int left_index=(*current_node)->left;
    tst_node<T>* left_node=array+left_index;
    int left_right_index=left_node->right;
    (*current_node)->left=left_right_index;
    compute_height_and_balance(*current_node);
    left_node->right=*current_index;
    compute_height_and_balance(left_node);
    *current_index=left_index;
    *current_node=array+left_index;
}

template<class T> void tst<T>::rr(tst_node<T>** current_node,int* current_index) {
    int right_index=(*current_node)->right;
    tst_node<T>* right_node=array+right_index;
    int right_left_index=right_node->left;
    (*current_node)->right=right_left_index;
    compute_height_and_balance(*current_node);
    right_node->left=*current_index;
    compute_height_and_balance(right_node);
    *current_index=right_index;
    *current_node=array+right_index;
}

template<class T> void tst<T>::lr(tst_node<T>** current_node,int* current_index) {
    int* left_index=&((*current_node)->left);
    tst_node<T>* left_node=array+*left_index;
    rr(&left_node,left_index);
    ll(current_node,current_index);
}

template<class T> void tst<T>::rl(tst_node<T>** current_node,int* current_index) {
    int* right_index=&((*current_node)->right);
    tst_node<T>* right_node=array+*right_index;
    ll(&right_node,right_index);
    rr(current_node,current_index);
}

template<class T> int tst<T>::compute_height_and_balance(tst_node<T>* current_node) {
    int left = current_node->left;
    int right = current_node->right;
    int left_height,right_height,result;
    tst_node<T>* left_node;
    tst_node<T>* right_node;

    if(right>=0) {
        right_node=array+right;
        right_height=right_node->height;
        if(left>=0) {
            left_node=array+left;
            left_height=left_node->height;
            result=right_height-left_height;
            if(left_height>right_height) {
                right_height=left_height;
            }
            current_node->height=right_height+1;
            return result;
        }
        else {
            current_node->height=right_height+1;
            return right_height;
        }
    }
    else {
        if(left>=0) {
            left_node=array+left;
            left_height=left_node->height;
            current_node->height=left_height+1;
            return -left_height;
        }
        else {
            current_node->height=0;
            return 0;
        }
    }
}

template<class T> void tst<T>::debug() {
    debug(array+root);
}

template<class T> size_t tst<T>::bytes_allocated() {
    return sizeof(tst)+size*sizeof(tst_node<T>);
}

template<class T> int tst<T>::get_maximum_key_length() {
    return maximum_key_length;
}

template<class T> void tst<T>::debug(tst_node<T>* current_node) {
    int index=current_node->left;
    printf("%c",current_node->c);
    if(current_node->data) {
        printf("*");
    }
    else{
        printf(".");
    }
    if(index>=0) {
        debug(array+index);
    }
    else {
        printf("-");
    }
    index=current_node->next;
    if(index>=0) {
        debug(array+index);
    }
    else {
        printf("-");
    }
    index=current_node->right;
    if(index>=0) {
        debug(array+index);
    }
    else {
        printf("-");
    }
}

#endif
