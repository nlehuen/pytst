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

class PythonReference {
public:
    explicit PythonReference() : ref(Py_None) {
        Py_INCREF(ref);
    }

    explicit PythonReference(PyObject *object) : ref(object) {
        if(ref==NULL) {
            throw TSTException("Cannot reference NULL");
        }
        Py_INCREF(ref);
    }
    
    explicit PythonReference(PyObject *object, int borrow) : ref(object) {
        if(borrow==0) {
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

    PyObject* get() {
        return ref;
    }

    PyObject* lend() {
        Py_INCREF(ref);
        return ref;
    }

    ~PythonReference() {
        Py_DECREF(ref);
    }

    void write(FILE* file) {
    }

private:
    PyObject* ref;
};

class CallableAction : public action<char,PythonReference> {
public:
    CallableAction(PythonReference perform,PythonReference result) : _perform(perform), _result(result) {
    }

    virtual ~CallableAction() {
    }

    virtual void perform(char* string,int string_length,int remaining_distance,PythonReference data) {
        if(_perform.get()==Py_None) {
            return;
        }
        PyObject* tuple=Py_BuildValue("s#iO",string,string_length,remaining_distance,data.get());
        Py_DECREF(PyObject_CallObject(_perform.get(),tuple));
        Py_DECREF(tuple);
    }

    virtual PythonReference result() {
        if(_result.get()==Py_None) {
            return PythonReference();
        }
        else {
            return PythonReference(PyObject_CallObject(_result.get(),NULL),1);
        }
    }

private:
    PythonReference _perform,_result;
};

class CallableFilter : public filter<char,PythonReference> {
public:
    CallableFilter(PythonReference _callable) : callable(_callable) {
    }

    virtual ~CallableFilter() {
    }

    virtual PythonReference perform(char* string,int string_length,int remaining_distance,PythonReference data) {
        PyObject* tuple=Py_BuildValue("s#iO",string,string_length,remaining_distance,data.get());
        PythonReference result(PyObject_CallObject(callable.get(),tuple),1);
        Py_DECREF(tuple);
        return result;
    }

private:
    PythonReference callable;
};

class NullFilter : public filter<char,PythonReference> {
public:
    NullFilter() {
    }

    virtual ~NullFilter() {
    }

    virtual PythonReference perform(char* string,int string_length,int remaining_distance,PythonReference data) {
        return data;
    }
};

class DictAction : public action<char,PythonReference> {
public:
    DictAction() : dict(PyDict_New(),1) {
    }

    virtual ~DictAction() {
    }

    virtual void perform(char* string,int string_length,int remaining_distance,PythonReference data) {
        PythonReference key(Py_BuildValue("s#",string,string_length),1);
        
        PyObject* old_tuple=PyDict_GetItem(dict.get(),key.get());
        if(old_tuple!=NULL) {
            long value=PyInt_AsLong(PyTuple_GetItem(old_tuple,0));
            if(value>=remaining_distance) {
                return;
            }
        }

        PythonReference tuple(Py_BuildValue("(iO)",remaining_distance,data.get()));
        
        PyDict_SetItem(dict.get(),key.get(),tuple.get());
    };

    virtual PythonReference result() {
        return dict;
    }

private:
    PythonReference dict;
};

class ListAction : public action<char,PythonReference> {
public:
    ListAction() : list(PyList_New(0),1) {
    }

    virtual ~ListAction() {
    }

    virtual void perform(char* string,int string_length,int remaining_distance,PythonReference data) {
        PyList_Append(list.get(),data.get());
    }

    virtual PythonReference result() {
        return list;
    }

private:
    PythonReference list;
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

class ObjectSerializer {
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

    virtual ~MemoryStorage() {
        int i;
        tst_node<char,PyObject*>* node;
        for(i=0,node=array;i<next;i++,node++) {
            store_data(node,NULL);
        }
    }

    inline virtual PyObject* store_data(tst_node<char,PyObject*>* node,PyObject* data) {
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

    TST(PyObject* file) : tst<char,PyObject*,MemoryStorage>(new MemoryStorage(16),Py_None) {
        if(!PyFile_Check(file)) {
            throw TSTException("Argument of constructor must be a file object");
        }
        tst<char,PyObject*,MemoryStorage>::read(PyFile_AsFile(file));
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
        tst<char,PyObject*,MemoryStorage>::write(PyFile_AsFile(file));
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
