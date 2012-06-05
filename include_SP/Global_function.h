#ifndef HEADFILE_
#define HEADFILE_
#include "HeadFile.h"
#endif
#ifndef CSTRING_
#define CSTRING_
#include "Cstring.h"
#endif
namespace Global_function
{
void SNPuts(string content);
std::string Upper(std::string word);
void StringReplace(std::string &currentString,std::string const &oldString,std::string const &newString);
void StringSplitFromAToB(std::string const &currentString,std::string const &A,std::string const &B,vArrayString &container);
void readFileToString(const char *filePath,std::string &container);
void replaceAll(string& s, const string& f, const string& r);
void linuxCommandResult(string command,string& result);
int file_exists(string fileName);
void vStringSplit(vArrayString &array,std::string &a);
void vStringSplitByString(vArrayString &array,std::string &a,std::string &sep);
void vStringSplitByString(vArrayString &array,std::string &a,const char *sep_char);
bool checkStringHasWhiteSpace(string &a);
void deleteSpaceInStartAndEnd(string &a);
string intToString(int a);
void vStringSplit(std::string &a,vArrayString &tokens);
void dStringSplit(std::string &a,dArrayString &tokens);
int CoutNumOfLineInString(string &s);
string GetFirstElementInLine(string &s);
string GetSecondElementInLine(string &s);
string GetSecondLastElementInLine(string &s);
string GetFirstLastElementInLine(string &s);
void assignPairArraySSToCharAddress( pairArraySS &s,char *c);
int coutCharNumOfPariArraySS(pairArraySS &s);
void assignCharAddressToPairArraySS(char *c,pairArraySS &s);
char IntToCharAddress(int i);
int  CharAddressToInt(char *dig);
void JoinMemAndMemBySep(void *r,void *i,void *sep,size_t sizeOfr,size_t sizeOfi,size_t sizeOfsep,void *str);
void seperateMemByMem(void *w,void *sep,void *result1,void *result2,size_t sizeOfw);
void split(char **arr, char *str, const char *del)  ;
size_t rfind(char *str1,char sep,size_t sizeOfstr1);
inline void SPstrncpy(char *d,char *s,size_t l);
char intToChar(int a);
//inline int strcmp(const char *str1,const char *str2);
int strcmp(const char *str1,const char *str2);
bool strstr(const void *str1,size_t lengthOfStr1,const void *str2,size_t lengthOfStr2);
void readFileToCstring(const char *filePath,Cstring *s);
}

