#define __PYTHON__BUILD__

#include "tst.h"

class TSTException {
    public:
        TSTException(char* _message) {
            message=_message;
        }

        char* message;
};

class CallableAction : public action<char,PyObject*> {
    public:
        CallableAction(PyObject* perform,PyObject* result) {
            if(!perform) perform=Py_None;
            Py_INCREF(perform);
            _perform=perform;
            if(!result) result=Py_None;
            Py_INCREF(result);
            _result=result;
        }

        virtual ~CallableAction() {
            Py_DECREF(_perform);
            Py_DECREF(_result);
        }

        virtual void perform(char* key,int remaining_distance,PyObject* data) {
            if(_perform==Py_None) {
                return;
            }
            if(!data) {
                data=Py_None;
            }

            PyObject* tuple=Py_BuildValue("siO",key,remaining_distance,data);
            Py_DECREF(PyObject_CallObject(_perform,tuple));
            Py_DECREF(tuple);
        }

        virtual PyObject* result() {
            if(_result==Py_None) {
                return Py_None;
            }
            else {
                return PyObject_CallObject(_result,NULL);
            }
        }

    private:
        PyObject *_perform,*_result;
};

class CallableFilter : public filter<char,PyObject*> {
    public:
        CallableFilter(PyObject* _callable) {
            Py_INCREF(_callable);
            callable=_callable;
        }

        virtual ~CallableFilter() {
            Py_DECREF(callable);
        }

        virtual PyObject* perform(char* key,int remaining_distance,PyObject* data) {
            if(!data) {
                data=Py_None;
            }

            PyObject* tuple=Py_BuildValue("siO",key,remaining_distance,data);
            PyObject* result=PyObject_CallObject(callable,tuple);
            if(result==NULL) {
                PyErr_Print();
            }
            Py_DECREF(tuple);
            return result;
        }

    private:
        PyObject* callable;
};

class DictAction : public action<char,PyObject*> {
    public:
        DictAction() {
            dict=PyDict_New();
            if(!dict) {
                throw TSTException("Cannot build a list");
            }
        }

        virtual ~DictAction() {
            Py_DECREF(dict);
        }

        virtual void perform(char* key,int remaining_distance,PyObject* data) {
            if(!data) {
                data=Py_None;
            }

            PyObject* old_tuple=PyDict_GetItemString(dict,key);
            if(old_tuple!=NULL) {
                long value=PyInt_AsLong(PyTuple_GetItem(old_tuple,0));
                if(value>=remaining_distance) {
                    return;
                }
            }

            PyObject* tuple=PyTuple_New(2);
            PyTuple_SetItem(tuple,0,PyInt_FromLong(remaining_distance));
            Py_INCREF(data);
            PyTuple_SetItem(tuple,1,data);
            PyDict_SetItemString(dict,key,tuple);
            Py_DECREF(tuple);
        };

        virtual PyObject* result() {
            Py_INCREF(dict);
            return dict;
        }

    private:
        PyObject* dict;
};

class ListAction : public action<char,PyObject*> {
    public:
        ListAction() {
            list=PyList_New(0);
            if(!list) {
                throw TSTException("Cannot build a list");
            }
        }

        virtual ~ListAction() {
            Py_DECREF(list);
        }

        virtual void perform(char* key,int remaining_distance,PyObject* data) {
            if(!data) {
                data=Py_None;
            }
            PyList_Append(list,data);
        }

        virtual PyObject* result() {
            Py_INCREF(list);
            return list;
        }

    private:
        PyObject* list;
};

class TupleListAction : public action<char,PyObject*> {
    public:
        TupleListAction() {
            list=PyList_New(0);
            if(!list) {
                throw TSTException("Cannot build a list");
            }
        }

        virtual ~TupleListAction() {
            Py_DECREF(list);
        }

        virtual void perform(char* key,int remaining_distance,PyObject* data) {
            if(!data) {
                data=Py_None;
            }
            PyObject* tuple=Py_BuildValue("siO",key,remaining_distance,data);
            PyList_Append(list,tuple);
            Py_DECREF(tuple);
        }

        virtual PyObject* result() {
            Py_INCREF(list);
            return list;
        }

    private:
        PyObject* list;
};

