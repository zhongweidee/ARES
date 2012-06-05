namespace SPS
/* Super string function */
{
 #define strstrCheckRange lengthOfStr1-((char *)buf-(char*)str1) 
inline bool strstr(const void *str1,size_t lengthOfStr1,const void *str2,size_t lengthOfStr2){
      const void *buf=str1;
      const void *result=str1;
      while(
            (result!=0)
          &&(strstrCheckRange>=lengthOfStr2)
	  &&(((result =memchr(buf,(int)(*((char *)str2)),strstrCheckRange))!=0))
	   ){
         if(!memcmp(result,str2,lengthOfStr2)){ 
                 return true;
                                              }
	      buf=(char *)result+1;
                    }
      return false;
}

inline int strcmp(const char *str1,const char *str2){
     size_t lengthOfStr1=strlen(str1);
     size_t lengthOfStr2=strlen(str2);
    if((lengthOfStr1==lengthOfStr2)&&(!memcmp(str1,str2,lengthOfStr1))){
      return 0; 
                                 }
      return 1;
}


}
