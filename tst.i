%module(directors="1") tst

%apply (char *STRING, int LENGTH) { (char *string, int string_length) };

%{
#include "TST.cxx"
%}

%exception {
    try { $action }
    catch (TSTException e) { PyErr_SetString(PyExc_RuntimeError,e.message); SWIG_fail;}
}

%feature("director") tst<PyObject*>;
%feature("director") action<PyObject*>;
%feature("director") filter<PyObject*>;
%feature("director") serializer<PyObject*>;

%include "tst.h"

%template(_object_tst) tst<PyObject*>;
%template(Action)      action<PyObject*>;
%template(Filter)      filter<PyObject*>;
%template(Serializer)  serializer<PyObject*>;

%typemap(out) PyObject* {
	Py_INCREF($1);
	$result = $1;
}

%include "TST.cxx"

