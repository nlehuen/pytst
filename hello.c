#include <stdlib.h>
#include <stdio.h>
#include "tst.h"

void debug(struct tst* _tst,char *string) {
    printf("%s--->%i\n",string,tst_find_node(_tst,_tst->root,string));
}

int main(int argc,char** argv) {
    struct tst* mytst=tst_create(2);
    int i;
    for(i=0;i<2;i++) {
        printf("------------------ %03i\n",i);
        debug(mytst,"Nicolas");
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
