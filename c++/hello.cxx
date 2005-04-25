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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tst.h"
#include <time.h>

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
        virtual void perform(char* string,int string_length,int remaining_distance,char* data) {}
        virtual char* result() { return NULL; }
};

class printer : public donothing {
    public:
        virtual void perform(char* key,int remaining_distance,char* data) {
            printf("%s = %s (%i)\n",key,data,remaining_distance);
        }
};

typedef memory_storage<char,char*> memory_storage_char_string;

class stringtst : public tst<char,char*,memory_storage_char_string> {
    public:
        stringtst() : tst<char,char*,memory_storage_char_string>(new memory_storage_char_string(1600),NULL) {
        }

        stringtst(FILE* file) : tst<char,char*,memory_storage_char_string>() {
            stringserializer* s=new stringserializer();
            read(file,s);
            delete s;
        }

    protected:
       virtual void store_data(tst_node<char,char*>* node,char* data);
};

void stringtst::store_data(tst_node<char,char*>* node,char* data) {
            // printf("sd %x %x %x %s\n",(int)node,(int)node->data,node->c,data);
            if(node->data) {
                // printf("freeing %x\n",(int)node->data);
                tst_free(node->data);
            }
            node->data=data;
        }

class tester : public donothing {
    public:
        tester(stringtst* mytst) : donothing() {
            this->mytst=mytst;
        }

        virtual void perform(char* string,int string_length,int remaining_distance,char* data) {
            donothing* dn = new donothing();
            mytst->almost(string,string_length,3,NULL,dn);
            mytst->common_prefix(string,string_length,NULL,dn);
            delete dn;
        }

    private:
        stringtst* mytst;
};

#define ITERATIONS 4000000

int main2(int argc,char** argv) {
    stringtst* linetst=new stringtst();

    clock_t start, end;
    double elapsed;



    start = clock();
    for(int i=0;i<ITERATIONS;i++) {
        char* line=(char*)malloc(10);
        sprintf(line,"%d\0",i);
        free(line);




    }
    end = clock();
    elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Build : %f\n",elapsed);

    start = clock();
    for(int i=0;i<ITERATIONS;i++) {
//    for(int i=ITERATIONS-1;i>=0;i--) {
        char* line=(char*)malloc(10);
        sprintf(line,"%d\0",i);
        linetst->put(line,strlen(line),line);
    }

    end = clock();
    elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Write : %f\n",elapsed);

    linetst->pack();

    /*printer p;
    linetst->walk(NULL,&p);
    char line[256];    
    printf("OK...");
    getchar();*/

    start = clock();
    for(int i=ITERATIONS-1;i>=0;i--) {
//    for(int i=0;i<ITERATIONS;i++) {
        char line[256];
        sprintf(line,"%d\0",i);
        // printf("%s\n",line);
        char *result=linetst->get(line,strlen(line));
        assert(result);
        assert(strcmp(line,result)==0);
    }


    end = clock();
    elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Read : %f\n",elapsed);


    return 0;
}

typedef memory_storage<char,int> memory_storage_char_int;

int main(int argc,char **argv) {
    tst<char,int,memory_storage_char_int> md5tst(new memory_storage_char_int(256),0L);
    clock_t start, end;
    double elapsed;
    FILE* input;
    int lines;

    start = clock();
    lines = 0;
    input = fopen("url-list.txt","r");
    while(true) {
        char line[256];
        fscanf(input,"%s\n",line);
        md5tst.put(line,strlen(line),1L);
        if(lines++%1000==0) {
            printf("%d\n",lines);
        }
        if(lines==100000) {
            break;
        }
    }
    fclose(input);
    end=clock();
    elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Load : %f\n",elapsed);

    start = clock();
    input = fopen("url-list.txt","r");
    lines=0;
    while(true) {
        char line[256];
        fscanf(input,"%s\n",line);
        if(md5tst.get(line,strlen(line))!=1L) {
            printf("Bummer ! %d %s\n",lines++,line);
            return 1;
        }
        if(lines==100000) {
            break;
        }
    }
    fclose(input);
    end=clock();
    elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Read : %f\n",elapsed);

    return 0;
}