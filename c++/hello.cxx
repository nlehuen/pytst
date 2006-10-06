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
#include <time.h>

#define SCANNER
#include "tst.h"

class stringserializer {
public:
    void write(FILE* file,char* data) {
        if(data) {
            size_t len=strlen(data);
            fwrite(&len,sizeof(int),1,file);
            fwrite(data,sizeof(char),len,file);
        }
        else {
            size_t len=0;
            fwrite(&len,sizeof(int),1,file);
        }
    }

    char* read(FILE* file) {
        size_t len;
        fread(&len,sizeof(size_t),1,file);
        if(len>0) {
            char* data=(char*)tst_malloc((len+1)*sizeof(char));
            fread(data,sizeof(char),len,file);
            data[len]='\0';
            return data;
        }
        else {
            return 0;
        }
    }
};

class donothing : public tst_action<char,char*> {
    public:
        virtual void perform(const char* string,int string_length,int remaining_distance,char* data) {}
        virtual char* result() { return 0; }
};

class printer : public donothing {
    public:
        virtual void perform(const char* key,int remaining_distance,char* data) {
            printf("%s = %s (%i)\n",key,data,remaining_distance);
        }
};

typedef memory_storage<char,char*> memory_storage_char_string;
typedef tst<char,char*,memory_storage_char_string,stringserializer> stringtst;

class tester : public donothing {
    public:
        tester(stringtst* mytst) : donothing() {
            this->mytst=mytst;
        }

        virtual void perform(const char* string,int string_length,int remaining_distance,char* data) {
            donothing* dn = new donothing();
            mytst->close_match(string,string_length,3,0,dn);
            mytst->prefix_match(string,string_length,0,dn);
            delete dn;
        }

    private:
        stringtst* mytst;
};

#define ITERATIONS 10000

int main(int argc,char** argv) {
    memory_storage_char_string* storage = new memory_storage_char_string(8);
    stringtst* linetst=new stringtst(storage,0);

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
        char* line=(char*)malloc(10);
        sprintf(line,"%d\0",i);
        linetst->put(line,(int)strlen(line),line);
    }

    end = clock();
    elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Write : %f\n",elapsed);

    linetst->pack();

    start = clock();
    for(int i=ITERATIONS-1;i>=0;i--) {
        char line[256];
        sprintf(line,"%d\0",i);
        char *result=linetst->get(line,(int)strlen(line));
        assert(result);
        assert(strcmp(line,result)==0);
    }
    end = clock();
    elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Read : %f\n",elapsed);

    start = clock();
    FILE* output=fopen("test.dump","wb");
    linetst->write(output);
    fclose(output);
    end = clock();
    elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Wrote to disk : %f\n",elapsed);

    memory_storage_char_string* storage2 = new memory_storage_char_string(1);
    stringtst* linetst2=new stringtst(storage2,0);
    start = clock();
    FILE* input=fopen("test.dump","rb");
    linetst2->read(input);
    fclose(input);
    end = clock();
    elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Read from disk : %f\n",elapsed);

    start = clock();
    for(int i=ITERATIONS-1;i>=0;i--) {
        char line[256];
        sprintf(line,"%d\0",i);
        char *result=linetst->get(line,(int)strlen(line));
        assert(result);
        assert(strcmp(line,result)==0);
    }
    end = clock();
    elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Read : %f\n",elapsed);

    {
	    lexical_iterator<char,char*,memory_storage_char_string,stringserializer> fg = linetst->iterator("123",3);
        while(true) {
            lexical_iterator<char,char*,memory_storage_char_string,stringserializer>::value_type v=fg.next();
            if(v.second) {
                printf("%s\n",v.first.c_str());
            }
            else {
                break;
            }
        }
    }

    {
        match_iterator<char,char*,memory_storage_char_string,stringserializer> fg = linetst->close_match_iterator("1",1,2);
        while(true) {
            match_iterator<char,char*,memory_storage_char_string,stringserializer>::value_type v=fg.next();
            if(v.second) {
                printf("%s\n",v.first.c_str());
            }
            else {
                break;
            }
        }
    }

    printf("OK !\n");
    getchar();

    return 0;
}
