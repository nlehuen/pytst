#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "tst.h"

// #define NDEBUG
#include <assert.h>

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
	int id, old_size;
	tst_node* new_node;
    tst_node* old_array = _tst->array;

	assert(_tst->next<=_tst->size);

	if(_tst->next==_tst->size) {
        old_size = _tst->size;
        _tst->size+=(_tst->size>>1);

        printf("Resize : %i --> %i\n",old_size,_tst->size);

        _tst->array=(tst_node*)memcpy(
			malloc(_tst->size*sizeof(tst_node)),
			old_array,
			old_size*sizeof(tst_node));
		assert(memcmp(_tst->array,old_array,old_size*sizeof(tst_node))==0);
        free(old_array);
    }

	id=_tst->next++;
	new_node=_tst->array+id;
    new_node->c=0;
    new_node->next=-1;
    new_node->higher=-1;
    new_node->lower=-1;

	assert(_tst->next<=_tst->size);
	
	return id;
}

void tst_adjust_size(tst* _tst) {
	tst_node* old_array = _tst->array;

	assert(_tst->next<=_tst->size);
    if(_tst->next<_tst->size) {
		printf("Resize : %i --> %i\n",_tst->size,_tst->next);
		_tst->size=_tst->next;
        _tst->array=(tst_node*)memcpy(
			malloc(_tst->size*sizeof(tst_node)),
			old_array,
			_tst->size*sizeof(tst_node));
		assert(memcmp(_tst->array,old_array,_tst->size*sizeof(tst_node))==0);
        free(old_array);
    }
	assert(_tst->next<=_tst->size);
}

int tst_find_node(tst* _tst,int current_node,char* current_char) {
	tst_node* current;
    int diff;

    while(1) {
		assert(_tst->next<=_tst->size);

        current=_tst->array+current_node;
        
        if(current->c==0) {
            printf("%c !!!\n",*current_char);
            current->c=(*current_char);
            diff=0;
        }
        else {
            diff=(*current_char)-(current->c);
        }

        if(diff==0) {
			assert(current->c==*current_char);
            printf("%c = %c\n",*current_char,current->c);
            current_char++;
            if(*current_char) {
                if(current->next<0) {
                    current->next=tst_create_node(_tst);
                }
                current_node=current->next;
            }
            else {
				assert(_tst->next<=_tst->size);
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
