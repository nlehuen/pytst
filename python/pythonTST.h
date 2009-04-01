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
#include "qad_string.h"

#include <iostream>
#include <fstream>

#ifdef ZIPPED_TREE
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#endif

typedef qad_string<char> string_type;

class CallableAction : public tst_action<char,PythonReference,string_type > {
public:
    CallableAction(PythonReference perform,PythonReference result) : _perform(perform), _result(result) {
    }

    virtual ~CallableAction() {
    }

    virtual void perform(const string_type& string,int remaining_distance,PythonReference data) {
        if(_perform.get()==Py_None) {
            return;
        }
        PythonReference tuple(Py_BuildValue("s#iO",string.data(),string.size(),remaining_distance,data.get()),0);
        PyObject* result = PyObject_CallObject(_perform.get(),tuple.get());
        if(result) {
            Py_DECREF(result);
        } else {
            throw PythonException("An exception was raised in a Python callback");
        }
    }

    virtual PythonReference result() {
        if(_result.get()==Py_None) {
            return PythonReference();
        }
        else {
            PyObject* result = PyObject_CallObject(_result.get(),0);
            if(result) {
                return PythonReference(result,0);
            }
            else {
                throw PythonException("An exception was raised in a Python callback");
            }
        }
    }

private:
    PythonReference _perform,_result;
};

class CallableFilter : public tst_filter<char,PythonReference,string_type > {
public:
    CallableFilter(PythonReference _callable) : callable(_callable) {
    }

    virtual ~CallableFilter() {
    }

    virtual PythonReference perform(const string_type& string,int remaining_distance,PythonReference data) {
        PythonReference tuple(Py_BuildValue("s#iO",string.data(),string.size(),remaining_distance,data.get()),0);
        PyObject* result = PyObject_CallObject(callable.get(),tuple.get());
        if(result) {
            return PythonReference(result,0);
        }
        else {
            throw PythonException("An exception was raised in a Python callback");
        }
    }

private:
    PythonReference callable;
};

class DictAction : public tst_action<char,PythonReference,string_type > {
public:
    DictAction() : dict(PyDict_New(),0) {
    }

    virtual ~DictAction() {
    }

