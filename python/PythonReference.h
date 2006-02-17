#ifndef __PYTHONREFERENCE_H__
#define __PYTHONREFERENCE_H__

#include "Python.h"

class PythonReference {
public:
    explicit PythonReference() : ref(Py_None) {
        Py_INCREF(ref);
    }
    
    explicit PythonReference(PyObject *object, int borrow=1) : ref(object) {
        if(ref==0) {
            throw TSTException("Cannot reference NULL");
        }
        if(borrow) {
            Py_INCREF(ref);
        }
    }
    
    PythonReference(const PythonReference& that) : ref(that.ref) {
        Py_INCREF(ref);
    }
    
    PythonReference& operator= (const PythonReference& that) {
        PyObject* old = ref;
        
        if((this->ref = that.ref) != old) {
            Py_INCREF(ref);
            Py_DECREF(old);
        }
        
        return *this;
    }
    
    ~PythonReference() {
        Py_DECREF(ref);
    }

    int operator==(const PythonReference& that) {
        return (ref==that.ref);
    }
    
    int operator!=(const PythonReference& that) {
        return (ref!=that.ref);
    }

    PythonReference getattr(char* name) {
        return PythonReference(PyObject_GetAttrString(get(),name));
    }
    
    PyObject* get() {
        return ref;
    }
    
    PyObject* lend() {
        Py_INCREF(ref);
        return ref;
    }

private:
    PyObject* ref;
};
#endif
