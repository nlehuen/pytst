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

%typemap(jni) jchar *, jchar[ANY], jchar[]               "jstring"
%typemap(jtype) jchar *, jchar[ANY], jchar[]               "String"
%typemap(jstype) jchar *, jchar[ANY], jchar[]               "String"
%typemap(javain) jchar *, jchar[ANY], jchar[] "$javainput"

%{
#include "javaTST.h"
%}

%include "tst.h"

%typemap(in) (char* result,JNIEnv* jenv),(char* perform,JNIEnv* jenv) {
    $1 = 0;
    if ($input) {
        $1 = (char *)jenv->GetStringUTFChars($input, 0);
        if (!$1) return $null;
    }
	$2 = jenv;
}

%typemap(in) (jchar* string,int string_length),(jchar* stop_chars,int stop_chars_length) {
    $1 = 0;
    if ($input) {
        $1 = (jchar*)jenv->GetStringChars((jstring)$input, 0);
        if (!$1) return $null;
        $2 = jenv->GetStringLength((jstring)$input);
    }
}

%typemap(in) (jobject data,JNIEnv* jenv2) {
    $1 = (jobject)$input;
	$2 = jenv;
}

%typemap(freearg) (char* result,JNIEnv* jenv),(char* perform,JNIEnv* jenv) {
	if ($1) jenv->ReleaseStringUTFChars($input, $1); 
}

%typemap(freearg) (jchar* string,int string_length),(jchar* stop_chars,int stop_chars_length) {
	if ($1) jenv->ReleaseStringChars((jstring)$input, $1);
}

typedef memory_storage<jchar,jlong> java_long_memory_storage;

%template(_ObjectMemoryStorage) memory_storage<jchar,jobject>;
%template(_ObjectTST) tst<jchar,jobject,ObjectMemoryStorage>;
%template(_ObjectAction) action<jchar,jobject>;
%template(_ObjectFilter) filter<jchar,jobject>;
%template(_ObjectSerializer) serializer<jchar,jobject>;

%template(_LongMemoryStorage) memory_storage<jchar,jlong>;
%template(_LongTST) tst<jchar,jlong,java_long_memory_storage>;
%template(_LongAction) action<jchar,jlong>;
%template(_LongFilter) filter<jchar,jlong>;
%template(_LongSerializer) serializer<jchar,jlong>;

%include "javaTST.h"
