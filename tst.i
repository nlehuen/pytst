%module(directors="1") tst

%apply (char *STRING, int LENGTH) { (char *string, int string_length) };

%{
#include "TST.cxx"
%}

%typemap(out) PyObject* {
	Py_INCREF($1);
	$result = $1;
}

%exception {
    try { $action }
    catch (TSTException e) { PyErr_SetString(PyExc_RuntimeError,e.message); SWIG_fail;}
}

%feature("director") tst<PyObject*>;
%feature("director") action<PyObject*>;
%feature("director") filter<PyObject*>;
%feature("director") serializer<PyObject*>;

%feature("director") tst<int>;
%feature("director") action<int>;
%feature("director") filter<int>;
%feature("director") serializer<int>;

%include "tst.h"

%template(_object_tst) tst<PyObject*>;
%template(Action)      action<PyObject*>;
%template(Filter)      filter<PyObject*>;
%template(Serializer)  serializer<PyObject*>;

%template(IntegerTST) tst<int>;
%template(IntegerAction)      action<int>;
%template(IntegerFilter)      filter<int>;
%template(IntegerSerializer)  serializer<int>;

%include "TST.cxx"

