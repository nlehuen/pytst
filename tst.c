#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "debug.h"
#include "tst.h"

tst* tst_create(int initial_size) {
    tst* _tst=(tst*)malloc(sizeof(tst));
    if(_tst) {
        _tst->array=(tst_node*)malloc(initial_size*sizeof(tst_node));
        _tst->root=-1;
        _tst->next=0;
        _tst->size=initial_size;
    }
    _tst->root=tst_create_node(_tst,&(_tst->array),0);
    return _tst;
}

int tst_create_node(tst* _tst,tst_node** current_node,int current_index) {
    int id;
    tst_node* new_node;

    if(_tst->next==_tst->size) {
        _tst->size+=(_tst->size>>1);
        LOG1("===> Resize to %i\n",_tst->size);
        _tst->array=realloc(_tst->array,_tst->size*sizeof(tst_node));
        *current_node = _tst->array+current_index;
    }

    id=_tst->next++;
    new_node=_tst->array+id;
    new_node->c=0;
    new_node->next=-1;
    new_node->right=-1;
    new_node->left=-1;
    new_node->height=0;

    return id;
}

void tst_adjust_size(tst* _tst) {
    if(_tst->next<_tst->size) {
        _tst->size=_tst->next;
        _tst->array=realloc(_tst->array,_tst->size*sizeof(tst_node));
    }
}

int tst_build_node(tst* _tst,tst_node** current_node,int* current_index,char* current_char) {
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
                next_index=tst_create_node(_tst,current_node,*current_index);
                (*current_node)->next=next_index;
            }
            *current_node = _tst->array + next_index;
            result=tst_build_node(_tst,current_node,&next_index,current_char);
            *current_node = _tst->array+*current_index;
            (*current_node)->next=next_index;
            tst_balance_node(_tst->array,current_node,current_index);
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
            next_index=tst_create_node(_tst,current_node,*current_index);
            (*current_node)->right=next_index;
        }
        *current_node = _tst->array + next_index;
        result=tst_build_node(_tst,current_node,&next_index,current_char);
        *current_node = _tst->array+*current_index;
        (*current_node)->right=next_index;
        tst_balance_node(_tst->array,current_node,current_index);
        return result;
    }
    else {
        LOG2("%c < %c\n",*current_char,(*current_node)->c);
        next_index = (*current_node)->left;
        if(next_index<0) {
            next_index=tst_create_node(_tst,current_node,*current_index);
            (*current_node)->left=next_index;
        }
        *current_node = _tst->array + next_index;
        result=tst_build_node(_tst,current_node,&next_index,current_char);
        *current_node = _tst->array+*current_index;
        (*current_node)->left=next_index;
        tst_balance_node(_tst->array,current_node,current_index);
        return result;
    }
}

tst_node* tst_find_node(tst* _tst,int* current_index,char* current_char) {
    tst_node* array=_tst->array;
    tst_node* current_node;
    int diff;

    while(*current_index>=0) {
        current_node=array+*current_index;

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

TST_NODE_TYPE tst_get(tst* _tst,char* string) {
    int current_index=_tst->root;
    tst_node* current_node=tst_find_node(_tst,&current_index,string);
    return current_node->data;
}

TST_NODE_TYPE tst_put(tst* _tst,char* string,TST_NODE_TYPE data) {
    tst_node* current_node=_tst->array+_tst->root;
    int node_index=tst_build_node(_tst,&current_node,&(_tst->root),string);
    TST_NODE_TYPE result;
    current_node=_tst->array+node_index;
    result = current_node->data;
    current_node->data=data;
    return result;
}

void tst_balance_node(tst_node* array,tst_node** current_node,int* current_index) {
    int current_balance;
    current_balance=tst_compute_height_and_balance(array,*current_node);
    if(current_balance>1) {
        current_balance=tst_compute_height_and_balance(array,array+(*current_node)->right);
        if(current_balance>0) {
            tst_rr(array,current_node,current_index);
        }
        else {
            tst_rl(array,current_node,current_index);
        }
    }
    else if(current_balance<-1) {
       current_balance=tst_compute_height_and_balance(array,array+(*current_node)->left);
       if(current_balance<0) {
            tst_ll(array,current_node,current_index);
        }
        else {
            tst_lr(array,current_node,current_index);
        }
    }
}

void tst_ll(tst_node* array,tst_node** current_node,int* current_index) {
    int left_index=(*current_node)->left;
    tst_node* left_node=array+left_index;
    int left_right_index=left_node->right;
    (*current_node)->left=left_right_index;
    tst_compute_height_and_balance(array,*current_node);
    left_node->right=*current_index;
    tst_compute_height_and_balance(array,left_node);
    *current_index=left_index;
    *current_node=array+left_index;
}

void tst_rr(tst_node* array,tst_node** current_node,int* current_index) {
    int right_index=(*current_node)->right;
    tst_node* right_node=array+right_index;
    int right_left_index=right_node->left;
    (*current_node)->right=right_left_index;
    tst_compute_height_and_balance(array,*current_node);
    right_node->left=*current_index;
    tst_compute_height_and_balance(array,right_node);
    *current_index=right_index;
    *current_node=array+right_index;
}

void tst_lr(tst_node* array,tst_node** current_node,int* current_index) {
    int* left_index=&((*current_node)->left);
    tst_node* left_node=array+*left_index;
    tst_rr(array,&left_node,left_index);
    tst_ll(array,current_node,current_index);
}

void tst_rl(tst_node* array,tst_node** current_node,int* current_index) {
    int* right_index=&((*current_node)->right);
    tst_node* right_node=array+*right_index;
    tst_ll(array,&right_node,right_index);
    tst_rr(array,current_node,current_index);
}

int tst_compute_height_and_balance(tst_node* array,tst_node* current_node) {
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

void tst_debug_node(tst_node* array,tst_node* current_node) {
    int index=current_node->left;
    printf("%c",current_node->c);
    if(index>=0) {
        tst_debug_node(array,array+index);
    }
    else {
        printf("-");
    }
    index=current_node->next;
    if(index>=0) {
        tst_debug_node(array,array+index);
    }
    else {
        printf("-");
    }
    index=current_node->right;
    if(index>=0) {
        tst_debug_node(array,array+index);
    }
    else {
        printf("-");
    }
}


void tst_free(tst* _tst) {
    free(_tst);
}
