#ifndef HEADFILE_
#define HEADFILE_
#endif
#ifdef HEADFILE_
#include "../include_SP/HeadFile.h"
#endif
class CheckDuplicateCell{
   private:
        string all;
        char sep;
   public:
        CheckDuplicateCell(char s):sep(s){
                                        }
        void operator() (string& elem) {
           //theValue=theValue+"."+elem; 
           if(all.find(elem)){
              cout<<"Warning: find the duplicate cell "<<elem<<endl;
              //exit(0); 
                            }
           all.append(1,sep);
           all.append(elem);
             }
        /*operator string(){
           return all;
                          }
        */
};

/*class atecharAddressTocharArray{
      private:
      public:
                   
}*/
