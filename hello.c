#include <stdio.h>
#include "tst.h"

void debug(tst* _tst,char *string) {
    printf("%s--->%i\n",string,tst_find_node(_tst,_tst->root,string));
}

int main(int argc,char** argv) {
    tst* mytst=tst_create(1024);
    printf("Hello, world %i, %i\n",&(mytst->array[0]),&(mytst->array[1]));
    printf("Hello, world %i, %i\n",mytst->array,mytst->array+1);
    int i;
    for(i=0;i<100;i++) {
        printf("------------------ %03i\n",i);
        debug(mytst,"Nicolas");
        debug(mytst,"Carine");
        debug(mytst,"Youpila");
        debug(mytst,"Aaaaron");
        debug(mytst,"Nicole");
        debug(mytst,"Tripou");
        debug(mytst,"Carinette");
        debug(mytst,"Fripounette");
        debug(mytst,"Cailloux");
    }
    tst_free(mytst);
    return 0;
}
