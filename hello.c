#include <stdlib.h>
#include <stdio.h>
#include "tst.h"

void debug(struct tst* _tst,char *string) {
	tst_node* root_node=_tst->array+_tst->root;
    printf("%s--->%i==%i\n"
        ,string
        ,tst_build_node(_tst,&root_node,&(_tst->root),string)
        ,tst_find_node(_tst,_tst->root,string));
}

int main(int argc,char** argv) {
    struct tst* mytst=tst_create(2);
    int i;
    for(i=0;i<3;i++) {
        printf("root:%i\n",mytst->root);
        printf("------------------ %03i\n",i);
        debug(mytst,"a");
        debug(mytst,"b");
        debug(mytst,"c");
        debug(mytst,"d");
        debug(mytst,"e");
        debug(mytst,"f");
        debug(mytst,"g");
        debug(mytst,"h");
        debug(mytst,"i");
        debug(mytst,"j");
        debug(mytst,"k");
        debug(mytst,"l");
        debug(mytst,"m");
        debug(mytst,"n");
        debug(mytst,"o");
        debug(mytst,"p");
        debug(mytst,"q");
        debug(mytst,"nicolas");
        debug(mytst,"trevor");
        debug(mytst,"carine");
        debug(mytst,"pascal");
        debug(mytst,"adeline");
        debug(mytst,"amelie");
        debug(mytst,"amelie");
        tst_debug_node(mytst->array,mytst->array+mytst->root);
        printf("\n");
    }
    tst_free(mytst);
    return 0;
}
