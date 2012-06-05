#ifndef CSTRING_
#define CSTRING_
#include "Cstring.h"
#endif
namespace ED
{
void linuxCommandResult(const char *command,Cstring* result);
void ExtractDeviceList(const char *svrfRulePath,Cstring* result);
}
