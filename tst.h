#ifndef __TST__H_INCLUDED__
#define __TST__H_INCLUDED__

struct tst_node {
    char c;
    int next;
    int right;
    int left;
    int height;
    int balance;
    void* data;
};
typedef struct tst_node tst_node;

struct tst {
    struct tst_node *array;
    int root,next,size;
};
typedef struct tst tst;

struct tst* tst_create();
void tst_free(tst* _tst);
int tst_create_node(tst* _tst,tst_node** current,int current_node);
void tst_adjust_size(tst* _tst);
int tst_build_node(tst* _tst,tst_node** current_node,int* current_index,char* current_char);
int tst_find_node(tst* _tst,int current_node,char* current_char);

/****** PLUS BESOIN DE CES DEUX FONCTIONS PUISQUE L'ARBRE EST TOUJOURS BALANCE
void tst_balance(tst* _tst,int* flag);
void tst_balance_recursive(tst_node* array,tst_node** current_node,int* current_index,int* flag);
**************************************************************/
void tst_balance_node(tst_node* array,tst_node** current_node,int* current_index);
void tst_ll(tst_node* array,tst_node** current_node,int* current_index);
void tst_rr(tst_node* array,tst_node** current_node,int* current_index);
void tst_lr(tst_node* array,tst_node** current_node,int* current_index);
void tst_rl(tst_node* array,tst_node** current_node,int* current_index);
void tst_compute_height_and_balance(tst_node* array,tst_node* current_node);

void tst_debug_node(tst_node* array,tst_node* current_node);

#endif
