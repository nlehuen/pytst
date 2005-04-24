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
#include "tst.h"
#include "jni.h"

typedef memory_storage<jchar,jobject> java_object_memory_storage;
typedef memory_storage<jchar,jlong> java_long_memory_storage;

class ObjectTST : public tst<jchar,jobject,java_object_memory_storage> {
public:
    ObjectTST(int initial_size,jobject data,JNIEnv* jenv2) : tst<jchar,jobject,java_object_memory_storage>(new java_object_memory_storage(initial_size),data) {
        jenv = jenv2;
        if(data) {
            jenv->NewGlobalRef(data);
        }
    }

    ~ObjectTST() {
        if(default_value) {
            jenv->DeleteGlobalRef(default_value);
        }
    }
protected:
    virtual jobject store_data(tst_node<jchar,jobject>* node,jobject data,int want_old_value) {
        jobject old_data = node->data;
        if(old_data!=default_value) {
            jenv->DeleteGlobalRef(old_data);
        }
        if(data!=default_value) {
            data = jenv->NewGlobalRef(data);
            node->data = data;
        }
        else {
            data=default_value;
        }
        return old_data;
    }
private:
    JNIEnv* jenv;
};

class ObjectAction : public action<jchar,jobject> {
public:
    ObjectAction(jobject target,char *perform,char* result,JNIEnv* jenv) : action<jchar,jobject>() {
        this->jenv=jenv;
        this->target=jenv->NewGlobalRef(target);
        jclass clazz = jenv->GetObjectClass(this->target);
        if(clazz) {
            if(perform) {
                this->performID = jenv->GetMethodID(clazz,perform,"(Ljava/lang/String;ILjava/lang/Object;)V");
                if(!this->performID) return;
            }
            else {
                this->performID=0;
            }
            if(result) {
                this->resultID = jenv->GetMethodID(clazz,result,"()Ljava/lang/Object;");
                if(!this->resultID) return;
            }
            else {
                this->resultID=0;
            }
        }
    }

    ~ObjectAction() {
        jenv->DeleteGlobalRef(target);
    }

    virtual void perform(jchar* string,int string_length,int remaining_distance,jobject data) {
        if(performID) {
            jstring key_string = jenv->NewString(string,string_length);
            if(key_string) {
                jenv->CallVoidMethod(target,performID,key_string,(jint)remaining_distance,data);
            }
        }
    }

    virtual jobject result() {
        if(resultID) {
            jobject result = jenv->CallObjectMethod(target,resultID);
            return result;
        }
        else {
            return NULL;
        }
    }

private:
    JNIEnv* jenv;
    jobject target;
    jmethodID performID,resultID;
};

class ObjectFilter : public filter<jchar,jobject> {
public:
    ObjectFilter(jobject target,char *perform,JNIEnv* jenv) : filter<jchar,jobject>() {
        this->jenv=jenv;
        this->target=jenv->NewGlobalRef(target);
        jclass clazz = jenv->GetObjectClass(this->target);
        if(clazz) {
            if(perform) {
                this->performID = jenv->GetMethodID(clazz,perform,"(Ljava/lang/String;ILjava/lang/Object;)Ljava/lang/Object;");
                if(!this->performID) return;
            }
            else {
                this->performID=0;
            }
        }
    }

    ~ObjectFilter() {
        jenv->DeleteGlobalRef(target);
    }

    virtual jobject perform(jchar* string,int string_length,int remaining_distance,jobject data) {
        jobject result=NULL;

        if(performID) {
            jstring key_string = jenv->NewString(string,string_length);
            if(key_string) {
                result = jenv->CallObjectMethod(target,performID,key_string,(jint)remaining_distance,data);
            }
        }

        return result;
    }

private:
    JNIEnv* jenv;
    jobject target;
    jmethodID performID;
};

class ObjectSerializer : public serializer<jchar,jobject> {
public:
    virtual void write(FILE* file,jobject data) {
    }

    virtual jobject read(FILE* file) {
        return NULL;
    }
};

class LongTST : public tst<jchar,jlong,java_long_memory_storage> {
public:
    LongTST(int initial_size,jlong data) : tst<jchar,jlong,java_long_memory_storage>(new java_long_memory_storage(initial_size),data) {
    }
};

class LongAction : public action<jchar,jlong> {
public:
    LongAction(jobject target,char *perform,char* result,JNIEnv* jenv) : action<jchar,jlong>() {
        this->jenv=jenv;
        this->target=jenv->NewGlobalRef(target);
        jclass clazz = jenv->GetObjectClass(this->target);
        if(clazz) {
            if(perform) {
                this->performID = jenv->GetMethodID(clazz,perform,"(Ljava/lang/String;IJ)V");
                if(!this->performID) return;
            }
            else {
                this->performID=0;
            }
            if(result) {
                this->resultID = jenv->GetMethodID(clazz,result,"()J");
                if(!this->resultID) return;
            }
            else {
                this->resultID=0;
            }
        }
    }

    ~LongAction() {
        jenv->DeleteGlobalRef(target);
    }

    virtual void perform(jchar* string,int string_length,int remaining_distance,jlong data) {
        if(performID) {
            jstring key_string = jenv->NewString(string,string_length);
            if(key_string) {
                jenv->CallVoidMethod(target,performID,key_string,(jint)remaining_distance,data);
            }
        }
    }

    virtual jlong result() {
        if(resultID) {
            jlong result = (jlong)jenv->CallLongMethod(target,resultID);
            return result;
        }
        else {
            return NULL;
        }
    }

private:
    JNIEnv* jenv;
    jobject target;
    jmethodID performID,resultID;
};

class LongFilter : public filter<jchar,jlong> {
public:
    LongFilter(jobject target,char *perform,JNIEnv* jenv) : filter<jchar,jlong>() {
        this->jenv=jenv;
        this->target=jenv->NewGlobalRef(target);
        jclass clazz = jenv->GetObjectClass(this->target);
        if(clazz) {
            if(perform) {
                this->performID = jenv->GetMethodID(clazz,perform,"(Ljava/lang/String;IJ)J");
                if(!this->performID) return;
            }
            else {
                this->performID=0;
            }
        }
    }

    ~LongFilter() {
        jenv->DeleteGlobalRef(target);
    }

    virtual jlong perform(jchar* string,int string_length,int remaining_distance,jlong data) {
        jlong result = NULL;

        if(performID) {
            jstring key_string = jenv->NewString(string,string_length);
            if(key_string) {
                result = (jlong)jenv->CallLongMethod(target,performID,key_string,(jint)remaining_distance,data);
            }
        }

        return result;
    }

private:
    JNIEnv* jenv;
    jobject target;
    jmethodID performID;
};

class LongSerializer : public serializer<jchar,jlong> {
public:
    virtual void write(FILE* file,jlong data) {
        fwrite(&data,sizeof(data),1,file);
    }

    virtual jlong read(FILE* file) {
        jlong data;
        fread(&data,sizeof(data),1,file);
        return data;
    }
};