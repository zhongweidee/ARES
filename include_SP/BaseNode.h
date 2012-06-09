#ifndef HEADFILE_
#define HEADFILE_
#include "HeadFile.h"
#endif
#ifndef GLOBAL_FUNCTION_
#define GLOBAL_FUNCTION_
#include "Global_function.h"
#endif
#ifndef CSTRING_
#define CSTRING_
#include "Cstring.h"
#endif
#ifndef ARRAYOFCSTRING_H_
#define ARRAYOFCSTRING_H_
#include "arrayOfCstring.h"
#endif
class child
{
   public:
     child(){
	cellName=0;
        instanceName=0;
        param=0;
        connection =(ArrayCstring *)malloc(sizeof(ArrayCstring));
        ArrayCstringNew(connection,20);
	     };
     ~child(){
   	delete [] cellName;
   	delete [] instanceName;
   	delete [] param;
   	ArrayCstringDelete(connection);
   	free(connection);
	     };
     char *cellName;
     char *instanceName;
     char *param;
     ArrayCstring *connection;
     int calledTag;

};
class BaseNode
{
    public:
       BaseNode();
       ~BaseNode();
       BaseNode(const BaseNode &b);
       //virtual bool hasChild(){ return false;};
       bool isEmpty();
       bool hasChild();
       void initMemberVar(char *a,char *b);
       void addCstrToParentConneciton(char *cstr);
       void readingContent(string &content);
       void PortListExist();
       ChildrenPtr &getChildrenPtr();
       ChildrenPtr    children;
       ArrayCstring *connection; /* elem is "1A1.A2" or "2A1.A2", first 1 or 0 is show whether connection with port */
       char *vportList; // for example :  A1 A2 B1 B2 //seperated by space
       char *subcktName; 
       int tag;
       char *param;
             /*connection format is "@A1.A2%1@"  means that ownPin A1 connected calledPin A2, 1 is A2 is portName, @%. is sep*/
             /*connection format is "@A1.A2%0@"  means that ownPin A1 connected calledPin A2, 0 is A2 isn't portName,@%. is sep*/
       //char **connection;
       //size_t sizeOfConnection;
       /* parentConnection format is "{calledPin@netName}" */      
       //Array*parentConnection;
       //size_t SizeOfParentConnection;
       //char *parentName; 
       //char *parentInstanceName; 
       //Cstring *parentConnection;
       //Cstring *portConnection;
       //char *instanceName; 
       //char *relationship; 
     private:
       void buildConnectionCallByName(ArrayCstring *connection,string &line);
       //void buildConnectionCallByOrderWithParameter(pairArraySS &connection,string &line);
       void buildConnectionCallByOrderWithParameter(ArrayCstring *c,string &line);
       void buildConnectionCallByOrderWithoutParameter(ArrayCstring *connection,string &line);
       const char whetherCalledPinNameIsPortName(string &pinName,char *portList);
       void paserSubcktContentInSpice(std::string &content);
       void getChildrenFromSubcktContent(std::string &content);
       void getvPortList(std::string &subcktLine);
       void handleParameterInCallByOrder(string &line,pair<charPos,vector<pair<string,string> > > &returnHash);
};
