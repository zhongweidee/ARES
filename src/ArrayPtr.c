#ifndef ARRAY_PTR_H_
#define ARRAY_PTR_H_
#include "../include_SP/ArrayPtr.h"
#endif
#ifndef HEADFILE_
#define HEADFILE_
#include "../include_SP/HeadFile.h"
#endif

#ifndef OBSTACK_H_
#define OBSTACK_H_
#include <obstack.h>
#define obstack_chunk_alloc malloc
#define obstack_chunk_free free
#endif
/* memory pool refence the www.ibm.com/developerworks/cn/linux/l-memory */
void ArrayPtrAllocFailed(void){
  printf("Error: array alloc memory failed!\n");
}

void ArrayPtrNew(ArrayPtr *arr)
{
arr->obstackPtr = (struct obstack *) malloc (sizeof (struct obstack));
obstack_init (arr->obstackPtr);
obstack_alloc_failed_handler =&ArrayPtrAllocFailed;
obstack_alignment_mask(arr->obstackPtr)=0;
arr->totalNum=0;
}

void ArrayPtrPush(ArrayPtr *arr,void *src,size_t sizeOfSrc){
   void **dest =(void **)obstack_alloc(arr->obstackPtr,sizeOfSrc); 
   printf("LOG: pointer is %p\n",src);
    (*dest)=src;
   //memcpy(dest,src,sizeOfSrc);
   arr->lengthOfLastOne=sizeOfSrc;
   (arr->totalNum)++;
}
void *ArrayPtrPopAddr(ArrayPtr *arr){
  //void *TopAddr= obstack_base(arr->obstackPtr); 
  return ((char *)obstack_base(arr->obstackPtr)-(arr->lengthOfLastOne));
}

void ArrayPtrFree(ArrayPtr *arr,void(*free_function)(void *)){
    int a=0;
    for(;a<(arr->totalNum);a++){
    printf("LOG: str addr is %p\n",ArrayPtrPopAddr(arr));
    void **ptr= (void **)ArrayPtrPopAddr(arr);
    printf("LOG: str is %p\n",(*ptr));
    (*free_function)(*ptr); 
    obstack_free(arr->obstackPtr,ptr); 
                              }
    obstack_free(arr->obstackPtr,0); 
    //obstack_free(arr->obstackPtr,0); 
    free(arr->obstackPtr);
}

