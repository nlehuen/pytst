#include <stdlib.h>
#include <stdio.h>
#include "tst.h"

void debug(struct tst* _tst,char *string) {
    printf("%s--->%i\n",string,tst_find_node(_tst,_tst->root,string));
}

int main(int argc,char** argv) {
    struct tst* mytst=tst_create(2);
    int i,flag;
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
        tst_debug_node(mytst,mytst->array+mytst->root);
        printf("\nbalance\n");
        do {
            flag=0;
            tst_balance(mytst,&flag);
        } while(flag==1);
        tst_debug_node(mytst,mytst->array+mytst->root);
        printf("\n");
    }
    tst_free(mytst);
    return 0;
}
