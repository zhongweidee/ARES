//#define _GNU_SOURCE 
//#include <stdlib.h>
//#include <stdio.h>
//#include <assert.h>
#include "../src/arrayOfCstring.c"
#include "../src/Hash.c"
#define DEBUG
int main(void)
{
    Hash *h =(Hash*)malloc(sizeof(Hash));
    HashNew(h,30); 
    ENTRY **entry=(ENTRY **)malloc(sizeof(ENTRY *));
    //*entry=(ENTRY *)malloc(sizeof(ENTRY));
    const char *a="k1";
    const char *b="k2";
    const char *c="v1";
    const char *d="v2";
    const char *e="ftmpll_ndec[2]";
    const char *f="ftmpll_ndec[1]";
    const char *g="ftmpll";
    HashInsertString(h,a,(char *)c); 
    HashInsertPoint(h,b,(char *)d); 
    HashInsertPoint(h,e,(char *)g); 
    //HashInsertPoint(h,f,(char *)g); 
    int result =HashValueAtKey(h,"ftmpll_ndec[1]",entry);
    if(result !=0){
    printf(" k2's value is %s\n",(*entry)->data);
                  }
    else{
    printf(" can't find value in  ftmpll_ndec[1]\n");
         }
    HashFree(h);
    //free(*entry);
    free(entry);
    free(h); 
}
