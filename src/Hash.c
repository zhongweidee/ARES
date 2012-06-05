#ifndef _GNU_SOURCE 
#define _GNU_SOURCE // must for GNU hsearch
#endif
#ifndef SEARCH_H_
#define SEARCH_H_
#include <search.h> 
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
   h->htab=calloc(30,sizeof(struct hsearch_data));
   memset(h->htab,0,sizeof(h->htab));
   h->initialNumOfElem=size;
   h->retElem =malloc(sizeof(ENTRY *));
   assert(h->retElem !=0);
   ENTRY e;
   status=hcreate_r(h->initialNumOfElem,h->htab);
   assert(status!=0);
   h->keys =malloc(sizeof(ArrayCstringNew *));
   ArrayCstringNew(h->keys,20*size);
}

void HashInsertString(Hash *h,char *key,char *value)
{
   int status;
   (h->elem).key=key;
   (h->elem).data=value;
   status = hsearch_r(h->elem,ENTER,&(h->retElem),(h->htab));
   assert(status!=0);
   ArrayCstringPush(h->keys,key);
}


void HashInsertPoint(Hash *h,char *key,void *value)
{
   int status;
   (h->elem).key=key;
   (h->elem).data=value;
   status = hsearch_r(h->elem,ENTER,&(h->retElem),(h->htab));
   assert(status!=0);
   ArrayCstringPush(h->keys,key);
}

void *HashValueAtKey(Hash *h,const char *key)
{
   int status;
   status = hsearch_r(h->elem,FIND,&(h->retElem),(h->htab));
   assert(status!=0);
   return (h->retElem)->data;
}

void HashFree(Hash *h)
{
 need to free CstringArray  
 hdestroy_r(h->htab);
} 

