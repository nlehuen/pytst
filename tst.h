#ifndef __TST__H_INCLUDED__
#define __TST__H_INCLUDED__

#ifndef TST_NODE_TYPE
#define TST_NODE_TYPE char*
#endif

struct tst_node {
    char c;
    int next;
    int right;
    int left;
    int height;
    TST_NODE_TYPE data;
};
typedef struct tst_node tst_node;

struct tst {
    tst_node *array;
    int root,next,size;
};
typedef struct tst tst;

/**
 * Interface publique
 **/
struct tst* tst_create();
TST_NODE_TYPE tst_get(tst* _tst,char* string);
TST_NODE_TYPE tst_put(tst* _tst,char* string,TST_NODE_TYPE data);
void tst_free(tst* _tst);

/**
 * Interface privée
 **/
int tst_create_node(tst* _tst,tst_node** current,int current_node);
void tst_adjust_size(tst* _tst);

tst_node* tst_find_node(tst* _tst,int* current_index,char* current_char);
int tst_build_node(tst* _tst,tst_node** current_node,int* current_index,char* current_char);

void tst_balance_node(tst_node* array,tst_node** current_node,int* current_index);
void tst_ll(tst_node* array,tst_node** current_node,int* current_index);
void tst_rr(tst_node* array,tst_node** current_node,int* current_index);
void tst_lr(tst_node* array,tst_node** current_node,int* current_index);
void tst_rl(tst_node* array,tst_node** current_node,int* current_index);
int tst_compute_height_and_balance(tst_node* array,tst_node* current_node);

void tst_debug_node(tst_node* array,tst_node* current_node);

#endif