class ObjectSerializer : public serializer<char,PyObject*> {
    public:
        ObjectSerializer() {
            PyObject* name=PyString_FromString("cPickle");
            PyObject* cPickle=PyImport_Import(name);
            Py_DECREF(name);
            if(!cPickle) {
                throw TSTException("Cannot get module cPickle");
            }
            dumps = PyObject_GetAttrString(cPickle,"dumps");
            if(!dumps) {
                Py_DECREF(cPickle);
                throw TSTException("Cannot get cPickle.dumps");
            }
            loads = PyObject_GetAttrString(cPickle,"loads");
            if(!loads) {
                Py_DECREF(dumps);
                Py_DECREF(cPickle);
                throw TSTException("Cannot get cPickle.loads");
            }
            Py_DECREF(cPickle);
        }

        virtual ~ObjectSerializer() {
            Py_DECREF(dumps);
            Py_DECREF(loads);
        }

        virtual void write(FILE* file,PyObject* data) {
            PyObject* call=Py_BuildValue("Oi",data,2);
            if(!call) {
                throw TSTException("Py_BuildValue(\"Oi\",data,2) failed");
            }
            PyObject* result=PyObject_CallObject(dumps,call);
            Py_DECREF(call);
            if(!result) {
                throw TSTException("Call to dumps failed");
            }
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
            PyObject* call=Py_BuildValue("(O)",dumps);
            if(!call) {
                Py_DECREF(dumps);
                free(string);
                throw TSTException("Py_BuildValue(\"(O)\",dumps) failed");
            }
            PyObject* result=PyObject_CallObject(loads,call);
            Py_DECREF(call);
            Py_DECREF(dumps);
            free(string);
            if(!result) {
                throw TSTException("Call to loads failed");
            }
            return result;
        }

    private:
        PyObject *dumps,*loads;
};

class TST : public tst<char,PyObject*> {
    public:
        TST();
        TST(PyObject* file);
        TST(int initial_size,PyObject* default_value);
        virtual ~TST();
        PyObject* write(PyObject* file);
        virtual PyObject* get(char* string);
        virtual PyObject* get_or_build(char* string,filter<char,PyObject*>* factory);
        virtual PyObject* put(char* string,PyObject* data);
        PyObject* __getitem__(char* string);
        PyObject* __setitem__(char* string,PyObject* data);
        void __delitem__(char* string);

    protected:
        virtual PyObject* store_data(tst_node<char,PyObject*>* node,PyObject* data,int want_old_value);
};

TST::TST() : tst<char,PyObject*>(16,Py_None) {
    Py_INCREF(Py_None);
}

TST::TST(PyObject* file) : tst<char,PyObject*>() {
    if(!PyFile_Check(file)) {
        throw TSTException("Argument of constructor must be a file object");
    }
    ObjectSerializer os;
    tst<char,PyObject*>::read(PyFile_AsFile(file),&os);
}

TST::TST(int initial_size,PyObject* default_value) : tst<char,PyObject*>(initial_size,default_value) {
    if(!default_value) default_value=Py_None;
    Py_INCREF(default_value);
}

TST::~TST() {
    clear_nodes();
    // TODO : pourquoi ce DECREF est en trop ?
    // Py_DECREF(default_value);
}

PyObject* TST::store_data(tst_node<char,PyObject*>* node,PyObject* data,int want_old_value) {
    PyObject* result=node->data;
    if(want_old_value==0) {
        Py_XDECREF(result);
    }
    Py_XINCREF(data);
    node->data=data;
    return result;
}

PyObject* TST::write(PyObject* file) {
    if(!PyFile_Check(file)) {
        throw TSTException("Argument of write() must be a file object");
    }
    ObjectSerializer *os=new ObjectSerializer();
    tst<char,PyObject*>::write(PyFile_AsFile(file),os);
    delete os;
    return Py_None;
}

PyObject* TST::get(char* string) {
    PyObject* result=tst<char,PyObject*>::get(string);
    Py_INCREF(result);
    return result;
}

PyObject* TST::get_or_build(char* string,filter<char,PyObject*>* factory) {
    PyObject* result=tst<char,PyObject*>::get_or_build(string,factory);
    Py_INCREF(result);
    return result;
}


PyObject* TST::put(char* string,PyObject* data) {
    PyObject* result=tst<char,PyObject*>::put(string,data);
    return result;
}

PyObject* TST::__getitem__(char* string) {
    return get(string);
}

PyObject* TST::__setitem__(char* string,PyObject* data) {
    return put(string,data);
}

void TST::__delitem__(char* string) {
    remove(string);
}

