#ifndef __FUNDAMENTALS__H_INCLUDED__
#define __FUNDAMENTALS__H_INCLUDED__

const int UNDEFINED_INDEX=-1;

class TSTException {
public:
    TSTException(char* _message) {
        message=_message;
    }

    char* message;
};

template<class S,class T> class tst_node {
public:
    tst_node() :
        c(0)
        ,data()
        ,next(UNDEFINED_INDEX)
        ,right(UNDEFINED_INDEX)
        ,left(UNDEFINED_INDEX)
#ifdef SCANNER
        ,position(UNDEFINED_INDEX)
        ,backtrack(UNDEFINED_INDEX)
        ,backtrack_match_index(UNDEFINED_INDEX)
#endif
    {
    }

    S c;
    T data;
    int next;
    int right;
    int left;
#ifdef SCANNER
    int position;
    int backtrack;
    int backtrack_match_index;
#endif

    T store(T value) {
        T old = data;
        data = value;
        return old;
    }
};

template<class S,class T> class node_info {
public:
    int index;
    tst_node<S,T>* node;

    int height;
    int balance;
    int right_balance;
    int left_balance;
    int balance_performed;

    node_info() :
        index(UNDEFINED_INDEX)
        ,node(NULL)
        ,height(0)
        ,balance(0)
        ,right_balance(0)
        ,left_balance(0)
        ,balance_performed(0)
    {
    }
};

template<class S,class T> class action {
public:
    action() {}
    virtual ~action() {}
    virtual void perform(S* string,int string_length,int remaining_distance,T data)=0;
    virtual T result()=0;
};

template<class S,class T> class filter {
public:
    filter() {}
    virtual ~filter() {}
    virtual T perform(S* string,int string_length,int remaining_distance,T data)=0;
};

template<class T> class null_reader_writer {
    public:
        void write(FILE* file, T value) {
        }
        
        T read(FILE* file) {
            return T();
        }
};

#endif