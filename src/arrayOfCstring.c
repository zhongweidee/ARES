#ifndef HEADFILE_
#define HEADFILE_
#include "../include_SP/HeadFile.h"
#endif
#ifndef ARRAYOFCSTRING_H_
#define ARRAYOFCSTRING_H_
#include "../include_SP/arrayOfCstring.h"
#endif

/*typedef struct {
   int numOfElems;
   int size;
   int allocSize;
   char** elems;
} ArrayCstring;
*/
void ArrayCstringNew(ArrayCstring *s,int allocS)
{
   s->allocSize=allocS;
   s->numOfElems=0;  
   s->size=0;
   s->elems=(char**)calloc(s->allocSize,sizeof(char**));
   assert(s->elems!=0);
}

void ArrayCstringGrow(ArrayCstring *s){
     printf("LOG1: arrayCstringGrow s->numOfElems is %d s->allocSize is %d\n",s->numOfElems,s->allocSize);
     if(((s->numOfElems)+1)>(s->allocSize)){
     //printf("LOG: s->numOfElems is %d",s->numOfElems);
     //printf("LOG: s->allocSize is %d",s->allocSize);
         s->allocSize=(s->allocSize)*2;
         s->elems=(char**)realloc(s->elems,(s->allocSize)*sizeof(char**));
          }
}
void ArrayCstringPush(ArrayCstring *s,char *elem,int lengthOfElem){
        ArrayCstringGrow(s);
        (s->elems)[s->numOfElems]=(char *)calloc(lengthOfElem,sizeof(char*));
        memcpy((s->elems)[s->numOfElems],elem,lengthOfElem+1);
	(s->size)+=lengthOfElem;
        (s->numOfElems)+=1;
}
char *ArrayCstringIndex(ArrayCstring *s,int i)
{
   return s->elems[i];
}

void ArrayCstringCopy(ArrayCstring *s,ArrayCstring *c){
    //printf("start to ArrayCstringCopy %s\n",s->numOfElems); 
    printf("s numOfElems is %d\n",s->numOfElems); 
    ArrayCstringNew(c,2);
    //c->allocSize=s->allocSize;
    //c->numOfElems=s->numOfElems;
    //c->size=s->size;
    int a=0;
    for(;a<(s->numOfElems);++a){
    //printf("numOfElems is %d\n",s->numOfElems);
//	    printf("a is %d\n",a);
	    char *buf=ArrayCstringIndex(s,a);
            ArrayCstringPush(c,buf,strlen(buf)+1);
	                    }
}
void ArrayCstringPrintAllElems(ArrayCstring *s){
   int a=0;
   for(;a<(s->numOfElems);++a){
    printf("Debug:s->elems, %s\n",(s->elems)[a]);
                            }
}
void ArrayCstringPop(ArrayCstring *s,char *dest)
{
   dest =ArrayCstringIndex(s->numOfElems); 
}

void ArrayCstringDelete(ArrayCstring *s)
{
   int a=0;
   for(;a<(s->numOfElems);++a){
    free((s->elems)[a]);
                            }
   free(s->elems);
}

