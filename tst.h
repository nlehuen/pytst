#ifndef __TST__H_INCLUDED__
#define __TST__H_INCLUDED__

#include "Python.h"

struct tst_node {
    char c;
    int next;
    int right;
    int left;
    int height;
    PyObject* data;
};
typedef struct tst_node tst_node;


class tst {
    public:
        tst(int initial_size);
        ~tst();
        
        void adjust();
        PyObject* get(char* string);
        PyObject* put(char* string,PyObject* data);
        void debug();
        size_t bytes_allocated();

    protected:
        int create_node(tst_node** current_node,int current_index);
        int build_node(tst_node** current_node,int* current_index,char* current_char);
        tst_node* find_node(int* current_index,char* current_char);
    
    private:
        tst_node *array;
        int root,next,size;
        void balance_node(tst_node** current_node,int* current_index);
        void ll(tst_node** current_node,int* current_index);
        void rr(tst_node** current_node,int* current_index);
        void lr(tst_node** current_node,int* current_index);
        void rl(tst_node** current_node,int* current_index);
        int compute_height_and_balance(tst_node* current_node);
        void debug(tst_node* current_node);
};

#endif
