%module(directors="1") tst

%{
#include "TST.cxx"
%}

%feature("director") action<int>;
%feature("director") action<char*>;
%feature("director") action<PyObject*>;

%include "tst.h"

%template(IntegerTST) tst<int>;
%template(IntegerAction) action<int>;

%template(StringTST) tst<char*>;
%template(StringAction) action<char*>;

%template(_object_tst) tst<PyObject*>;
%template(Action) action<PyObject*>;

%include "TST.cxx"

