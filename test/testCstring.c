#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
//#include "../include_SP/arrayOfCstring.h"
#include "../src/arrayOfCstring.c"

int main(void){
  ArrayCstring *ep;
  ArrayCstring *ep1;
  ep  =(ArrayCstring *)malloc(1*sizeof(ArrayCstring));
  ep1 =(ArrayCstring *)malloc(1*sizeof(ArrayCstring));
  ArrayCstringNew(ep,2);
  ArrayCstringPush(ep,"ysdfsd",7);
  printf("start to \n");
  for (int b=0;b<1000000;++b){
  ArrayCstringPush(ep,"1213423",8);
                           }
  ArrayCstringCopy(ep,ep1);
  int a;
  for(a=0;a<20;++a){
    char *str=ArrayCstringIndex(ep,a);
    printf("string is %s\n",str);
                      }
  ArrayCstringDelete(ep1);
  ArrayCstringDelete(ep);
  free(ep);
  free(ep1);
}
