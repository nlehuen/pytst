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
        debug(mytst,"a%i");
        debug(mytst,"b%i");
        debug(mytst,"c%i");
        debug(mytst,"d%i");
        debug(mytst,"e%i");
        debug(mytst,"f%i");
        debug(mytst,"g%i");
        debug(mytst,"h%i");
        debug(mytst,"i%i");
        debug(mytst,"j%i");
        tst_debug_node(mytst->array,mytst->array+mytst->root);
        printf("\nbalance\n");
        do {
            flag=0;
            tst_balance(mytst,&flag);
        } while(flag==1);
        tst_debug_node(mytst->array,mytst->array+mytst->root);
        printf("\n");
    }
    tst_free(mytst);
    return 0;
}
