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
void tst_free(struct tst* _tst);
int tst_create_node(struct tst* _tst,tst_node** current,int current_node);
void tst_adjust_size(struct tst* _tst);
int tst_find_node(struct tst* _tst,int current_node,char* current_char);
void tst_compute_height_and_balance(tst* _tst,tst_node* current_node);

void tst_balance(tst* _tst,int* flag);
void tst_balance_recursive(tst* _tst,tst_node** current_node,int* current_index,int* flag);
void tst_balance_node(tst* _tst,tst_node** current_node,int* current_index,int* flag);
void tst_ll(tst* _tst,tst_node** current_node,int* current_index);
void tst_rr(tst* _tst,tst_node** current_node,int* current_index);
void tst_lr(tst* _tst,tst_node** current_node,int* current_index);
void tst_rl(tst* _tst,tst_node** current_node,int* current_index);

void tst_debug_node(tst* _tst,tst_node* current_node);

#endif
