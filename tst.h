#ifndef __TST__
#define __TST__

struct tst_node {
    char c;
    int next;
    int higher;
    int lower;
    void* data;
};
typedef struct tst_node tst_node;

struct tst {
    tst_node *array;
    int root,next,size;
};
typedef struct tst tst;

tst* tst_create();
void tst_free(tst* _tst);
int tst_create_node(tst* _tst);
void tst_adjust_size(tst* _tst);
int tst_find_node(tst* _tst,int current_node,char* current_char);

#endif
