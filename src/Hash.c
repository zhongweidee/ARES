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
#ifndef OBSTACK_H_
#define OBSTACK_H_
#include <obstack.h>
#define obstack_chunk_alloc malloc
#define obstack_chunk_free free
#endif
#ifndef ARRAY_PTR_H_
#define ARRAY_PTR_H_
#include "../include_SP/ArrayPtr.h"
#endif


void HashAllocFailed(void){
  printf("Error: Hash alloc memory failed!\n");
}


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
/* init garbage OBSTACK */
   h->garbage=(struct obstack *)malloc(sizeof(struct obstack)); 
   obstack_init (h->garbage);
   obstack_alloc_failed_handler =&HashAllocFailed;
   obstack_alignment_mask(h->garbage)=0;
/* init array of arraycstring's ptr */
   h->arrayOfPtr=(ArrayPtr *)calloc(1,sizeof(ArrayPtr ));
   ArrayPtrNew(h->arrayOfPtr);
}
void HashInsertPtr(Hash *h,char *key,void *data,size_t len)
{
  /* check whether have the key already */
      //ENTRY **entry=(ENTRY **)malloc(sizeof(ENTRY));
      ENTRY **entry=(ENTRY **)obstack_alloc(h->garbage,sizeof(ENTRY));
      int result = HashValueAtKey(h,key,entry);
      if(result==0){
      printf("LOG: result is %d not find hash key: %s\n",result,key);
      ArrayCstring *value = (ArrayCstring*)malloc(sizeof(ArrayCstring )); 
      ArrayCstringNew(value,2);
      ArrayCstringPush(value,(char *)data,len);
     // HashInsertPtr(h,key,value); 
      int status;
      ENTRY *retElem;   
      ENTRY *InsertEntry =(ENTRY *)obstack_alloc(h->garbage,sizeof(ENTRY));
      InsertEntry->key=(char *)obstack_alloc(h->garbage,strlen(key)+1);
      memcpy(InsertEntry->key,key,strlen(key)+1);
   //InsertEntry->data=obstack_alloc(h->garbage,sizeof(void *)));
      InsertEntry->data=value;
      status = hsearch_r(*InsertEntry,ENTER,&retElem,(h->htab));
      if(status ==0){
      printf("LOG: status is %d\n",status);
                    }
      assert(status!=0);
      ArrayPtrPush(h->arrayOfPtr,value,sizeof(ArrayCstring *));
                                         }
      else{
      printf("LOG: result is %d find hash key: %s, and the array address is %p \n",result,key,((*entry)->data));
      ArrayCstringPush((ArrayCstring*)((*entry)->data),(char *)data,len);
           }
      
}


int HashValueAtKey(Hash *h,const char *key,ENTRY **findE)
{
   int status;
   ENTRY wishFind;
   wishFind.key=(char *)key;
   status = hsearch_r(wishFind,FIND,findE,(h->htab));
   if(status==0){
     return 0;
                }
   else{
   //HashPrintKeys(h);
   return 1;
        }
}

void HashFree(Hash *h)
{
 ArrayPtrFree(h->arrayOfPtr,&ArrayCstringDelete);
 free(h->arrayOfPtr);
 obstack_free(h->garbage,0);
 free(h->garbage);
 hdestroy_r(h->htab);
 free(h->htab);  
} 

