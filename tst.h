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
    struct tst_node *array;
    int root,next,size;
};
typedef struct tst tst;

struct tst* tst_create();
void tst_free(struct tst* _tst);
int tst_create_node(struct tst* _tst,tst_node** current,int current_node);
void tst_adjust_size(struct tst* _tst);
int tst_find_node(struct tst* _tst,int current_node,char* current_char);

#endif
