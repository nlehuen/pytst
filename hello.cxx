#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tst.h"

class stringserializer : public serializer<char*> {
    virtual void write(FILE* file,char* data) {
        size_t len=strlen(data);
        fwrite(&len,sizeof(int),1,file);
        fwrite(data,sizeof(char),len,file);
    }

    virtual char* read(FILE* file) {
        size_t len;
        fread(&len,sizeof(size_t),1,file);
        char* data=(char*)malloc((len+1)*sizeof(char));
        fread(data,sizeof(char),len,file);
        data[len]='\0';
        return data;
    }
};

class donothing : public action<char*> {
    public:
        virtual void perform(char* key,int remaining_distance,char* data);
        virtual char* result();
};

void donothing::perform(char* key,int remaining_distance,char* data) {
}

char* donothing::result() {
    return NULL;
}

class printer : public donothing {
    public:
        virtual void perform(char* key,int remaining_distance,char* data);
};

void printer::perform(char* key,int remaining_distance,char* data) {
    printf("%s = %s\n",key,data);
}

int main(int argc,char** argv) {
    tst<char*>* linetst=new tst<char*>(2,NULL);
    tst<size_t>* lengthtst=new tst<size_t>(2,0);
    char* line;
    FILE* input;
    
    printf("Taille d'un noeud char* : %i\n",sizeof(tst_node<char*>));
    printf("Taille d'un noeud size_t : %i\n",sizeof(tst_node<int>));
    
    input = fopen("prenoms.txt","r");
    line = (char*)malloc(256);
    while(fgets(line,256,input)!=NULL) {
        linetst->put(line,line);
        lengthtst->put(line,strlen(line));
        line = (char*)malloc(256);
    }
    fclose(input);

    /*input = fopen("prenoms.txt","r");
    line = (char*)malloc(256);
    while(fgets(line,256,input)!=NULL) {
        printf("%s ==> %s (%i)",line,linetst->get(line),lengthtst->get(line));
        free(line);
        line = (char*)malloc(256);
    }
    fclose(input);
    free(line);*/

    linetst->adjust();
    lengthtst->adjust();
    printf("Taille totale line : %i\n",linetst->bytes_allocated());
    printf("Taille totale length : %i\n",lengthtst->bytes_allocated());

    /*action<char*>* myaction=new donothing();
    linetst->almost("Yohan;H\r\n",(int)strlen("Yohan;H\r\n"),7,NULL,myaction);
    delete myaction;

    myaction=new printer();
    linetst->walk(NULL,myaction);
    linetst->common_prefix("Yohan",NULL,myaction);
    delete myaction;*/
    
    FILE* output=fopen("test.tst","wb");
    if(output==NULL) {
        printf("Impossible d'ouvrir le fichier en écriture\n");
    }
    else {
        stringserializer* sser=new stringserializer();
        linetst->write(output,sser);
        delete sser;
    }
    fclose(output);

    delete linetst;
    delete lengthtst;

    FILE* finput=fopen("test.tst","rb");
    if(finput==NULL) {
        printf("Impossible d'ouvrir le fichier en lecture\n");
    }
    else {
        stringserializer* sser=new stringserializer();
        linetst=new tst<char*>(finput,sser);
        delete sser;

        printf("linetst read from disk\n");

        action<char*>* myaction=new printer();
        linetst->walk(NULL,myaction);
        linetst->common_prefix("Yohan",NULL,myaction);
        delete myaction;

        delete linetst;
    }
    fclose(finput);


    return 0;
}
