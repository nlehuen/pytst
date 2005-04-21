/* 
 # $Id: tst.i 1151 2005-03-31 20:28:27Z nlehuen $
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

%{
#include "javaTST.h"
%}

%include "tst.h"

%typemap(in) (char* result,JNIEnv* jenv) {
    $1 = 0;
    if ($input) {
        $1 = (char *)jenv->GetStringUTFChars($input, 0);
        if (!$1) return $null;
    }
	$2 = jenv;
}

%typemap(in) (jobject data,JNIEnv* jenv2) {
    $1 = (jobject)$input;
	$2 = jenv;
}

%typemap(freearg) (char* result,JNIEnv* jenv) {
	if ($1) jenv->ReleaseStringUTFChars($input, $1); 
}

%template(_ObjectTST) tst<char,jobject>;
%template(_ObjectAction) action<char,jobject>;
%template(_ObjectFilter) filter<char,jobject>;
%template(_ObjectSerializer) serializer<char,jobject>;

%include "javaTST.h"
