#include "tst.h"

tst* tst_create(int initial_size) {
    tst* _tst=(tst*)malloc(sizeof(tst));
    if(_tst) {
        _tst->array=(tst_node*)malloc(initial_size*sizeof(tst_node));
        _tst->root=-1;
        _tst->next=0;
        _tst->size=initial_size;
    }
    _tst->root=tst_create_node(_tst);
    return _tst;
}

int tst_create_node(tst* _tst) {
    if(_tst->next==_tst->size) {
        int old_size = _tst->size;
        tst_node* old_array = _tst->array;

        _tst->size*=3;
        _tst->size>>=1;

        printf("Resize : %i --> %i\n",old_size,_tst->size);

        _tst->array = (tst_node*)malloc(_tst->size*sizeof(tst_node));
        memcpy(_tst->array,old_array,old_size*sizeof(tst_node));
        free(old_array);
    }
    int id=_tst->next++;
    tst_node* new_node=_tst->array+id;
    new_node->c=0;
    new_node->next=-1;
    new_node->higher=-1;
    new_node->lower=-1;
    return id;
}

void tst_adjust_size(tst* _tst) {
    if(_tst->next<_tst->size) {
        tst_node* old_array = _tst->array;

        printf("Resize : %i --> %i\n",_tst->size,_tst->next);

        _tst->size=_tst->next;
        _tst->array = (tst_node*)malloc(_tst->size*sizeof(tst_node));
        memcpy(_tst->array,old_array,_tst->size*sizeof(tst_node));
        free(old_array);
    }
}

int tst_find_node(tst* _tst,int current_node,char* current_char) {
    
    while(1) {
        tst_node* current=_tst->array+current_node;
        
        int diff;
        if(current->c==0) {
            printf("%c !!!\n",*current_char);
            current->c=*current_char;
            diff=0;
        }
        else {
            diff=(*current_char)-current->c;
        }

        if(diff==0) {
            printf("%c = %c\n",*current_char,current->c);
            current_char++;
            if(*current_char) {
                if(current->next<0) {
                    current->next=tst_create_node(_tst);
                }
                current_node=current->next;
            }
            else {
                return current_node;
            }
        }
        else if(diff>0) {
            printf("%c > %c\n",*current_char,current->c);
            if(current->higher<0) {
                current->higher=tst_create_node(_tst);
            }
            current_node=current->higher;
        }
        else {
            printf("%c < %c\n",*current_char,current->c);
            if(current->lower<0) {
                current->lower=tst_create_node(_tst);
            }
            current_node=current->lower;
        }
    }
}

void tst_free(tst* _tst) {
    free(_tst);
}
