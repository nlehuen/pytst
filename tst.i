%module(directors="1") tst

%apply (char *STRING, int LENGTH) { (char *string, int string_length) };

%{
#include "TST.cxx"
%}






%exception {
    try { $action }
    catch (TSTException e) { PyErr_SetString(PyExc_RuntimeError,e.message); SWIG_fail;}
}

%feature("director") action<PyObject*>;
%feature("director") filter<PyObject*>;
%feature("director") serializer<PyObject*>;

%include "tst.h"

%template(_TST)         tst<PyObject*>;
%template(_Action)      action<PyObject*>;
%template(_Filter)      filter<PyObject*>;
%template(_Serializer)  serializer<PyObject*>;

%include "TST.cxx"

