#define __PYTHON__BUILD__

#include "tst.h"

#include "Python.h"

class TSTException {
    public:
        TSTException(char* _message) {
            message=_message;
        }

        char* message;
};

class CallableAction : public action<PyObject*> {
    public:
        CallableAction(PyObject* _callable) {
            Py_INCREF(_callable);
            callable=_callable;
        }

        virtual ~CallableAction() {
            Py_DECREF(callable);
        }

        virtual void perform(char* key,int remaining_distance,PyObject* data) {
            if(!data) {
                data=Py_None;
            }

            PyObject* tuple=Py_BuildValue("siO",key,remaining_distance,data);
            PyObject_CallObject(callable,tuple);
            Py_DECREF(tuple);
        }

        virtual PyObject* result() {
            return Py_None;
        }

    private:
        PyObject* callable;
};

class CallableFilter : public filter<PyObject*> {
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

class DictAction : public action<PyObject*> {
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
            Py_XINCREF(data);
            PyTuple_SetItem(tuple,1,data);
            PyDict_SetItemString(dict,key,tuple);
            Py_DECREF(tuple);
        };

        virtual PyObject* result() {
            return dict;
        }

    private:
        PyObject* dict;
};

class ListAction : public action<PyObject*> {
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
            Py_INCREF(data);
            PyList_Append(list,data);
        }

        virtual PyObject* result() {
            return list;
        }

    private:
        PyObject* list;
};

class ObjectSerializer : public serializer<PyObject*> {
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

class TST : public tst<PyObject*> {
    public:
        TST();
        TST(PyObject* file);
        TST(int initial_size,PyObject* default_value);
        virtual ~TST();
        PyObject* write(PyObject* file);

    protected:
        virtual void store_data(tst_node<PyObject*>* node,PyObject* data);
};

TST::TST() : tst<PyObject*>(16,Py_None) {
    Py_INCREF(Py_None);
}

TST::TST(PyObject* file) : tst<PyObject*>() {
    if(!PyFile_Check(file)) {
        throw TSTException("Argument of constructor must be a file object");
    }
    ObjectSerializer os;
    tst<PyObject*>::read(PyFile_AsFile(file),&os);
}

TST::TST(int initial_size,PyObject* default_value) : tst<PyObject*>(initial_size,default_value) {
    Py_XINCREF(default_value);
}

TST::~TST() {
    Py_XDECREF(default_value);
}

void TST::store_data(tst_node<PyObject*>* node,PyObject* data) {
    Py_XDECREF(node->data);
    Py_XINCREF(data);
    node->data=data;
}

PyObject* TST::write(PyObject* file) {
    if(!PyFile_Check(file)) {
        throw TSTException("Argument of write() must be a file object");
    }
    ObjectSerializer *os=new ObjectSerializer();
    tst<PyObject*>::write(PyFile_AsFile(file),os);
    delete os;
    return Py_None;
}
