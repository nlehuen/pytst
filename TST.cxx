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
            if(!data) {
                data=Py_None;
            }

            PyObject* tuple=PyTuple_New(3);
            PyTuple_SetItem(tuple,0,PyString_FromString(key));
            PyTuple_SetItem(tuple,1,PyInt_FromLong(remaining_distance));
            Py_INCREF(data);
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
            if(!data) {
                data=Py_None;
            }

            PyObject* tuple=PyTuple_New(3);
            PyTuple_SetItem(tuple,0,PyString_FromString(key));
            PyTuple_SetItem(tuple,1,PyInt_FromLong(remaining_distance));
            Py_INCREF(data);
            PyTuple_SetItem(tuple,2,data);
            PyObject* result=PyObject_CallObject(callable,tuple);
            if(result==NULL) {
                PyErr_Print();
                result=Py_None;
            }
            Py_INCREF(result);
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
            if(!data) {
                data=Py_None;
            }

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
            Py_INCREF(data);
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
            if(!data) {
                data=Py_None;
            }
            Py_INCREF(data);
            PyList_Append(list,data);
        }

        PyObject* get_list() {
            Py_INCREF(list);
            return list;
        }

    private:
        PyObject* list;
};

class ObjectSerializer : public serializer<PyObject*> {
    public:
        ObjectSerializer() {
            PyObject* name=PyString_FromString("cPickle");
            cPickle=PyImport_Import(name);
            if(!cPickle) {
                printf("Impossible d'importer cPickle\n");
                PyErr_SetString(PyExc_RuntimeError,"Impossible d'importer cPickle");
            }
            Py_DECREF(name);
        }

        virtual ~ObjectSerializer() {
            Py_DECREF(cPickle);
        }

        virtual void write(FILE* file,PyObject* data) {
            PyObject* dumps = PyObject_GetAttrString(cPickle,"dumps");
            PyObject* call=Py_BuildValue("(oi)",data,2);
            PyObject* result=PyObject_CallObject(dumps,call);
            Py_DECREF(call);
            Py_DECREF(dumps);
            char *string;
            int length;
            PyString_AsStringAndSize(result,&string,&length);
            fwrite(&length,sizeof(int),1,file);
            fwrite(string,sizeof(char),length,file);
            Py_DECREF(result);
        }

        virtual PyObject* read(FILE* file) {
            int length;
            fread(&length,sizeof(int),1,file);
            char* string=(char*)malloc(length);
            fread(string,sizeof(char),length,file);
            PyObject* dumps=PyString_FromStringAndSize(string,length);
            PyObject* loads=PyObject_GetAttrString(cPickle,"loads");
            PyObject* call=Py_BuildValue("(o)",loads);
            PyObject* result=PyObject_CallObject(loads,call);
            Py_DECREF(call);
            Py_DECREF(loads);
            Py_DECREF(dumps);
            free(string);
            return result;
        }
    
    private:
        PyObject* cPickle;
};

class TST : public tst<PyObject*> {
    public:
        TST();
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

TST::TST() : tst<PyObject*>(16,Py_None) {
    Py_XINCREF(default_value);
}

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
    PyObject* result = tst<PyObject*>::put(string,data);
    Py_XINCREF(result);
    return result;
}

PyObject* TST::__setitem__(char* string,PyObject* data) {
    return put(string,data);
}

int TST::create_node(tst_node<PyObject*>** current_node,int current_index) {
    int result=tst<PyObject*>::create_node(current_node,current_index);
    Py_XINCREF((array+result)->data);
    return result;
}
