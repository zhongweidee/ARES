#ifndef _GNU_SOURCE 
#define _GNU_SOURCE // must for GNU hsearch
#endif
#ifndef SEARCH_H_
#define SEARCH_H_
#include <search.h>
#endif
#ifndef ARRAYOFCSTRING_H_
#define ARRAYOFCSTRING_H_
#include "arrayOfCstring.h"
#endif

typedef struct {
    ENTRY elem;
    size_t initialNumOfElem; 
    size_t existNumOfElem; 
    //ENTRY *entryArray[];
    ENTRY *retElem; 
    struct hsearch_data *htab; 
    ArrayCstring *keys; 
} Hash;
typedef struct _ENTRY
{
  unsigned int used;
  ENTRY entry;
}
_ENTRY;


void HashNew(Hash *h,size_t size);
void HashInsertEntry(Hash *h,ENTRY *entry);
//void HashInsertString(Hash *h,const char *key,char *value);
//void HashInsertPoint(Hash *h,const char *key,void *value);
int HashValueAtKey(Hash *h,const char *key,ENTRY **findE);
void HashFree(Hash *h);
ArrayCstring *HashKeys(Hash *h);
void HashPrintKeys(Hash *h);
