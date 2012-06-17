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
   h->existNumOfElem=0;
   h->htab=(struct hsearch_data *)calloc(30,sizeof(struct hsearch_data));
   assert(h->htab!=0);
   status=hcreate_r(size,h->htab);
   putsLogD(status); 
   assert(status!=0);
   h->initialNumOfElem=size;
   h->keys =(ArrayCstring*)malloc(sizeof(ArrayCstring ));
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

//void HashInsertString(Hash *h,const char *key,char *value)
void HashInsertEntry(Hash *h,ENTRY *entry)
{
   (h->existNumOfElem)++;
   ArrayCstringPush(h->keys,entry.key,strlen(entry.key));
   int status;
   ENTRY *retElem;
   status = hsearch_r(entry,ENTER,&retElem,(h->htab));
   assert(status!=0);
}
void CopyEntry(ENTRY *src, ENTRY *des)
{
     des.key = strdump(src.key); 
     des.data=src.value;
}

/*void HashInsertPoint(Hash *h,ENTRY *entry)
{
   int status;
   (h->elem).key=(char *)key;
   (h->elem).data=value;
   ENTRY *retElem;
   status = hsearch_r(h->elem,ENTER,&retElem,(h->htab));
   assert(status!=0);
   ArrayCstringPush(h->keys,(char*)key,strlen(key));
}*/

int HashValueAtKey(Hash *h,const char *key,ENTRY **findE)
{
   int status;
   ENTRY wishFind;
   wishFind.key=(char *)key;
   //status = hsearch_r(h->elem,FIND,&(h->retElem),(h->htab));
   //status = hsearch_r(wishFind,FIND,&(h->retElem),(h->htab));
   status = hsearch_r(wishFind,FIND,findE,(h->htab));
   if(status==0){
     return 0;
                }
   else{
   HashPrintKeys(h);
   return 1;
        }
   //assert(status!=0);
   //assert(status!=0);
   //printf("Debug: find the hash key is %s\n",(h->retElem)->key);
   //return (h->retElem)->data;
   //return h->retElem;
}

void HashFree(Hash *h)
{
 //need to free CstringArray  
// for(int a=0;a<((h->keys)->numOfElems);++a){
 //   free(ArrayCstringIndex(h->keys,a)); 
  //                                          }
 //free(h->retElem);
 ArrayCstringDelete(h->keys);  
 free(h->keys); 
 hdestroy_r(h->htab);
 free(h->htab);  
} 

