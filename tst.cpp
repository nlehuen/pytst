#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "debug.h"
#include "tst.h"

tst::tst(int initial_size) {
    array=(tst_node*)malloc(initial_size*sizeof(tst_node));
    next=0;
    root=create_node(&array,0);
    size=initial_size;
}

tst::~tst() {
    free(array);
}

void tst::adjust() {
    if(next<size) {
        size=next;
        array=(tst_node*)realloc(array,size*sizeof(tst_node));
    }
}

TST_NODE_TYPE tst::get(char* string) {
    int current_index=root;
    tst_node* current_node=find_node(&current_index,string);
    return current_node->data;
}

TST_NODE_TYPE tst::put(char* string,TST_NODE_TYPE data) {
    tst_node* current_node=array+root;
    int node_index=build_node(&current_node,&root,string);
    TST_NODE_TYPE result;
    current_node=array+node_index;
    result = current_node->data;
    current_node->data=data;
    return result;
}

int tst::create_node(tst_node** current_node,int current_index) {
    int id;
    tst_node* new_node;

    if(next==size) {
        size+=(size>>1);
        LOG1("===> Resize to %i\n",size);
        array=(tst_node*)realloc(array,size*sizeof(tst_node));
        *current_node = array+current_index;
    }

    id=next++;
    new_node=array+id;
    new_node->c=0;
    new_node->next=-1;
    new_node->right=-1;
    new_node->left=-1;
    new_node->height=0;

    return id;
}

int tst::build_node(tst_node** current_node,int* current_index,char* current_char) {
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
        if(*current_char) {
            next_index = (*current_node)->next;
            if(next_index<0) {
                /* attention cela doit FORCEMENT se faire en deux ligne
                   car current_node peut être modifié par tst_create_node. */
                next_index=create_node(current_node,*current_index);
                (*current_node)->next=next_index;
            }
            *current_node = array + next_index;
            result=build_node(current_node,&next_index,current_char);
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
        result=build_node(current_node,&next_index,current_char);
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
        result=build_node(current_node,&next_index,current_char);
        *current_node = array+*current_index;
        (*current_node)->left=next_index;
        balance_node(current_node,current_index);
        return result;
    }
}

tst_node* tst::find_node(int* current_index,char* current_char) {
    tst_node* _array=array;
    tst_node* current_node;
    int diff;

    while(*current_index>=0) {
        current_node=_array+*current_index;

        if(current_node->c==0) {
            *current_index=-1;
            return 0;
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

    return 0;
}

void tst::balance_node(tst_node** current_node,int* current_index) {
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

void tst::ll(tst_node** current_node,int* current_index) {
    int left_index=(*current_node)->left;
    tst_node* left_node=array+left_index;
    int left_right_index=left_node->right;
    (*current_node)->left=left_right_index;
    compute_height_and_balance(*current_node);
    left_node->right=*current_index;
    compute_height_and_balance(left_node);
    *current_index=left_index;
    *current_node=array+left_index;
}

void tst::rr(tst_node** current_node,int* current_index) {
    int right_index=(*current_node)->right;
    tst_node* right_node=array+right_index;
    int right_left_index=right_node->left;
    (*current_node)->right=right_left_index;
    compute_height_and_balance(*current_node);
    right_node->left=*current_index;
    compute_height_and_balance(right_node);
    *current_index=right_index;
    *current_node=array+right_index;
}

void tst::lr(tst_node** current_node,int* current_index) {
    int* left_index=&((*current_node)->left);
    tst_node* left_node=array+*left_index;
    rr(&left_node,left_index);
    ll(current_node,current_index);
}

void tst::rl(tst_node** current_node,int* current_index) {
    int* right_index=&((*current_node)->right);
    tst_node* right_node=array+*right_index;
    ll(&right_node,right_index);
    rr(current_node,current_index);
}

int tst::compute_height_and_balance(tst_node* current_node) {
    int left = current_node->left;
    int right = current_node->right;
    int left_height,right_height,result;
    tst_node* left_node;
    tst_node* right_node;
    
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

void tst::debug() {
    debug(array+root);
}

size_t tst::bytes_allocated() {
    return sizeof(tst)+size*sizeof(tst_node);
}

void tst::debug(tst_node* current_node) {
    int index=current_node->left;
    printf("%c",current_node->c);
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
