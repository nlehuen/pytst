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
        virtual void perform(char* key,int remaining_distance,char* data) {
            LOG2("%s = %s\n",key,data);
        }
};

class stringtst : public tst<char*> {
    public:
        stringtst() : tst<char*>(16,NULL){
        }
        
        stringtst(FILE* file) : tst<char*>() {
            stringserializer* s=new stringserializer();
            read(file,s);
            delete s;
        }

        virtual void store_data(tst_node<char*>* node,char* data) {
            if(node->data) {
                printf("freeing %x\n",(int)node->data);
                free(node->data);
            }
            node->data=data;
        }
};

int main(int argc,char** argv) {
    printf("Taille d'un noeud char* : %i\n",sizeof(tst_node<char*>));
    printf("Taille d'un noeud size_t : %i\n",sizeof(tst_node<int>));
    
    for(int i=0;i<1000;i++) {
        tst<char*>* linetst=new stringtst();
        tst<size_t>* lengthtst=new tst<size_t>(16,0);
        char* line;
        FILE* input;

        input = fopen("prenoms.txt","r");
        line = (char*)malloc(256);
        while(fgets(line,256,input)!=NULL) {
            linetst->put(line,line);
            lengthtst->put(line,strlen(line));
            line = (char*)malloc(256);
        }
        fclose(input);
        free(line);

        linetst->adjust();
        lengthtst->adjust();
        printf("Taille totale line : %i\n",linetst->bytes_allocated());
        printf("Taille totale length : %i\n",lengthtst->bytes_allocated());

        FILE* output=fopen("test.tst","wb");
        if(output==NULL) {
            printf("Impossible d'ouvrir le fichier en écriture\n");
        }
        else {
            stringserializer* sser=new stringserializer();
            linetst->write(output,sser);
            delete sser;
            fclose(output);
        }

        printf("On delete...\n");

        delete linetst;

        printf("OK pour linetst\n");

        delete lengthtst;

        FILE* finput=fopen("test.tst","rb");
        if(finput==NULL) {
            printf("Impossible d'ouvrir le fichier en lecture\n");
        }
        else {
            linetst=new stringtst(finput);

            printf("linetst read from disk\n");

            action<char*>* myaction=new donothing();
            linetst->walk(NULL,myaction);
            linetst->common_prefix("Yohan",NULL,myaction);
            delete myaction;

            delete linetst;
            fclose(finput);
        }
    }

    return 0;
}
