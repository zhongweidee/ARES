#include "HeadFile.h"
#include "Global_function.h"
#include <stdio.h>
int main(void){
    char *a=(char *)malloc(sizeof(char *));
    char *b=(char *)malloc(sizeof(char *));
    a= "dsfjjjj";
    b="jj1";
    Global_function::strstr(a,7,b,3);
    free(a);
    free(b);
    /*if(Global_function::strstr(a,7,b,3)){
         printf("LOG: true\n");
                                        }
    else{
         printf("LOG: false\n");
        }*/
return 0;
}
