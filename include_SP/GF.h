
#ifndef HEADFILE_
#define HEADFILE_
#include "HeadFile.h"
#endif
#ifndef HASH_H_
#define HASH_H_
#include "Hash.h"
#endif
#ifndef CSTRING_
#define CSTRING_
#include "../include_SP/Cstring.h"
#endif
namespace GF{
void joinStr(char* arr,int numOfStr...);
void splitDataBaseToHash(Cstring *s,const char sep1,const char sep2,const char flag,Hash *h);
}
