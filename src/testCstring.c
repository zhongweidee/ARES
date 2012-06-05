#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "arrayOfCstring.h"

int main(void){
  ArrayCstring *ep;
  ArrayCstring *ep1;
  ep  =(ArrayCstring *)malloc(1*sizeof(ArrayCstring));
  ep1 =(ArrayCstring *)malloc(1*sizeof(ArrayCstring));
  ArrayCstringNew(ep,2);
  ArrayCstringPush(ep,"ysdfsd",7);
  printf("start to \n");
  ArrayCstringPush(ep,"1213423",8);
  ArrayCstringCopy(ep,ep1);
  ArrayCstringDelete(ep);
  free(ep);
  int a;
  for(a=0;a<2;++a){
    char *str=ArrayCstringIndex(ep1,a);
    printf("string is %s\n",str);
                      }
  ArrayCstringDelete(ep1);
  free(ep1);
}
