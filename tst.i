%module(directors="1") tst

%apply (char *STRING, int LENGTH) { (char *string, int string_length) };

%{
#include "TST.cxx"
%}

%exception {
    try { $action }
    catch (TSTException e) { PyErr_SetString(PyExc_RuntimeError,e.message); SWIG_fail;}
}

%include "tst.h"

%template(_TST)         tst<char,PyObject*>;
%template(_Action)      action<char,PyObject*>;
%template(_Filter)      filter<char,PyObject*>;
%template(_Serializer)  serializer<char,PyObject*>;

%include "TST.cxx"

