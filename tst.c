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

int tst_create_node(tst* _tst,tst_node** current,int current_node) {
    int id;
    tst_node* new_node;

    if(_tst->next==_tst->size) {
        _tst->size+=(_tst->size>>1);
        _tst->array=realloc(_tst->array,_tst->size*sizeof(tst_node));
        *current = _tst->array+current_node;
    }

    id=_tst->next++;
    new_node=_tst->array+id;
    new_node->c=0;
    new_node->next=-1;
    new_node->higher=-1;
    new_node->lower=-1;

    return id;
}

void tst_adjust_size(tst* _tst) {
    if(_tst->next<_tst->size) {
        _tst->size=_tst->next;
        _tst->array=realloc(_tst->array,_tst->size*sizeof(tst_node));
    }
}

int tst_find_node(tst* _tst,int current_node,char* current_char) {
    tst_node* current;
    int diff;

    while(1) {
        current=_tst->array+current_node;

        if(current->c==0) {
            LOG1("%c !!!\n",*current_char);
            current->c=(*current_char);
            diff=0;
        }
        else {
            diff=(*current_char)-(current->c);
        }

        if(diff==0) {
            LOG2("%c = %c\n",*current_char,current->c);
            current_char++;
            if(*current_char) {
                if(current->next<0) {
                    /* attention cela doit FORCEMENT se faire en deux ligne
                       car current peut être modifié par tst_create_node. */
                    current_node=tst_create_node(_tst,&current,current_node);
                    current->next=current_node;
                }
                else {
                    current_node=current->next;
                }
            }
            else {
                return current_node;
            }
        }
        else if(diff>0) {
            LOG2("%c > %c\n",*current_char,current->c);
            if(current->higher<0) {
                current_node=tst_create_node(_tst,&current,current_node);
                current->higher=current_node;
            }
            else {
                current_node=current->higher;
            }
        }
        else {
            LOG2("%c < %c\n",*current_char,current->c);
            if(current->lower<0) {
                current_node=tst_create_node(_tst,&current,current_node);
                current->lower=current_node;
            }
            else {
                current_node=current->lower;
            }
        }
    }
}

void tst_free(tst* _tst) {
    free(_tst);
}
