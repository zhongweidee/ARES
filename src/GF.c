#ifndef GF_
#define GF_
#include "../include_SP/GF.h"
#endif
namespace GF{
void joinStr(char* arr,int numOfStr...)
{
   char *bufStr;
   char *pos;
   pos=arr;
   int i;
   va_list vl;
   va_start(vl,numOfStr);
   for(i=0;i<numOfStr;i++){
     bufStr=va_arg(vl,char*);
     memcpy(pos,bufStr,strlen(bufStr));
     pos+=strlen(bufStr);
                          }
     memcpy(pos,"\0",1);
     va_end(vl);
}
void splitDataBaseToHash(Cstring *s,const char *sep1,const char *sep2,const char flag,Hash *h){
    size_t hashSize;
    hashSize=0;
    while(memchr(s->elems,flag,s->total_element)!=0){
         hashSize++;
                                                     } 
    HashNew(h,hashSzie);
    void *posA=memchr(s->elems,sep1,s->total_element);
    void *posB,*posC,*posD;
    while(posA!=0){
      posB=memchr(posA,flag,(s->total_element)-(posA-(s->elem))); 
      posC=posB+1; 
      posD=memchr(posC,sep2,(s->total_element)-(posC-(s->elem)));
      char keyForHash[posB-posA+1];
      memcpy(keyForHash,posA,(posB-posA));
      void *result = HashValueAtKey(h,keyForHash);
      if(result==0){
      char instancePin[posD-posC+1];
      memcpy(instancePin,posC,(posD-posC));
      ArrayCstring *value = malloc(sizeof(ArrayCstring *)); 
      ArrayCstringNew(value,10);
      ArrayCstringPush(value,instancePin,posD-posC+1);
                                         }
      else{
      ArrayCstring *value =result; 
      ArrayCstringPush(value,instancePin,posD-posC+1);
           }
      posA=memchr(posD+1,sep1,s->total_element-(posD+1-(s->elems)));
                   }
}

}
