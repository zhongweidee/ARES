//class SubcktNode:public BaseNode
#ifndef HEADFILE_
#define HEADFILE_
#include "HeadFile.h"
#endif

class SubcktNode
{
    public:
       //SubcktNode():BaseNode(){};
       SubcktNode();
       ~SubcktNode();
       //SubcktNode(string &content);
       SubcktNode(const SubcktNode &s);
       void CopyFromBaseNode(BaseNode &s);
       void initMemberVar(char *a,char *b);
       Cstring *parentConnection;
       Cstring *portConnection;
       ChildrenPtr    children;
       ArrayCstring *connection; /* elem is "1A1.A2" or "2A1.A2", first 1 or 0 is show whether connection with port */
       char *vportList; // for example :  A1 A2 B1 B2 //seperated by space
       char *subcktName; 
       int tag;
       char *instanceName; 
       char *relationship; 
       bool isChild(SubcktNode &node);
       bool isBrother(SubcktNode &node);
       bool isSame(SubcktNode &s);
       bool hasTwoGenerations();
       bool hasChild();
       ChildrenPtr & getChildrenPtr();
       
   /*private:
       //void buildConnectionCallByOrderWithParameter(pairArraySS &connection,string &line);
       void buildConnectionCallByOrderWithParameter(ArrayCstring *c,string &line);
       void buildConnectionCallByOrderWithoutParameter(ArrayCstring *connection,string &line);
       const char whetherCalledPinNameIsPortName(string &pinName,char *portList);
       void paserSubcktContentInSpice(std::string &content);
       void getChildrenFromSubcktContent(std::string &content);
       void getvPortList(std::string &subcktLine);
       void handleParameterInCallByOrder(string &line,pair<charPos,vector<pair<string,string> > > &returnHash);
       */
};
