%module tst

%{
#include "TST.cxx"
%}

%include "tst.h"

%template(IntegerTST) tst<int>;
%template(StringTST) tst<char*>;
%template(_object_tst) tst<PyObject*>;

%include "TST.cxx"

