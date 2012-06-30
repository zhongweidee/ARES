#ifndef HEADFILE_
#define HEADFILE_
#include "../include_SP/HeadFile.h"
#endif
#ifndef GLOBAL_FUNCTION_
#define GLOBAL_FUNCTION_
#include "../include_SP/Global_function.h"
#endif
namespace Global_function
{
void SNPuts(string content){
    if(logMode==0){
    cout<<"LOG: "<<content<<endl;
                  }
}
std::string Upper(std::string word)
{
     transform(word.begin(),word.end(),word.begin(),::toupper); 
     return  word;
}
void StringReplace(std::string &currentString,std::string const &oldString,std::string const &newString)
{
     size_t pos=0;
     size_t lengthOldString =oldString.length();
     size_t lengthNewString =newString.length();
     //size_t stringCount =oldString.size();
     while((pos=currentString.find(oldString))!=string::npos){
         currentString.replace(pos,lengthOldString,newString);
         pos +=lengthNewString;
                                             }
}


void StringSplitFromAToB(std::string const &currentString,std::string const &A,std::string const &B,vArrayString &container)
{
     if((currentString.find(A)==string::npos)||(currentString.find(B)==string::npos)){
	     cout<<"Error: can't find the string "<<A<<" and "<<B;
	     cout<<"Error:"<<currentString;
	     cout<<endl;
	     exit(0);
		     }
     size_t posA=0;
     size_t posB=0;
     size_t lengthB=B.length();
     //size_t stringCount =currentString.size();
     while((posA=currentString.find(A,posA))!=string::npos){
        while((posB=currentString.find(B,posB))!=string::npos){
              if((posB-posA) <=0){
                cout <<"Error: posB need larger than posA"<<endl;
                exit(0);
                               }
              //posB=posB+lengthB;
              //std::string tempString = currentString.substr(posA,posB+lengthB+1-posA); 
              container.push_back(currentString.substr(posA,posB+lengthB+1-posA));
              posA=posB+B.size();
              posB=posA;
              //cout<<"LOG: start to push "<<posA<<endl;
              //cout<<tempString<<endl;
              //cout<<"LOG: end to push "<<posB<<endl;
                                                         }
                                                       }
}

void readFileToString(const char *filePath,std::string &container)
{
     cout<<"LOG:start to readFileString"<<endl;
     std::ifstream inFile(filePath);
     inFile.seekg(0,std::ios::end);
     container.reserve(inFile.tellg());
     inFile.seekg(0,std::ios::beg);
     container.assign((std::istreambuf_iterator<char>(inFile)),
                                 std::istreambuf_iterator<char>()); 
     cout<<"LOG:end to readFileString"<<endl;
}

void readFileToCstring(const char *filePath,Cstring *s){
    int fd;
    fd=open(filePath,O_RDONLY); 
    assert(fd!=-1); 
    off_t start= lseek(fd,0,SEEK_SET);
    off_t end= lseek(fd,-1,SEEK_END);
    off_t allocNum=end -start +1;
    char buf[allocNum];
    buf[allocNum-1]='\0';
    assert(read(fd,buf,allocNum)!=-1);
    CstringAppend(s,buf);
}


//test fuction

void replaceAll(string& s, const string& f, const string& r) {
    if (s.empty() || f.empty() || f == r || f.size() > s.size() || s.find(f) == string::npos) {
        //return s;
	cout<<"Warning: the input string is not illegal "<<endl;
	//exit(0);
    }
    else{
    ostringstream build_it;
    typedef string::iterator iter;
    iter i(s.begin());
    const iter::difference_type f_size(distance(f.begin(), f.end()));
    for (iter pos; (pos = search(i , s.end(), f.begin(), f.end())) != s.end(); ) {
        copy(i, pos,  ostreambuf_iterator<char>(build_it));
        copy(r.begin(), r.end(), ostreambuf_iterator<char>(build_it));
        advance(pos, f_size);
        i = pos;
    }
    copy(i, s.end(), ostreambuf_iterator<char>(build_it));
    //return build_it.str();
    s= build_it.str();
    //s.swap(build_it.str());
    }
}

void linuxCommandResult(string command,string& result)
{
   FILE *fp;
   //int status;
   //char *path = new char(10002);
   char path [10000];
   //char path[10000000];
   fp = popen(command.c_str(),"r");
   if(fp ==NULL){
    printf("Failed to run command\n" );
    exit(0);
                }
   while (fgets(path, 10000, fp) != NULL) {
     string *buf =new string(path);
     result+=*buf;
     delete buf;
     cout<<"LOG:find: "<<path<<endl;
  }
  /* close */
  //delete [] path;
  pclose(fp);
}

int file_exists(string fileName)
{
      
     return (access(fileName.c_str(),4)==0);
}


inline void vStringSplit(vArrayString &array,std::string &a)
{
   std::string buf;
   stringstream ss(a);
   //vArrayString array;
   while (ss >> buf)
       array.push_back(buf);
}
void vStringSplitByString(vArrayString &array,std::string &a,std::string &sep)
{
   replaceAll(a,sep," ");
   vStringSplit(array,a); 
}
void vStringSplitByString(vArrayString &array,std::string &a,const char *sep_char)
{
   string sep(sep_char);
   replaceAll(a,sep," ");
   vStringSplit(array,a); 
}

bool checkStringHasWhiteSpace(string &a)
{
     if(a.find(" ")!=string::npos){
       return true;
                                  }
     else{
       return false;
         }
}

void deleteSpaceInStartAndEnd(string &a){
	SNPuts("LOG: start to deleteSpaceInStartAndEnd");
     //size_t size=a.size();
     //int i=0;
     size_t posA =a.find_first_not_of(" ");
     size_t posB =a.find_last_not_of(" ");
     //SNPuts("LOG: posA is " +intToString(posA)+" posB is "+intToString(posB)+" size is "+size);

     if((posA!=string::npos)&&(posB!=string::npos)){
     string temp=a.substr(posA,posB-posA+1);
     swap(a,temp);
      }
     else if((posA!=string::npos)&&(posB==string::npos)){
     string temp=a.substr(posA);
     swap(a,temp);
     }
     else if((posA==string::npos)&&(posB!=string::npos)){
     string temp=a.substr(0,posB+1);
     swap(a,temp);
     }
     SNPuts("LOG: end to deleteSpaceInStartAndEnd");
}
string intToString(int a){
    stringstream ss(stringstream::in|stringstream::out);
    //cout<<"LOG:"<<a<<endl;
    ss<<a;
    return ss.str();
}

void vStringSplit(std::string &a,vArrayString &tokens)
{
   //cout<<"LOG: vStringSplit:"<<a<<endl;
   std::string buf;
   stringstream ss(a);
   while (ss >> buf)
       tokens.push_back(buf);
   //cout<<"LOG: end vStringSplit:"<<a<<endl;
}
void dStringSplit(std::string &a,dArrayString &tokens)
{
   std::string buf;
   stringstream ss(a);
   while (ss >> buf)
       tokens.push_back(buf);
}

/*child ChildPtrToChild(boost::shared_ptr<child> cp){
     return *cp;
}*/
 
int CoutNumOfLineInString(string &s){
   stringstream stream(s);
   string line;
   int NumOfLines=0;
   while(getline(stream,line,'\n')){
	   NumOfLines++;
		   }   
   return NumOfLines;
}

string GetFirstElementInLine(string &s){
       //cout<<"LOG:GetFirstElementInLine"<<endl;
       //cout<<s<<endl;
       //cout<<"LOG:posA"<<s.find_first_not_of(" ")<<" "<<(s.find_first_of(" ",s.find_first_not_of(" "))-1)<<endl;
       size_t posA=s.find_first_not_of(" ");
       return s.substr(posA,s.find_first_of(" ",s.find_first_not_of(" "))-1-posA+1);
}
string GetSecondElementInLine(string &s){
       cout<<"LOG:GetSecondElementInLine"<<endl;
       size_t posA =s.find_first_not_of(" ",s.find_first_of(" ",s.find_first_not_of(" ")));
       size_t posB =s.find_first_of(" ",posA);
       cout<<"LOG:posA "<<posA<<" posB "<<posB<<endl;
       cout<<"LOG:need to split: "<<s<<endl;
       cout<<"LOG:"<<s.substr(posA,posB-1-posA+1)<<endl;
       return s.substr(posA,posB-1-posA+1);
		       //s.find_first_of(" ",s.find_first_not_of(" ",s.find_first_of(" ",s.find_first_not_of(" ")))));
}
string GetSecondLastElementInLine(string &s){
          size_t posA=s.find_last_of(" ",s.find_last_not_of(" ",s.find_last_of(" ",s.find_last_not_of(" "))))+1;
       //cout<<"LOG:GetSecondLastElementInLine"<<endl;
          return s.substr(posA,s.find_last_not_of(" ",s.find_last_of(" ",s.find_last_not_of(" ")))-posA+1);
}
string GetFirstLastElementInLine(string &s){
      //cout<<"LOG:GetFirstLastElementInLine"<<endl;
      size_t posA=s.find_last_of(" ",s.find_last_not_of(" "))+1;
      return s.substr(posA,s.find_last_not_of(" ")-posA+1);
}

/*void assignStringToCharAddress( string &s, char *c){
     // c=new char [s.size() +1]; 
      strcpy(c,s.c_str());
      cout<<"LOG:assignStringToCharAddress "<<c<<endl;
}*/
void assignPairArraySSToCharAddress( pairArraySS &s,char *c){
     string buf;
     for(pairArraySSIter it=s.begin();it!=s.end();++it){
           buf=buf + "@" +((*it).first+"."+(*it).second);
                                                       }
           buf.append("@");
           //assignStringToCharAddress(buf,c);
     //      char str[int(buf.size()+1)];
           //c =buf.c_str(); 
           strcpy(c,buf.c_str());
}

int coutCharNumOfPariArraySS(pairArraySS &s){
     string buf;
     for(pairArraySSIter it=s.begin();it!=s.end();++it){
           buf=buf + "@" +((*it).first+"."+(*it).second);
                                                       }
           buf.append("@");
     return (buf.size()+1);
}
void assignCharAddressToPairArraySS(char *c,pairArraySS &s){
     string buf(c);
     if((buf.find(".")==string::npos)||(buf.find("@")==string::npos)){
         cout<<"Error: the char don't have the . point  or @ "<<buf<<endl;
         exit(0);
                                    }
     vArrayString array;  
     string sep("@");
     string bufSep(".");
     vStringSplitByString(array,buf,sep);
     for( vIterString it =array.begin();it!=array.end();++it){
     vArrayString arrayIt;  
     vStringSplitByString(arrayIt,*it,bufSep);
           if(arrayIt.size()==2){
           s.push_back(make_pair(arrayIt[0],arrayIt[1])); 
                             }
           else{
           cout<<"Error: not pair "<<*it<<endl;
           exit(0);
               }
                                                              }
}

char IntToCharAddress(int i){   //not verify
   char dig =(char)(((int)'0')+i);
   return dig;
}
 
int  CharAddressToInt(char *dig){
      return atoi(dig); 
}

/*char *generateRelationshipAndIndex(char *r,void *i,size_t size,char *str){
        size_t lengthOfR=strlen(r);
        char buf[lengthOfR+sizeof(size_t)+sizeof('@')+1]
        memcpy(buf,r,lengthOfR);
        memcpy(buf+lengthOfR+1,i,sizeof(size_t));
        return buf; 
}*/

void JoinMemAndMemBySep(void *r,void *i,void *sep,size_t sizeOfr,size_t sizeOfi,size_t sizeOfsep,void *str){
        memcpy(str,r,sizeOfr);
        memcpy((char *)str+sizeOfr,sep,sizeOfsep);
        memcpy((char *)str+sizeOfr+sizeOfsep,i,sizeOfi);
}

void seperateMemByMem(void *w,void *sep,void *result1,void *result2,size_t sizeOfw){
     void* findPtr;
     findPtr=memchr(w,*(char *)sep,sizeOfw);
     if(findPtr!=0){
     memcpy(result1,w,(char *)findPtr-(char*)w+1);
     memcpy(result2,(char *)findPtr+1,sizeOfw - ((char *)findPtr-(char*)w+1));
                   }
     findPtr=memchr((char*)findPtr+1,*(char *)sep,sizeOfw-((char *)findPtr-(char*)w));
     assert(findPtr==0);
     /*while(findPtr!=0){
     findPtr=memchr(findPtr+1,*(char *)sep,sizeOfw-findPtr);
                      } */
}
void split(char **arr, char *str, const char *del) {  
 char *s = strtok(str, del);  
 while(s != 0) {  
     *arr++ = s;  
     s = strtok(0, del);  
 }  
}  
size_t rfind(char *str1,char sep,size_t sizeOfstr1){
      char buf[sizeOfstr1+1];
      buf[sizeOfstr1]='\0';
      strncpy(buf,str1,sizeOfstr1);
      char *posB=strrchr(buf,sep);        
      return posB-buf;
}
inline void SPstrncpy(char *d,char *s,size_t l){
        d[l]='\0';
        strncpy(d,s,l);
}

char intToChar(int a){
   return (char)(((int)'0')+a);
}
int strcmp(const char *str1,const char *str2){
     size_t lengthOfStr1=strlen(str1);
     size_t lengthOfStr2=strlen(str2);
    if((lengthOfStr1==lengthOfStr2)&&(!memcmp(str1,str2,lengthOfStr1))){
      return 0; 
                                 }
      return 1;
}
#define strstrCheckRange lengthOfStr1-((char *)buf-(char*)str1) 
bool strstr(const void *str1,size_t lengthOfStr1,const void *str2,size_t lengthOfStr2){
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

/*void strchr(const void *str1,const void *str2,size_t lengthOfstr2)
{ char *pch;
   pch=(char *)memchr(str1,(char)str2[0],strlen(str));
   
   if(pch!=0){
   memcpy()
             }
}*/
/*size_t findMemByMem(void *mem1,void *mem2,size_t sizeOfMem1,size_t sizeOfMem2){
         void *pch;
         //pch =memchr(
}

char * convertConstCharPtrToCharPtr(const char* p){
       size_t length = strlen(p);
       void *pch =p;
       (char *)pch; 
}
char * convertCharPtrToConstCharPtr(char* p){
       void *pch=p;
       return  (char *)pch; 
}*/
}

