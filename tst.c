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
    new_node->balance=0;

    return id;
}

void tst_adjust_size(tst* _tst) {
    if(_tst->next<_tst->size) {
        _tst->size=_tst->next;
        _tst->array=realloc(_tst->array,_tst->size*sizeof(tst_node));
    }
}

int tst_find_node(tst* _tst,int current_index,char* current_char) {
    tst_node* current_node;
    int diff;

    while(1) {
        current_node=_tst->array+current_index;

        if(current_node->c==0) {
            LOG1("%c !!!\n",*current_char);
            current_node->c=(*current_char);
            diff=0;
        }
        else {
            diff=(*current_char)-(current_node->c);
        }

        if(diff==0) {
            LOG2("%c = %c\n",*current_char,current_node->c);
            current_char++;
            if(*current_char) {
                if(current_node->next<0) {
                    /* attention cela doit FORCEMENT se faire en deux ligne
                       car current_node peut être modifié par tst_create_node. */
                    current_index=tst_create_node(_tst,&current_node,current_index);
                    current_node->next=current_index;
                }
                else {
                    current_index=current_node->next;
                }
            }
            else {
                return current_index;
            }
        }
        else if(diff>0) {
            LOG2("%c > %c\n",*current_char,current_node->c);
            if(current_node->right<0) {
                current_index=tst_create_node(_tst,&current_node,current_index);
                current_node->right=current_index;
            }
            else {
                current_index=current_node->right;
            }
        }
        else {
            LOG2("%c < %c\n",*current_char,current_node->c);
            if(current_node->left<0) {
                current_index=tst_create_node(_tst,&current_node,current_index);
                current_node->left=current_index;
            }
            else {
                current_index=current_node->left;
            }
        }
    }
}

void tst_balance(tst* _tst,int* flag) {
    int* root_index=&(_tst->root);
	tst_node* array=_tst->array;
    tst_node* root_node=array+*root_index;
    tst_balance_recursive(array,&root_node,root_index,flag);
}

void tst_balance_recursive(tst_node* array,tst_node** current_node,int* current_index,int* flag) {
    int* other_index;
    tst_node* other_node;
    
    other_index=&((*current_node)->left);
    if(*other_index>=0) {
        other_node=array+*other_index;
        tst_balance_recursive(array,&other_node,other_index,flag);
    }
    other_index=&((*current_node)->right);
    if(*other_index>=0) {
        other_node=array+*other_index;
        tst_balance_recursive(array,&other_node,other_index,flag);
    }
    tst_balance_node(array,current_node,current_index,flag);
}

void tst_balance_node(tst_node* array,tst_node** current_node,int* current_index,int* flag) {
    int balance;
    tst_node* other_node;
    tst_compute_height_and_balance(array,*current_node);
    balance=(*current_node)->balance;
    if(balance>1) {
        other_node=array+(*current_node)->right;
        if(other_node->balance>0) {
            tst_rr(array,current_node,current_index);
        }
        else {
            tst_rl(array,current_node,current_index);
        }
        *flag=1;
    }
    else if(balance<-1) {
        other_node=array+(*current_node)->left;
        if(other_node->balance<0) {
            tst_ll(array,current_node,current_index);
        }
        else {
            tst_lr(array,current_node,current_index);
        }
        *flag=1;
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

void tst_compute_height_and_balance(tst_node* array,tst_node* current_node) {
    int left = current_node->left;
    int right = current_node->right;
    int left_height,right_height;
    tst_node* left_node;
    tst_node* right_node;
    
    if(right>=0) {
        right_node=array+right;
        right_height=right_node->height;
        if(left>=0) {
            left_node=array+left;
            left_height=left_node->height;
            current_node->balance=right_height-left_height;
            if(left_height>right_height) {
                right_height=left_height;
            }
            current_node->height=right_height+1;
        }
        else {
            current_node->balance=right_height;
            current_node->height=right_height+1;
        }
    }
    else {
        if(left>=0) {
            left_node=array+left;
            left_height=left_node->height;
            current_node->balance=-left_height;
            current_node->height=left_height+1;
        }
        else {
            current_node->balance=0;
            current_node->height=0;
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
