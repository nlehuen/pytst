%module(directors="1") tst

%apply (char *STRING, int LENGTH) { (char *string, int string_length) };

%{
#include "TST.cxx"
%}

%exception {
    try { $action }
    catch (TSTException e) { PyErr_SetString(PyExc_RuntimeError,e.message); SWIG_fail;}
}

%feature("director") action<int>;
%feature("director") action<char*>;
%feature("director") action<PyObject*>;
%feature("director") Action;
%feature("director") filter<int>;
%feature("director") filter<char*>;
%feature("director") filter<PyObject*>;
%feature("director") serializer<PyObject*>;

%include "tst.h"

%template(IntegerTST) tst<int>;
%template(IntegerAction) action<int>;
%template(IntegerFilter) filter<int>;

/*%template(StringTST) tst<char*>;
%template(StringAction) action<char*>;
%template(StringFilter) filter<char*>;*/

%template(_object_tst) tst<PyObject*>;
%template(Action) action<PyObject*>;
%template(Filter) filter<PyObject*>;
%template(Serializer) serializer<PyObject*>;

%include "TST.cxx"

