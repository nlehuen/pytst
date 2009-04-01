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
%module tst

%feature("autodoc", "1");

%typemap(in) PythonReference {
   $1 = PythonReference($input);
}

%typemap(out) PythonReference {
   $result = $1.lend();
}

%typemap(in) const string_type&, string_type& {
    char* buffer;
    Py_ssize_t size;
    PyString_AsStringAndSize($input,&buffer,&size);
    $1 = new string_type(buffer,size);
}

%typemap(freearg) const string_type&, string_type& {
    delete $1;
}

%typemap(out) const string_type&, string_type& {
    $result = PyString_FromStringAndSize($1.data(),$1.size());
}

%typemap(ret) const string_type&, string_type& {
    delete $1;
}

%exception {
    try { $action }
    catch (TSTException &e) {
        PyErr_SetString(PyExc_RuntimeError,e.what());
        SWIG_fail;
    }
    catch (PythonException &e) {
        if(!PyErr_Occurred()) {
            PyErr_SetString(PyExc_RuntimeError,e.what());
        }
        SWIG_fail;
    }
}

#define __PYTHON__BUILD__
%include "tst.h"
%include "fundamentals.h"
%include "iterators.h"
%include "memory_storage.h"

%template(_TST) tst<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type >;
%template(_Action) tst_action<char,PythonReference,string_type >;
%template(_Filter) tst_filter<char,PythonReference,string_type >;

%include "pythonTST.h"

%template(_lexical_iterator_type) lexical_iterator<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type >;
%template(_close_match_iterator_type) match_iterator<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type >;
%template(TSTLexicalIterator)    TSTIterator<lexical_iterator<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type > >;
%template(TSTCloseMatchIterator) TSTIterator<match_iterator<char,PythonReference,memory_storage<char,PythonReference>,ObjectSerializer,string_type > >;

%{
#include "pythonTST.h"
%}
