#define __PYTHON__BUILD__

#include "tst.h"

#include "Python.h"

class CallableAction : public action<PyObject*> {
    public:
        CallableAction(PyObject* _callable) {
            Py_XINCREF(_callable);
            callable=_callable;
        }

        virtual ~CallableAction() {
            Py_DECREF(callable);
        }

        virtual void perform(char* key,int remaining_distance,PyObject* data) {
            PyObject* tuple=PyTuple_New(3);
            PyTuple_SetItem(tuple,0,PyString_FromString(key));
            PyTuple_SetItem(tuple,1,PyInt_FromLong(remaining_distance));
            Py_XINCREF(data);
            PyTuple_SetItem(tuple,2,data);
            PyObject_CallObject(callable,tuple);
            Py_DECREF(tuple);
        }

    private:
        PyObject* callable;
};

class CallableFilter : public filter<PyObject*> {
    public:
        CallableFilter(PyObject* _callable) {
            Py_XINCREF(_callable);
            callable=_callable;
        }

        virtual ~CallableFilter() {
            Py_DECREF(callable);
        }

        virtual PyObject* perform(char* key,int remaining_distance,PyObject* data) {
            PyObject* tuple=PyTuple_New(3);
            PyTuple_SetItem(tuple,0,PyString_FromString(key));
            PyTuple_SetItem(tuple,1,PyInt_FromLong(remaining_distance));
            Py_XINCREF(data);
            PyTuple_SetItem(tuple,2,data);
            PyObject* result=PyObject_CallObject(callable,tuple);
            Py_XINCREF(result);
            Py_DECREF(tuple);
            return result;
        }

    private:
        PyObject* callable;
};

class DictAction : public action<PyObject*> {
    public:
        DictAction() {
            dict=PyDict_New();
        }

        virtual ~DictAction() {
            Py_DECREF(dict);
        }

        virtual void perform(char* key,int remaining_distance,PyObject* data) {
            PyObject* tuple=PyDict_GetItemString(dict,key);
            if(tuple!=NULL) {
                long value=PyInt_AsLong(PyTuple_GetItem(tuple,0));
                if(value>=remaining_distance) {
                    return;
                }
                else {
                    Py_DECREF(tuple);
                }
            }

            tuple=PyTuple_New(2);
            PyTuple_SetItem(tuple,0,PyInt_FromLong(remaining_distance));
            Py_XINCREF(data);
            PyTuple_SetItem(tuple,1,data);
            PyDict_SetItemString(dict,key,tuple);
        };

        PyObject* get_dict() {
            Py_INCREF(dict);
            return dict;
        }

    private:
        PyObject* dict;
};

class ListAction : public action<PyObject*> {
    public:
        ListAction() {
            list=PyList_New(0);
        }

        virtual ~ListAction() {
            Py_DECREF(list);
        }

        virtual void perform(char* key,int remaining_distance,PyObject* data) {
            PyObject* tuple=PyTuple_New(2);
            PyTuple_SetItem(tuple,0,PyString_FromString(key));

            Py_XINCREF(data);
            if(data!=Py_None) {
                PyTuple_SetItem(tuple,1,data);
                PyList_Append(list,tuple);
            }
        };

        PyObject* get_list() {
            Py_INCREF(list);
            return list;
        }

    private:
        PyObject* list;
};

class TST : public tst<PyObject*> {
    public:
        TST(int initial_size,PyObject* default_value);
        ~TST();
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
    Py_XINCREF(default_value);
}

TST::~TST() {
    Py_XDECREF(default_value);
}

PyObject* TST::get(char* string) {
    PyObject* result=tst<PyObject*>::get(string);
    Py_XINCREF(result);
    return result;
}

PyObject* TST::__getitem__(char* string) {
    return get(string);
}

PyObject* TST::put(char* string,PyObject* data) {
    Py_XINCREF(data);
    return tst<PyObject*>::put(string,data);
}

PyObject* TST::__setitem__(char* string,PyObject* data) {
    return put(string,data);
}

int TST::create_node(tst_node<PyObject*>** current_node,int current_index) {
    int result=tst<PyObject*>::create_node(current_node,current_index);
    Py_XINCREF((array+result)->data);
    return result;
}
