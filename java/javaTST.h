#include "tst.h"
#include "jni.h"

class ObjectTST : public tst<char,jobject> {
public:
    ObjectTST(int initial_size,jobject data,JNIEnv* jenv2) : tst<char,jobject>(initial_size,data) {
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
    virtual jobject store_data(tst_node<char,jobject>* node,jobject data,int want_old_value) {
        printf("store %d\n",data);
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

class ObjectAction : public action<char,jobject> {
public:
    ObjectAction(jobject target,char *perform,char* result,JNIEnv* jenv) : action<char,jobject>() {
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

    virtual void perform(char* key,int remaining_distance,jobject data) {
        if(performID) {
            jstring key_string = jenv->NewStringUTF(key);
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

class ObjectFilter : public filter<char,jobject> {
public:
    ObjectFilter(jobject target,char *perform,JNIEnv* jenv) : filter<char,jobject>() {
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

    virtual jobject perform(char* key,int remaining_distance,jobject data) {
        if(performID) {
            jstring key_string = jenv->NewStringUTF(key);
            if(key_string) {
                return jenv->CallObjectMethod(target,performID,key_string,(jint)remaining_distance,data);
            }
        }
        return NULL;
    }

private:
    JNIEnv* jenv;
    jobject target;
    jmethodID performID;
};

class ObjectSerializer : public serializer<char,jobject> {
public:
    virtual void write(FILE* file,jobject data) {
    }

    virtual jobject read(FILE* file) {
        return NULL;
    }
};

class LongAction : public action<char,long long> {
public:
    LongAction(jobject target,char *perform,char* result,JNIEnv* jenv) : action<char,long long>() {
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

    virtual void perform(char* key,int remaining_distance,long long data) {
        if(performID) {
            jstring key_string = jenv->NewStringUTF(key);
            if(key_string) {
                jenv->CallVoidMethod(target,performID,key_string,(jint)remaining_distance,data);
            }
        }
    }

    virtual long long result() {
        if(resultID) {
            long long result = (long long)jenv->CallLongMethod(target,resultID);
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

class LongFilter : public filter<char,long long> {
public:
    LongFilter(jobject target,char *perform,JNIEnv* jenv) : filter<char,long long>() {
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

    virtual long long perform(char* key,int remaining_distance,long long data) {
        if(performID) {
            jstring key_string = jenv->NewStringUTF(key);
            if(key_string) {
                return (long long)jenv->CallLongMethod(target,performID,key_string,(jint)remaining_distance,data);
            }
        }
        return NULL;
    }

private:
    JNIEnv* jenv;
    jobject target;
    jmethodID performID;
};

class LongSerializer : public serializer<char,long long> {
public:
    virtual void write(FILE* file,long long data) {
        fwrite(&data,sizeof(data),1,file);
    }

    virtual long long read(FILE* file) {
        long long data;
        fread(&data,sizeof(data),1,file);
        return data;
    }
};