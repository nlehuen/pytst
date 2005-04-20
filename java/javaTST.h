#include "tst.h"
#include "jni.h"

class JavaTST : public tst<char,jobject> {
public:
    JavaTST(jobject data,JNIEnv* jenv2) : tst<char,jobject>(256,data) {
        this->jenv = jenv;
    }
protected:
    virtual jobject store_data(tst_node<char,jobject>* node,jobject data,int want_old_value) {
        printf("Store %d\n",data);
        jobject old_data = node->data;
        if(old_data!=default_value && want_old_value==0) {
            printf("delete %d...",old_data);
            jenv->DeleteGlobalRef(old_data);
            printf("OK\n");
        }
        printf("New %d...",data);
        node->data = jenv->NewGlobalRef(data);
        printf("OK\n");
        return old_data;
    }
private:
    JNIEnv* jenv;
};

class Action : public action<char,jobject> {
public:
    Action(jobject target,char *perform,char* result,JNIEnv* jenv) : action<char,jobject>() {
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

    ~Action() {
        jenv->DeleteGlobalRef(target);
    }

    virtual void perform(char* key,int remaining_distance,jobject data) {
        printf("perform jenv=%d target=%d methodID=%d key=\"%s\" remaining_distance=%d data=%d\n",jenv,target,performID,key,remaining_distance,data);
        
        if(performID) {
            jstring key_string = jenv->NewStringUTF(key);
            if(key_string) {
                jenv->CallVoidMethod(target,performID,key_string,(jint)remaining_distance,data);
            }
        }
    }

    virtual jobject result() {
        printf("result jenv=%d target=%d methodID=%d\n",jenv,target,resultID);

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

class Filter : public filter<char,jobject> {
public:
    virtual jobject perform(char* key,int remaining_distance,jobject data) {
        return NULL;
    }
};

class Serializer : public serializer<char,jobject> {
public:
    virtual void write(FILE* file,jobject data) {
    }

    virtual jobject read(FILE* file) {
        return NULL;
    }
};