#ifndef __PYTHONREFERENCE_H__
#define __PYTHONREFERENCE_H__

#include "Python.h"

class PythonException : public std::exception {
public:
    PythonException(const char* _message) : message(_message) {
    }

    const char* what() {
        return message;
    }

private:
    const char* message;
};


class PythonReference {
public:
    explicit PythonReference() : ref(Py_None) {
        Py_INCREF(ref);
    }
    
    explicit PythonReference(PyObject *object, int borrow=1) : ref(object) {
        if(ref==0) {
            throw PythonException("Cannot reference NULL");
        }
        if(borrow) {
            Py_INCREF(ref);
        }
    }
    
    PythonReference(const PythonReference& that) : ref(that.ref) {
        Py_INCREF(ref);
    }
    
    inline PythonReference& operator= (const PythonReference& that) {
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

    inline int operator==(const PythonReference& that) {
        return (ref==that.ref);
    }
    
    inline int operator!=(const PythonReference& that) {
        return (ref!=that.ref);
    }

    inline PythonReference getattr(char* name) {
        return PythonReference(PyObject_GetAttrString(get(),name));
    }
    
    inline PyObject* get() {
        return ref;
    }
    
    inline PyObject* lend() {
        Py_INCREF(ref);
        return ref;
    }

private:
    PyObject* ref;
};
#endif
