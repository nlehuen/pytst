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

%apply (char *STRING, int LENGTH) { (char *string, int string_length) };
%apply (char *STRING, int LENGTH) { (char *stop_chars, int stop_chars_length) };

%typemap(in) PythonReference {
   $1 = PythonReference($input);
}
%typemap(out) PythonReference {
   $result = $1.lend();
}

%exception {
    try { $action }
    catch (TSTException e) { PyErr_SetString(PyExc_RuntimeError,e.message); SWIG_fail;}
}

#define __PYTHON__BUILD__
%include "tst.h"

%template(_TST)         tst<char,PythonReference,MemoryStorage>;
%template(_Action)      action<char,PythonReference>;
%template(_Filter)      filter<char,PythonReference>;
%template(_Serializer)  serializer<char,PythonReference>;

%include "pythonTST.h"

%{
#include "pythonTST.h"
%}