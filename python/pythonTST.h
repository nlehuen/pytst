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
#include "Python.h"
#include "PythonReference.h"

class CallableAction : public action<char,PythonReference> {
public:
    CallableAction(PythonReference perform,PythonReference result) : _perform(perform), _result(result) {
    }

    virtual ~CallableAction() {
    }

    virtual void perform(const char* string,int string_length,int remaining_distance,PythonReference data) {
        if(_perform.get()==Py_None) {
            return;
        }
        PythonReference tuple(Py_BuildValue("s#iO",string,string_length,remaining_distance,data.get()),0);
        Py_DECREF(PyObject_CallObject(_perform.get(),tuple.get()));
    }

    virtual PythonReference result() {
        if(_result.get()==Py_None) {
            return PythonReference();
        }
        else {
            return PythonReference(PyObject_CallObject(_result.get(),NULL),0);
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

    virtual PythonReference perform(const char* string,int string_length,int remaining_distance,PythonReference data) {
        PythonReference tuple(Py_BuildValue("s#iO",string,string_length,remaining_distance,data.get()),0);
        return PythonReference(PyObject_CallObject(callable.get(),tuple.get()),0);
    }

private:
    PythonReference callable;
};

class DictAction : public action<char,PythonReference> {
public:
    DictAction() : dict(PyDict_New(),0) {
    }

    virtual ~DictAction() {
    }

    virtual void perform(const char* string,int string_length,int remaining_distance,PythonReference data) {
        PythonReference key(Py_BuildValue("s#",string,string_length),0);
        
        PyObject* old_tuple=PyDict_GetItem(dict.get(),key.get());
        if(old_tuple!=NULL) {
            long value=PyInt_AsLong(PyTuple_GetItem(old_tuple,0));
            if(value>=remaining_distance) {
                return;
            }
        }

        PythonReference tuple(Py_BuildValue("iO",remaining_distance,data.get()),0);
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
    ListAction() : list(PyList_New(0),0) {
    }

    virtual ~ListAction() {
    }

    virtual void perform(const char* string,int string_length,int remaining_distance,PythonReference data) {
        PyList_Append(list.get(),data.get());
    }

    virtual PythonReference result() {
        return list;
    }

private:
    PythonReference list;
};

class TupleListAction : public action<char,PythonReference> {
public:
    TupleListAction() : list(PyList_New(0),0){
    }

    virtual ~TupleListAction() {
    }

    virtual void perform(const char* string,int string_length,int remaining_distance,PythonReference data) {
        PythonReference tuple(Py_BuildValue("s#iO",string,string_length,remaining_distance,data.get()),0);
        PyList_Append(list.get(),tuple.get());
    }

    virtual PythonReference result() {
        return list;
    }

private:
    PythonReference list;
};

class ObjectSerializer {
public:
    ObjectSerializer();
    
    void write(FILE* file,PythonReference data);
    PythonReference ObjectSerializer::read(FILE* file);

    void write_to_file(PythonReference file,PythonReference data);
    PythonReference ObjectSerializer::read_from_file(PythonReference file);

private:
    PythonReference dumps,loads;
};

ObjectSerializer::ObjectSerializer() {
    PythonReference name(PyString_FromString("cPickle"),0);
    PythonReference cPickle(PyImport_Import(name.get()),0);
    dumps = PythonReference(PyObject_GetAttrString(cPickle.get(),"dumps"),0);
    loads = PythonReference(PyObject_GetAttrString(cPickle.get(),"loads"),0);
}


void ObjectSerializer::write(FILE* file,PythonReference data) {
    PythonReference call(Py_BuildValue("Oi",data.get(),2),0);
    PythonReference result(PyObject_CallObject(dumps.get(),call.get()),0);
    char *string;
    int length;
    PyString_AsStringAndSize(result.get(),&string,&length);
    fwrite(&length,sizeof(int),1,file);
    fwrite(string,sizeof(char),length,file);
}

void ObjectSerializer::write_to_file(PythonReference file,PythonReference data) {
    return write(PyFile_AsFile(file.get()),data);
}

PythonReference ObjectSerializer::read(FILE* file) {
    int length;
    fread(&length,sizeof(int),1,file);
    char* string=(char*)tst_malloc(length);
    fread(string,sizeof(char),length,file);
    PythonReference dumped(PyString_FromStringAndSize(string,length),0);
    PythonReference call(Py_BuildValue("(O)",dumped.get()),0);
    PythonReference result(PyObject_CallObject(loads.get(),call.get()),0);
    tst_free(string);
    return result;
}

PythonReference ObjectSerializer::read_from_file(PythonReference file) {
    return read(PyFile_AsFile(file.get()));
}


typedef memory_storage<char,PythonReference> MemoryStorage;
typedef tst<char,PythonReference,MemoryStorage,ObjectSerializer> BaseTST;

class TST : public BaseTST {
public:
    TST() : BaseTST(new MemoryStorage(16),PythonReference()) {
    }

    virtual ~TST() {
    }

    virtual PythonReference write_to_file(PythonReference file) {
        if(!PyFile_CheckExact(file.get())) {
            throw TSTException("Argument of write() must be a file object");
        }
        this->write(PyFile_AsFile(file.get()));
        return PythonReference();
    }

    virtual PythonReference read_from_file(PythonReference file) {
        if(!PyFile_CheckExact(file.get())) {
            throw TSTException("Argument of write() must be a file object");
        }
        this->read(PyFile_AsFile(file.get()));
        return PythonReference();
    }

    PythonReference __getitem__(char* string,int string_length) {
        return get(string,string_length);
    }

    PythonReference __setitem__(char* string,int string_length,PythonReference data) {
        return put(string,string_length,data);
    }

    void __delitem__(char* string,int string_length) {
        remove(string,string_length);
    }

    PythonReference __contains__(char* string,int string_length) {
        if(contains(string,string_length)) {
            return PythonReference(Py_False);
        }
        else {
            return PythonReference(Py_True);
        }
    }
};
