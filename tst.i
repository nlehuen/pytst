%module tst

%{
#include "tst.h"
%}

class tst {
    public:
        tst(int initial_size);
        ~tst();
        
        void adjust();
        TST_NODE_TYPE get(char* string);
        TST_NODE_TYPE put(char* string,TST_NODE_TYPE data);
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