    virtual void perform(const string_type& string,int remaining_distance,PythonReference data) {
        PythonReference key(Py_BuildValue("s#",string.data(),string.size()),0);
        
        PyObject* old_tuple=PyDict_GetItem(dict.get(),key.get());
        if(old_tuple!=0) {
            long value=PyInt_AsLong(PyTuple_GetItem(old_tuple,0));
            if(value<remaining_distance) {
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

class ListAction : public tst_action<char,PythonReference,string_type > {
public:
    ListAction() : list(PyList_New(0),0) {
    }

    virtual ~ListAction() {
    }

    virtual void perform(const string_type& string,int remaining_distance,PythonReference data) {
        PyList_Append(list.get(),data.get());
    }

    virtual PythonReference result() {
        return list;
    }

private:
    PythonReference list;
};

class TupleListAction : public tst_action<char,PythonReference,string_type > {
public:
    TupleListAction() : list(PyList_New(0),0){
    }

    virtual ~TupleListAction() {
    }

    virtual void perform(const string_type& string,int remaining_distance,PythonReference data) {
        PythonReference tuple(Py_BuildValue("s#iO",string.data(),string.size(),remaining_distance,data.get()),0);
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
    
    void write(std::ostream& file,PythonReference data);
    PythonReference read(std::istream& file);

private:
    PythonReference dumps,loads;
};

ObjectSerializer::ObjectSerializer() {
    PythonReference name(PyString_FromString("cPickle"),0);
    PythonReference cPickle(PyImport_Import(name.get()),0);
    dumps = PythonReference(PyObject_GetAttrString(cPickle.get(),"dumps"),0);
    loads = PythonReference(PyObject_GetAttrString(cPickle.get(),"loads"),0);
}


void ObjectSerializer::write(std::ostream& file,PythonReference data) {
    PythonReference call(Py_BuildValue("Oi",data.get(),2),0);
    PythonReference result(PyObject_CallObject(dumps.get(),call.get()),0);
    char *string;
    Py_ssize_t length;
    PyString_AsStringAndSize(result.get(),&string,&length);
    file.write((char*)(&length),sizeof(Py_ssize_t));
    file.write(string,length);
}

PythonReference ObjectSerializer::read(std::istream& file) {
    Py_ssize_t length;
    file.read((char*)(&length),sizeof(Py_ssize_t));
    char* string=(char*)tst_malloc(length);
    file.read(string,length);
    PythonReference dumped(PyString_FromStringAndSize(string,length),0);
    PythonReference call(Py_BuildValue("(O)",dumped.get()),0);
    PythonReference result(PyObject_CallObject(loads.get(),call.get()),0);
    tst_free(string);
    return result;
}

class TST;

template <typename iterator_type>
class TSTIterator {
    public:
        friend class TST;
    
        TSTIterator __iter__() {
            return *this;
        }
    
        PyObject* next() {
            typename iterator_type::value_type v(iterator.next());
            if(v.second) {
                return Py_BuildValue("s#O",v.first.data(),v.first.size(),v.second->get());
            }
            else {
                PythonReference exceptions(PyImport_ImportModule("exceptions"),0);
                PythonReference stop_iteration = exceptions.getattr("StopIteration");
                PyErr_SetNone(stop_iteration.get());
                return 0;
            }
        }
    
    private:
        TSTIterator(iterator_type i) : iterator(i) {
        }
        
        iterator_type iterator;
};

typedef TSTIterator<lexical_iterator<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type > > TSTLexicalIterator;
typedef TSTIterator<match_iterator<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type > > TSTCloseMatchIterator;

class TST : public tst<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type > {
public:
    TST() : tst<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type >() {
    }

    virtual ~TST() {
    }

    virtual PythonReference write_to_file(PythonReference file) {
        if(!PyString_CheckExact(file.get())) {
            throw PythonException("Argument of write_to_file() must be a string object");
        }
        std::ofstream out(PyString_AsString(file.get()),std::ofstream::binary|std::ofstream::out|std::ofstream::trunc);
        out.exceptions(std::ofstream::eofbit | std::ofstream::failbit | std::ofstream::badbit);

#ifdef ZIPPED_TREE
        boost::iostreams::filtering_ostream fout;
        fout.push(boost::iostreams::zlib_compressor());
        fout.push(out);
        this->write(fout);
        fout.strict_sync();
#else
        this->write(out);
#endif        
        
        out.close();
        return PythonReference();
    }

    virtual PythonReference read_from_file(PythonReference file) {
        if(!PyString_CheckExact(file.get())) {
            throw PythonException("Argument of read_from_file() must be a string object");
        }
        std::ifstream in(PyString_AsString(file.get()),std::ifstream::binary|std::ifstream::in);
        in.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
        
#ifdef ZIPPED_TREE
        boost::iostreams::filtering_istream fin;
        fin.push(boost::iostreams::zlib_decompressor());
        fin.push(in);
        this->read(fin);
#else
        this->read(in);
#endif        

        in.close();
        return PythonReference();
    }

    PythonReference __getitem__(const string_type& string) {
        return get(string);
    }

    PythonReference __setitem__(const string_type& string,PythonReference data) {
        return put(string,data);
    }

    void __delitem__(const string_type& string) {
        remove(string);
    }

    PythonReference __contains__(const string_type& string) {
        if(contains(string)) {
            return PythonReference(Py_False);
        }
        else {
            return PythonReference(Py_True);
        }
    }
    
    TSTLexicalIterator __iter__() {
        return TSTLexicalIterator(tst<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type >::iterator());
    }

    TSTLexicalIterator iterator() {
        return TSTLexicalIterator(tst<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type >::iterator());
    }

    TSTLexicalIterator iterator(const string_type& string) {
        return TSTLexicalIterator(tst<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type >::iterator(string));
    }

    TSTCloseMatchIterator close_match_iterator(const string_type& string, int distance) {
        return TSTCloseMatchIterator(tst<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type >::close_match_iterator(string,distance));
    }

    using tst<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type >::put; 
    using tst<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type >::get; 
    using tst<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type >::pack; 
    using tst<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type >::walk; 
    using tst<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type >::close_match; 
    using tst<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type >::match; 
    using tst<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type >::scan; 
    using tst<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type >::scan_with_stop_chars;
};
