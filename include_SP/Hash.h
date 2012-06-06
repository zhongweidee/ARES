#ifndef _GNU_SOURCE 
#define _GNU_SOURCE // must for GNU hsearch
#endif
#ifndef SEARCH_H_
#define SEARCH_H_
#include <search.h>
#endif
#ifndef ARRAYOFCSTRING_H
#define ARRAYOFCSTRING_H
#include "../include_SP/arrayOfCstring.h"
#endif

typedef struct {
    ENTRY elem;
    ENTRY *retElem; 
    struct hsearch_data *htab; 
    size_t initialNumOfElem; 
    size_t existNumOfElem; 
    ArrayCstring *keys; 
} Hash;
void HashNew(Hash *h,size_t size);
void HashInsertString(Hash *h,char *key,char *value);
void HashInsertPoint(Hash *h,char *key,void *value);
void *HashValueAtKey(Hash *h,const char *key);
void HashFree(Hash *h);
