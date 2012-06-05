#ifndef HEADFILE_
#define HEADFILE_
#include "../include_SP/HeadFile.h"
#endif
#ifndef CSTRING_
#define CSTRING_
#include "../include_SP/Cstring.h"
#endif

void CstringNew(Cstring *s)
{
   //s->initFlag=true; 
   //s->current_element=0;
   s->total_element=0;
   s->allocMem=500*sizeof(char);
   s->elems=(char *)malloc(s->allocMem);
   assert(s->elems!=0);
   memcpy(s->elems,"yy",3);
   s->buf=s->elems;
}

void CstringNewWithNum(Cstring *s,size_t allocNum)
{
   //s->initFlag=true; 
   //s->current_element=0;
   //s->total_element=allocNum;
   s->total_element=0;
   s->allocMem=allocNum;
   s->elems=(char *)malloc(s->allocMem);
   assert(s->elems!=0);
   memcpy(s->elems,"yy",3);
   s->buf=s->elems;
}


char *CstringFind(Cstring *s,char *str){
     return strstr(s->elems,str);
}

void CstringAppendMutiArg(Cstring *s,int numOfStr, ...)
{
  char *bufStr;
  int i;
  va_list vl;
  va_start(vl,numOfStr);
  for(i=0;i<numOfStr;i++){
    bufStr=va_arg(vl,char*);
    CstringAppend(s,bufStr,strlen(bufStr)); 
                         }
  va_end(vl);
}
void CstringAppend(Cstring *s,const char * str){
    size_t lengthOfStr=strlen(str);
    (s->total_element)+=lengthOfStr;  
  if((s->total_element)>((s->allocMem)-1)){
    size_t dis=(s->buf) -(s->elems);
    s->elems=(char *)realloc(s->elems,((s->total_element)+1));
    assert(s->elems!=0);
    s->buf =(s->elems) + dis;
    memcpy(s->buf,str,lengthOfStr);
    (s->buf)+=lengthOfStr;
                                             }
  else{
    memcpy(s->buf,str,lengthOfStr);
    (s->buf)+=lengthOfStr;
      }
    char sep='\0';
    //memcpy((s->buf)+1,&sep,1);
    memcpy(s->buf,&sep,1);
}
void CstringUpperCase(Cstring *s){
  int i=0;
  char str[]="Test String.\n";
  char c;
  while ((s->elems)[i])
  {
    c=(s->elems)[i];
    (s->elems)[i]=toupper(c);
    i++;
  }
}

inline void CstringAppend(Cstring *s,const void* str,int lengthOfStr)
/* lengthOfStr don't contain the '\0' , CstringAppend don't automate generate it*/
{
    (s->total_element)+=lengthOfStr;  
  if((s->total_element)>((s->allocMem)-1)){
    size_t dis=(s->buf) -(s->elems);
    while((s->total_element)>((s->allocMem)-1)){
    (s->allocMem)*=2; 
    s->elems=(char *)realloc(s->elems,(s->allocMem));
    if(s->elems==0){
    assert(s->elems!=0);
                   }
                                                     }
    s->buf =(s->elems) + dis;
    memcpy(s->buf,str,lengthOfStr);
    (s->buf)+=lengthOfStr;
                                             }
  else{
    memcpy(s->buf,str,lengthOfStr);
    (s->buf)+=lengthOfStr;
      }
    char sep='\0';
    //memcpy((s->buf)+1,&sep,1);
    memcpy(s->buf,&sep,1);
}
void CstringCopy(Cstring *s, Cstring *c){
       c->allocMem=s->allocMem;
       c->total_element=s->total_element;
       CstringAppend(c,s->elems,s->total_element);   
}

void CstringToUpper(Cstring *s){
//    printf("Debug: s->total_element is %d\n",s->total_element);
    char *buf=(char *)malloc(s->total_element);     
    buf[s->total_element-1]='\0';
    assert(buf!=0);
    size_t i=0;
    char c;
    while((s->elems)[i])
    {
 //     printf("Debug: s->elems is %c\n",(s->elems)[i]);
      c=toupper((s->elems)[i]);
      memcpy(buf+i,&c,1);
  //    printf("Debug: buf is %s\n",buf);
   //   printf("Debug: i is %d\n",i);
      i++;
    }
    //printf("Debug: i is %d\n",i);
    //memcpy(buf+i,'\0',1); 
    //printf("Debug: buf is %s\n",buf);
    free(s->elems);
    s->elems=buf;
}

void CstringDelete(Cstring *s)
{
   free(s->elems);
}
