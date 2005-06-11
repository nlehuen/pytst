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
#include "PythonReference.h"

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

    virtual PythonReference perform(char* string,int string_length,int remaining_distance,PythonReference data) {
        PythonReference tuple(Py_BuildValue("s#iO",string,string_length,remaining_distance,data.get()),0);
        return PythonReference(PyObject_CallObject(callable.get(),tuple.get()),0);
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
    DictAction() : dict(PyDict_New(),0) {
    }

    virtual ~DictAction() {
    }

    virtual void perform(char* string,int string_length,int remaining_distance,PythonReference data) {
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

    virtual void perform(char* string,int string_length,int remaining_distance,PythonReference data) {
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

    virtual void perform(char* string,int string_length,int remaining_distance,PythonReference data) {
        PythonReference tuple(Py_BuildValue("s#iO",string,string_length,remaining_distance,data.get),0);
        PyList_Append(list.get(),tuple.get());
    }

    virtual PythonReference result() {
        return list;
    }

private:
    PythonReference list;
};

class ObjectSerializer : public serializer<char,PythonReference> {
public:
    ObjectSerializer() {
        PythonReference name(PyString_FromString("cPickle"),0);
        PythonReference cPickle(PyImport_Import(name.get()),0);
        dumps = PythonReference(PyObject_GetAttrString(cPickle.get(),"dumps"),0);
        loads = PythonReference(PyObject_GetAttrString(cPickle.get(),"loads"),0);
    }

    virtual ~ObjectSerializer() {
    }

    virtual void write(FILE* file,PythonReference data) {
        PythonReference call(Py_BuildValue("Oi",data.get(),2),0);
        PythonReference result(PyObject_CallObject(dumps.get(),call.get()),0);
        char *string;
        int length;
        PyString_AsStringAndSize(result.get(),&string,&length);
        fwrite(&length,sizeof(int),1,file);
        fwrite(string,sizeof(char),length,file);
    }

    virtual PythonReference read(FILE* file) {
        int length;
        fread(&length,sizeof(int),1,file);
        char* string=(char*)malloc(length);
        fread(string,sizeof(char),length,file);
        PythonReference dumped(PyString_FromStringAndSize(string,length),0);
        PythonReference call(Py_BuildValue("(O)",dumped.get()),0);
        PythonReference result(PyObject_CallObject(loads.get(),call.get()),0);
        free(string);
        return result;
    }

private:
    PythonReference dumps,loads;
};


typedef memory_storage<char,PythonReference> MemoryStorage;

class TST : public tst<char,PythonReference,MemoryStorage> {
public:
    TST() : tst<char,PythonReference,MemoryStorage>(new MemoryStorage(16),PythonReference()) {
    }

    TST(PyObject* file) : tst<char,PythonReference,MemoryStorage>(new MemoryStorage(16),PythonReference()) {
        if(!PyFile_Check(file)) {
            throw TSTException("Argument of constructor must be a file object");
        }
        ObjectSerializer os;
        tst<char,PythonReference,MemoryStorage>::read(PyFile_AsFile(file),&os);
    }

    TST(int initial_size,PyObject* default_value) : tst<char,PythonReference,MemoryStorage>(new MemoryStorage(initial_size),PythonReference(default_value)) {
    }

    TST(int initial_size) : tst<char,PythonReference,MemoryStorage>(new MemoryStorage(initial_size),PythonReference()) {
    }

    virtual ~TST() {
    }

    PyObject* write(PyObject* file) {
        if(!PyFile_CheckExact(file)) {
            throw TSTException("Argument of write() must be a file object");
        }
        ObjectSerializer os;
        tst<char,PythonReference,MemoryStorage>::write(PyFile_AsFile(file),&os);
        // Should we INCREF here ?
        return Py_None;
    }

    inline PyObject* get(char* string,int string_length) {
        return tst<char,PythonReference,MemoryStorage>::get(string,string_length).lend();
    }

    inline PyObject* get_or_build(char* string,int string_length,filter<char,PythonReference>* factory) {
        return tst<char,PythonReference,MemoryStorage>::get_or_build(string,string_length,factory).lend();
    }


    inline PyObject* put(char* string,int string_length,PyObject* data) {
        return tst<char,PythonReference,MemoryStorage>::put(string,string_length,PythonReference(data)).lend();
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
