#ifndef __PYTHONREFERENCE__
#define __PYTHONREFERENCE__
class PythonReference {
public:
    inline explicit PythonReference();
    inline explicit PythonReference(PyObject *object, int borrow=1);
    inline PythonReference(const PythonReference& that);

    inline PythonReference& operator= (const PythonReference& that);
    inline int operator==(const PythonReference& that);
    inline int operator!=(const PythonReference& that);

    inline PyObject* get();
    inline PyObject* lend();
    inline ~PythonReference();

private:
    PyObject* ref;
};

PythonReference::PythonReference() : ref(Py_None) {
    Py_INCREF(ref);
}

PythonReference::PythonReference(PyObject *object, int borrow) : ref(object) {
    if(ref==NULL) {
        throw TSTException("Cannot reference NULL");
    }
    if(borrow) {
        Py_INCREF(ref);
    }
}

PythonReference::PythonReference(const PythonReference& that) : ref(that.ref) {
    Py_INCREF(ref);
}

PythonReference& PythonReference::operator= (const PythonReference& that) {
    PyObject* old = ref;
    
    if((this->ref = that.ref) != old) {
        Py_INCREF(ref);
        Py_DECREF(old);
    }
    
    return *this;
}

int PythonReference::operator==(const PythonReference& that) {
    return (ref==that.ref);
}

int PythonReference::operator!=(const PythonReference& that) {
    return (ref!=that.ref);
}

PyObject* PythonReference::get() {
    return ref;
}

PyObject* PythonReference::lend() {
    Py_INCREF(ref);
    return ref;
}

PythonReference::~PythonReference() {
    Py_DECREF(ref);
}
#endif