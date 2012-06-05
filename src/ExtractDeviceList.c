
#ifndef HEADFILE_
#define HEADFILE_
#include "../include_SP/HeadFile.h"
#endif
#ifndef CSTRING_
#define CSTRING_
#include "../include_SP/Cstring.h"
#endif
//#ifdef CSTRING_
//#endif
namespace ED
{
void linuxCommandResult(const char *command,Cstring* result)
{
   FILE *fp;
   char path [10000];
   fp = popen(command,"r");
   if(fp ==NULL){
    printf("Failed to run command\n" );
    exit(0);
                }
   while (fgets(path, 10000, fp) != NULL) {
     CstringAppend(result,path,strlen(path));
  }
  pclose(fp);
}

void ExtractDeviceList(const char *svrfRulePath,Cstring* result)
{
  
  //Cstring *buffer =(Cstring *)malloc(sizeof(Cstring));
  //CstringNew(buffer);
  //const char *command="grep -P \"DEVICE\s+\S+\(\S+\)\" ";
  const char *commandForList="grep -oP \"DEVICE\\s+\\S+\\(\\S+\\)\" ";
  const char *sortCommand="| sort | uniq";
  char commandWithFileName[strlen(commandForList)+strlen(svrfRulePath)+strlen(sortCommand)+1];
  memcpy(commandWithFileName,commandForList,strlen(commandForList)+1);
  memcpy(commandWithFileName+strlen(commandForList),svrfRulePath,strlen(svrfRulePath)+1);
  memcpy(commandWithFileName+strlen(commandForList)+strlen(svrfRulePath),sortCommand,strlen(sortCommand)+1);
  linuxCommandResult(commandWithFileName,result);
}

}
