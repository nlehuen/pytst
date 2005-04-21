#include "tst.h"
#include "jni.h"

class ObjectTST : public tst<char,jobject> {
public:
    ObjectTST(jobject data,JNIEnv* jenv2) : tst<char,jobject>(256,data) {
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
    virtual jobject perform(char* key,int remaining_distance,jobject data) {
        return NULL;
    }
};

class ObjectSerializer : public serializer<char,jobject> {
public:
    virtual void write(FILE* file,jobject data) {
    }

    virtual jobject read(FILE* file) {
        return NULL;
    }
};