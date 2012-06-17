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
void splitDataBaseToHash(Cstring *s,const char sep1,const char sep2,const char flag,Hash *h){
    size_t hashSize;
    hashSize=0;
    void *flagPos;
    flagPos=memchr(s->elems,flag,s->total_element);
    while(flagPos!=0){
         hashSize++;
         flagPos=memchr((char*)flagPos +1,flag,(s->total_element-((char*)flagPos-(s->elems))));
                                                     } 
    //HashNew(h,hashSize);
    HashNew(h,20);
    void *posA=memchr(s->elems,sep1,s->total_element);
    void *posB,*posC,*posD;
    while(posA!=0){
      posB=memchr(posA,flag,(s->total_element)-((char *)posA-(s->elems))); 
      posC=(char *)posB+1; 
      posD=memchr(posC,sep2,(s->total_element)-((char *)posC-(s->elems)));
      char valueForHash[(char *)posB-(char *)posA];
      valueForHash[(char *)posB-(char *)posA-1]='\0';
      memcpy(valueForHash,(char*)posA+1,((char *)posB-(char *)posA)-1);
      printf("LOG: valueForHash is %s\n",valueForHash);
      char keyForHash[(char *)posD-(char *)posC+1];
      keyForHash[(char *)posD-(char *)posC]='\0';
      memcpy(keyForHash,(char *)posC,(char *)posD-(char *)posC);
      printf("LOG: keyForHash is %s\n",keyForHash);
      ENTRY **entry=(ENTRY **)malloc(sizeof(ENTRY*));
      int result = HashValueAtKey(h,keyForHash,entry);
      if(result==0){
      //memcpy(instancePin,posC,((char *)posD-(char *)posC));
      printf("LOG: result is %d not find hash key: %s\n",result,keyForHash);
      ArrayCstring *value = (ArrayCstring*)malloc(sizeof(ArrayCstring *)); 
      ArrayCstringNew(value,2);
      ArrayCstringPush(value,valueForHash,strlen(valueForHash));
      HashInsertPoint(h,keyForHash,valueForHash); 
                                         }
      else{
      //ArrayCstring *value =(ArrayCstring*)result; 
      printf("LOG: result is %d find hash key: %s\n",result,keyForHash);
      //printf("LOG: result is %s not find hash key: %s\n",result,keyForHash);
      ArrayCstringPush((ArrayCstring*)((*entry)->data),valueForHash,strlen(valueForHash));
           }
      posA=memchr((char *)posD+1,sep1,s->total_element-((char *)posD-(s->elems)));
                   }
}

}
