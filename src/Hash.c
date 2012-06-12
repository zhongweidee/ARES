#ifndef _GNU_SOURCE 
#define _GNU_SOURCE // must for GNU hsearch
#endif
#ifndef SEARCH_H_
#define SEARCH_H_
#include <search.h> 
#endif
#ifndef HEADFILE_
#define HEADFILE_
#include "../include_SP/HeadFile.h"
#endif
#ifndef HASH_H_
#define HASH_H_
#include "../include_SP/Hash.h"
#endif


void HashNew(Hash *h ,size_t size)
{
   int status;
   //h->htab ={0};
   //h->htab =calloc(30,sizeof(struct hsearch_data));
   h->htab=(hsearch_data *)calloc(30,sizeof(struct hsearch_data));
   memset(h->htab,0,sizeof(h->htab));
   h->initialNumOfElem=size;
   h->retElem =(ENTRY*)malloc(sizeof(ENTRY *));
   assert(h->retElem !=0);
   ENTRY e;
   status=hcreate_r(h->initialNumOfElem,h->htab);
   assert(status!=0);
   h->keys =(ArrayCstring*)malloc(sizeof(ArrayCstring *));
   ArrayCstringNew(h->keys,size);
}
ArrayCstring *HashKeys(Hash *h){
    return h->keys; 
}
void HashPrintKeys(Hash *h){
 printf("LOG: key num is %d\n",((h->keys)->numOfElems));
 for(int a=0;a<((h->keys)->numOfElems);++a){
    printf("LOG:key is %s\n",(ArrayCstringIndex(h->keys,a))); 
        }
}

void HashInsertString(Hash *h,char *key,char *value)
{
   int status;
   (h->elem).key=key;
   (h->elem).data=value;
   status = hsearch_r(h->elem,ENTER,&(h->retElem),(h->htab));
   assert(status!=0);
   ArrayCstringPush(h->keys,key,strlen(key));
}


void HashInsertPoint(Hash *h,char *key,void *value)
{
   int status;
   (h->elem).key=key;
   (h->elem).data=value;
   status = hsearch_r(h->elem,ENTER,&(h->retElem),(h->htab));
   assert(status!=0);
   ArrayCstringPush(h->keys,key,strlen(key));
}

void *HashValueAtKey(Hash *h,const char *key)
{
   int status;
   ENTRY wishFind;
   wishFind.key=(char *)key;
   //status = hsearch_r(h->elem,FIND,&(h->retElem),(h->htab));
   status = hsearch_r(wishFind,FIND,&(h->retElem),(h->htab));
   printf("Debug: status is %d\n",status);
   if(status==0){
    return 0;
                }
   else{
   //assert(status!=0);
   printf("Debug: find the hash key is %s\n",(h->retElem)->key);
   HashPrintKeys(h);
   return (h->retElem)->data;
   //return h->retElem;
       }
}

void HashFree(Hash *h)
{
 //need to free CstringArray  
 for(int a=0;a<((h->keys)->numOfElems);++a){
    free(ArrayCstringIndex(h->keys,a)); 
                                            }
 ArrayCstringDelete(h->keys);  
 hdestroy_r(h->htab);
} 

