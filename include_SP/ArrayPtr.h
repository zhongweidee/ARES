#ifndef HEADFILE_
#define HEADFILE_
#include "../include_SP/HeadFile.h"
#endif

typedef struct{
size_t totalNum;
struct obstack *obstackPtr;
size_t lengthOfLastOne;
}ArrayPtr;

void ArrayPtrAllocFailed(void);
void ArrayPtrNew(ArrayPtr *arr);
void ArrayPtrPush(ArrayPtr *arr,void *src,size_t sizeOfSrc);
void *ArrayPtrPopAddr(ArrayPtr *arr);
void ArrayPtrFree(ArrayPtr *arr,void(*free_function)(void *));

