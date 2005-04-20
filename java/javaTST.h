#include "tst.h"
#include "jni.h"

class JavaTST : public tst<char,jobject> {
public:
    JavaTST() : tst<char,jobject>(256,NULL) {
    }
};

class Action : public action<char,jobject> {
public:
    Action(jobject target) : action<char,jobject>() {
        this->target=target;
    }

    virtual void perform(char* key,int remaining_distance,jobject data) {
        printf("perform target=%d key=\"%s\" remaining_distance=%d data=%d\n",target,key,remaining_distance,data);
    }

    virtual jobject result() {
        return NULL;
    }

private:
    jobject target;
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