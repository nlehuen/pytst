/* 
 # $Id$
 # Copyright (C) 2004-2005 Nicolas Lehuen <nicolas@lehuen.com>
 #
 # This library is free software; you can redistribute it and/or
 # modify it under the terms of the GNU Lesser General Public
 # License as published by the Free Software Foundation; either
 # version 2.1 of the License, or (at your option) any later version.
 #
 # This library is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 # Lesser General Public License for more details.
 #
 # You should have received a copy of the GNU Lesser General Public
 # License along with this library; if not, write to the Free Software
 # Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#define __PYTHON__BUILD__

#include "tst.h"

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

    virtual void perform(char* string,int string_length,int remaining_distance,PyObject* data) {
        if(_perform==Py_None) {
            return;
        }
        if(!data) {
            data=Py_None;
        }
        Py_XINCREF(data);
        PyObject* tuple=Py_BuildValue("s#iO",string,string_length,remaining_distance,data);
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

    virtual PyObject* perform(char* string,int string_length,int remaining_distance,PyObject* data) {
        if(!data) {
            data=Py_None;
        }
        Py_XINCREF(data);
        PyObject* tuple=Py_BuildValue("s#iO",string,string_length,remaining_distance,data);
        PyObject* result=PyObject_CallObject(callable,tuple);
        Py_DECREF(tuple);
        return result;
    }

private:
    PyObject* callable;
};

class NullFilter : public filter<char,PyObject*> {
public:
    NullFilter() {
    }

    virtual ~NullFilter() {
    }

    virtual PyObject* perform(char* string,int string_length,int remaining_distance,PyObject* data) {
        Py_XINCREF(data);
        return data;
    }
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

    virtual void perform(char* string,int string_length,int remaining_distance,PyObject* data) {
        if(!data) {
            data=Py_None;
        }

        PyObject* key = Py_BuildValue("s#",string,string_length);
        
        PyObject* old_tuple=PyDict_GetItem(dict,key);
        if(old_tuple!=NULL) {
            long value=PyInt_AsLong(PyTuple_GetItem(old_tuple,0));
            if(value>=remaining_distance) {
                Py_DECREF(key);
                return;
            }
        }

        PyObject* tuple=PyTuple_New(2);
        PyTuple_SetItem(tuple,0,PyInt_FromLong(remaining_distance));
        Py_INCREF(data);
        PyTuple_SetItem(tuple,1,data);
        PyDict_SetItem(dict,key,tuple);
        Py_DECREF(tuple);
        Py_DECREF(key);
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

    virtual void perform(char* string,int string_length,int remaining_distance,PyObject* data) {
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

    virtual void perform(char* string,int string_length,int remaining_distance,PyObject* data) {
        if(!data) {
            data=Py_None;
        }
        PyObject* tuple=Py_BuildValue("s#iO",string,string_length,remaining_distance,data);
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

class MemoryStorage : public memory_storage<char,PyObject*> {
public:
    MemoryStorage() : memory_storage<char,PyObject*>(16) {
    }

    MemoryStorage(int initial_size) : memory_storage<char,PyObject*>(initial_size) {
    }

    ~MemoryStorage() {
        int i;
        tst_node<char,PyObject*>* node;
        for(i=0,node=array;i<next;i++,node++) {
            store_data(node,NULL);
        }
    }

    PyObject* store_data(tst_node<char,PyObject*>* node,PyObject* data) {
        PyObject* result=node->data;
        if((node->data=data)!=result) {
            Py_XINCREF(data);
            Py_XDECREF(result);
        }
        return result;
    }
};

class TST : public tst<char,PyObject*,MemoryStorage> {
public:
    TST() : tst<char,PyObject*,MemoryStorage>(new MemoryStorage(16),Py_None) {
        Py_INCREF(Py_None);
    }

    TST(PyObject* file) : tst<char,PyObject*,MemoryStorage>(new MemoryStorage(16),NULL) {
        if(!PyFile_Check(file)) {
            throw TSTException("Argument of constructor must be a file object");
        }
        ObjectSerializer os;
        tst<char,PyObject*,MemoryStorage>::read(PyFile_AsFile(file),&os);
        Py_XINCREF(default_value);
    }

    TST(int initial_size,PyObject* default_value) : tst<char,PyObject*,MemoryStorage>(new MemoryStorage(initial_size),default_value) {
        if(!default_value) default_value=Py_None;
        Py_INCREF(default_value);
    }

    ~TST() {
        Py_XDECREF(default_value);
    }

    PyObject* write(PyObject* file) {
        if(!PyFile_Check(file)) {
            throw TSTException("Argument of write() must be a file object");
        }
        ObjectSerializer *os=new ObjectSerializer();
        tst<char,PyObject*,MemoryStorage>::write(PyFile_AsFile(file),os);
        delete os;
        return Py_None;
    }

    inline PyObject* get(char* string,int string_length) {
        PyObject* result=tst<char,PyObject*,MemoryStorage>::get(string,string_length);
        Py_INCREF(result);
        return result;
    }

    inline PyObject* get_or_build(char* string,int string_length,filter<char,PyObject*>* factory) {
        PyObject* result=tst<char,PyObject*,MemoryStorage>::get_or_build(string,string_length,factory);
        Py_INCREF(result);
        return result;
    }


    inline PyObject* put(char* string,int string_length,PyObject* data) {
        Py_INCREF(data);
        PyObject* result=tst<char,PyObject*,MemoryStorage>::put(string,string_length,data);
        Py_INCREF(result);
        return result;
    }

    inline PyObject* __getitem__(char* string,int string_length) {
        PyObject* result=get(string,string_length);
        return result;
    }

    inline PyObject* __setitem__(char* string,int string_length,PyObject* data) {
        PyObject* result=put(string,string_length,data);
        return result;
    }

    inline void __delitem__(char* string,int string_length) {
        remove(string,string_length);
    }
};

class PythonReference {
public:
    inline PythonReference() {
        this->ref=NULL;
    }

    inline PythonReference(PyObject *object) {
        this->ref = object;
        Py_XINCREF(object);
    }

    inline PythonReference(const PythonReference& that) {
        this->ref = that.ref;
        Py_XINCREF(this->ref);
    }

    inline PythonReference& operator= (const PythonReference& that) {
        PyObject* old = this->ref;
        
        if((this->ref = that.ref) != old) {
            Py_XINCREF(this->ref);
            Py_XDECREF(old);
        }
        
        return *this;
    }

    inline PyObject* object() {
        return ref;
    }

    inline ~PythonReference() {
        Py_XDECREF(ref);
    }

private:
    PyObject* ref;
};
