#ifndef  HS_
#define HS_ 
#include "../include_SP/HS.h"
#endif
void initHS(const char * netInf){
     
}
     hcreate(leastNum); 
void inseartPair(HS *ep,const char *k,const char *v){
    HS e;
    e.key=k;
    e.data=v;
    ep =hsearch(e,ENTER); 
    if (ep == NULL) {
                   fprintf(stderr, "entry failed\n");
                   exit(EXIT_FAILURE);
               }
}

