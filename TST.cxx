#include "tst.h"

#include "Python.h"
// typedef char PyObject;

class TST : public tst<PyObject*> {
    public:
        TST(int initial_size,PyObject* default_value);
        PyObject* get(char* string);
        // surcharge nécessaire car la fonction n'est pas virtuelle
        PyObject* __getitem__(char* string);
        PyObject* put(char* string,PyObject* data);
        // surcharge nécessaire car la fonction n'est pas virtuelle
        PyObject* __setitem__(char* string,PyObject* data);
        
    protected:
        int create_node(tst_node<PyObject*>** current_node,int current_index);
};

TST::TST(int initial_size,PyObject* default_value) : tst<PyObject*>(initial_size,default_value) {
}

PyObject* TST::get(char* string) {
    PyObject* result=tst<PyObject*>::get(string);
    Py_INCREF(result);
    return result;
}

PyObject* TST::__getitem__(char* string) {
    return get(string);
}

PyObject* TST::put(char* string,PyObject* data) {
    Py_INCREF(data);
    return tst<PyObject*>::put(string,data);
}

PyObject* TST::__setitem__(char* string,PyObject* data) {
    return put(string,data);
}

int TST::create_node(tst_node<PyObject*>** current_node,int current_index) {
    int result=tst<PyObject*>::create_node(current_node,current_index);
    Py_INCREF((array+result)->data);
    return result;
}
