#include <stdlib.h>
#include <stdio.h>
#include "tst.h"

int main(int argc,char** argv) {
    tst* mytst=new tst(2);
    char* line;
    FILE* input;
    
    printf("Taille d'un noeud : %i\n",sizeof(tst_node));
    
    input = fopen("prenoms.txt","r");
    line = (char*)malloc(256);
    while(fgets(line,256,input)!=NULL) {
        mytst->put(line,(PyObject*)line);
        line = (char*)malloc(256);
    }
    fclose(input);

    input = fopen("prenoms.txt","r");
    line = (char*)malloc(256);
    while(fgets(line,256,input)!=NULL) {
        printf("%s ==> %s",line,(char*)mytst->get(line));
        free(line);
        line = (char*)malloc(256);
    }
    fclose(input);
    free(line);

    /*printf("Taille de l'arbre ; %i utilises, %i alloues\n",mytst->next,mytst->size);
    printf("Taille de l'arbre ; %i\n",mytst->size*sizeof(tst_node));
    tst_adjust_size(mytst);
    printf("Taille de l'arbre ajuste ; %i\n",mytst->size*sizeof(tst_node));*/

    mytst -> debug();

    delete mytst;
    return 0;
}
