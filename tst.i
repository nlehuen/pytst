%module tst

%{
#include "tst.h"
%}

%include "tst.h"

%template(int_tst) tst<int>;
%template(string_tst) tst<char*>;
%template(object_tst) tst<PyObject*>;

%typemap(in) PyObject* {
	Py_INCREF($input);
	$1=$input;
}
