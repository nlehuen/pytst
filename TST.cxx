#define __PYTHON__BUILD__

#include "tst.h"

#include "Python.h"

class CallableAction : public action<PyObject*> {
    public:
        CallableAction(PyObject* _callable) {
            Py_XINCREF(_callable);
            callable=_callable;
        }

        ~CallableAction() {
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

class CallablePredicate : public predicate<PyObject*> {
    public:
        CallablePredicate(PyObject* _callable) {
            Py_XINCREF(_callable);
            callable=_callable;
        }

        ~CallablePredicate() {
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
        DictAction(PyObject* _predicate) {
            Py_INCREF(_predicate);
            predicate=_predicate;
            dict=PyDict_New();
        }

        ~DictAction() {
            Py_DECREF(predicate);
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

            if(predicate!=Py_None) {
                PyObject* tuple2=PyTuple_New(1);
                Py_XINCREF(data);
                PyTuple_SetItem(tuple2,0,data);
                PyObject* data2=PyObject_CallObject(predicate,tuple2);
                Py_DECREF(tuple2);
                if(data2) {
                    data=data2;
                }
                else {
                    return;
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
        PyObject* dict,*predicate;
};

class ListAction : public action<PyObject*> {
    public:
        ListAction(PyObject* _predicate) {
            Py_INCREF(_predicate);
            predicate=_predicate;
            list=PyList_New(0);
        }

        ~ListAction() {
            Py_DECREF(predicate);
            Py_DECREF(list);
        }

        virtual void perform(char* key,int remaining_distance,PyObject* data) {
            PyObject* tuple=PyTuple_New(2);
            PyTuple_SetItem(tuple,0,PyString_FromString(key));

            if(predicate!=Py_None) {
                PyObject* tuple2=PyTuple_New(1);
                Py_XINCREF(data);
                PyTuple_SetItem(tuple2,0,data);
                PyObject* data2=PyObject_CallObject(predicate,tuple2);
                Py_DECREF(tuple2);
                if(data2) {
                    data=data2;
                }
                else {
                    return;
                }
            }

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
        PyObject* list,*predicate;
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
        PyObject* almost(char* string, int string_length, int remaining_distance);

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

PyObject* TST::almost(char* string, int string_length, int remaining_distance) {
    DictAction action(Py_None);
    tst<PyObject*>::almost_perform(string,string_length,remaining_distance,&action);
    return action.get_dict();
}

int TST::create_node(tst_node<PyObject*>** current_node,int current_index) {
    int result=tst<PyObject*>::create_node(current_node,current_index);
    Py_INCREF((array+result)->data);
    return result;
}
