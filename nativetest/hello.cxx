#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tst.h"


class stringserializer : public serializer<char,char*> {
    virtual void write(FILE* file,char* data) {
        size_t len=strlen(data);
        fwrite(&len,sizeof(int),1,file);
        fwrite(data,sizeof(char),len,file);
    }

    virtual char* read(FILE* file) {
        size_t len;
        fread(&len,sizeof(size_t),1,file);
        char* data=(char*)tst_malloc((len+1)*sizeof(char));
        fread(data,sizeof(char),len,file);
        data[len]='\0';
        return data;
    }
};

class donothing : public action<char,char*> {
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
            printf("%s = %s (%i)\n",key,data,remaining_distance);
        }
};

class stringtst : public tst<char,char*> {
    public:
        stringtst() : tst<char,char*>(16,NULL) {
        }

        virtual ~stringtst() {
            clear_nodes();
        }

        stringtst(FILE* file) : tst<char,char*>() {
            stringserializer* s=new stringserializer();
            read(file,s);
            delete s;
        }

    protected:
       virtual void store_data(tst_node<char,char*>* node,char* data);
};

class tester : public donothing {
    public:
        tester(tst<char,char*>* mytst) : donothing() {
            this->mytst=mytst;
        }

        virtual void perform(char* key,int remaining_distance,char* data) {
            donothing* dn = new donothing();
            mytst->almost(key,strlen(key),3,NULL,dn);
            mytst->common_prefix(key,NULL,dn);
            delete dn;
        }

    private:
        tst<char,char*>* mytst;
};


void stringtst::store_data(tst_node<char,char*>* node,char* data) {
            // printf("sd %x %x %x %s\n",(int)node,(int)node->data,node->c,data);
            if(node->data) {
                // printf("freeing %x\n",(int)node->data);
                tst_free(node->data);
            }
            node->data=data;
        }

int main(int argc,char** argv) {
    printf("Taille d'un noeud char* : %i\n",sizeof(tst_node<char,char*>));
    printf("Taille d'un noeud size_t : %i\n",sizeof(tst_node<char,int>));

    tst<char,char*>* linetst=new tst<char,char*>(16,"<nothing>");
    linetst->put("abc","abc");
    linetst->put("abcdef","abcdef");
    linetst->put("01","01");
    printf("%s\n",linetst->get("abc"));
    printf("%s\n",linetst->get("01"));
    printf("%s\n",linetst->get("foobar"));

    printer p=printer();
    linetst->walk(NULL,&p);

    printf("-----------------------\n");
    linetst->scan("abc",&p);
    printf("-----------------------\n");
    linetst->scan("01",&p);
    printf("-----------------------\n");
    linetst->scan("abc01",&p);
    printf("-----------------------\n");
    linetst->scan("abc---01",&p);
    printf("-----------------------\n");
    linetst->scan("abcdef---abc--01--abcdef--abc",&p);
    printf("-----------------------\n");
    linetst->scan("--abcdef---abc--01--abcdef--abc01",&p);
    printf("-----------------------\n");
    linetst->scan("--abcdef---abc--01--abcdef--abc01--",&p);

    for(int hhk=0;hhk<10;hhk++) {
    printf("---- suppressions ---\n");
    linetst->walk(NULL,&p);
    printf("01 =>\n");
    linetst->remove("01");
    linetst->walk(NULL,&p);
    printf("abcdef =>\n");
    linetst->remove("abcdef");
    linetst->walk(NULL,&p);
    printf("abc =>\n");
    linetst->remove("abc");
    linetst->walk(NULL,&p);
    printf("---- suppressions ---\n");

    linetst->debug_print_root();

    char* buffer=(char*)malloc(256*sizeof(char));
    sprintf(buffer,"new abc %i",hhk);
    printf("---- ajout ---\n");
    linetst->put("abcdef",buffer);
    linetst->put("abc","new abc");
    linetst->put("01","new 01");
    linetst->walk(NULL,&p);
    printf("---- ajout ---\n");

    linetst->debug_print_root();
    }
    delete linetst;

    return 0;
}

int main3(int argc,char** argv) {
    printf("Taille d'un noeud char* : %i\n",sizeof(tst_node<char,char*>));
    printf("Taille d'un noeud size_t : %i\n",sizeof(tst_node<char,int>));

    for(int i=0;i<10;i++) {
        tst<char,char*>* linetst=new stringtst();
        tst<char,size_t>* lengthtst=new tst<char,size_t>(16,0);
        char* line;
        FILE* input;

        input = fopen("..\\..\\prenoms.txt","r");
        
        if(input==NULL) {
            printf("Impossible d'ouvrir le fichier prenoms.txt\n");
            return 1;
        }
        
        line = (char*)tst_malloc(256);
        while(fgets(line,256,input)!=NULL) {
            linetst->put(line,line);
            lengthtst->put(line,strlen(line));
            line = (char*)tst_malloc(256);
        }
        fclose(input);
        tst_free(line);

        tester* t=new tester(linetst);
        linetst->walk(NULL,t);
        delete t;

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

        printf("%s",linetst->get("Nicolas;H\n"));

        printf("On delete...\n");

        delete linetst;

        printf("OK pour linetst\n");

        delete lengthtst;

        printf("OK pour lengthtst\n");

        FILE* finput=fopen("test.tst","rb");
        if(finput==NULL) {
            printf("Impossible d'ouvrir le fichier en lecture\n");
        }
        else {
            linetst=new stringtst(finput);

            printf("linetst read from disk\n");

            action<char,char*>* myaction=new donothing();
            linetst->walk(NULL,myaction);
            linetst->common_prefix("Yohan",NULL,myaction);
            linetst->almost("Yohan",5,4,NULL,myaction);
            delete myaction;

            delete linetst;
            fclose(finput);
        }
    }

    return 0;
}
