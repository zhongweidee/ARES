//#define _GNU_SOURCE 
//#include <stdlib.h>
//#include <stdio.h>
//#include <assert.h>
#include "../src/arrayOfCstring.c"
#include "../src/Hash.c"
int main(void)
{
    Hash *h =(Hash*)malloc(sizeof(Hash));
    HashNew(h,30); 
    char *a="k1";
    char *b="k2";
    char *c="v1";
    char *d="v2";
    char *e="ftmpll_ndec[2]";
    char *f="ftmpll_ndec[1]";
    char *g="ftmpll";
    HashInsertString(h,(char*)a,(char*)c); 
    HashInsertPoint(h,(char *)b,(char *)d); 
    HashInsertPoint(h,(char *)e,(char *)g); 
    printf(" k2's value is %s\n",HashValueAtKey(h,"ftmpll_ndec[1]"));
    HashFree(h);
    free(h); 
}
