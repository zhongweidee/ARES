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
#ifndef EXTRACTDEVICELIST_
#define EXTRACTDEVICELIST_
#include "ExtractDeviceList.h"
#endif
#ifndef BASENODE_
#define BASENODE_
#include "BaseNode.h"
#endif
#ifndef FUNCTIONOBJECT_
#define FUNCTIONOBJECT_
#include "../src/functionObject.cc"
#endif
//
//class SpiceNetlistNode:public Node
class SpiceNetlistNode
{
 public:
  // SpiceNetlistNode(std::string netlistPath);
   void   init(std::string netlistPath,Cstring *deviceList,const char * calibreLvsRulePath);
   void   replace_all_distinct(std::string&   str,const   std::string&   old_value,const   std::string&   new_value);
   std::string getNetlistName();
   //std::string getSubcktList();
   //std::string getSubcktContentByName(std::string name); 
   BaseNodePtr &getSubcktNodeByName(string &name);
   //mHashSSubcktNode &getSubcktMap();
   BaseNodeArrayPtr& getSubcktArray();
   vArrayString splitStringBy(std::string &str,std::string &delim); 
   bool PaserParameter(std::string &netlistContent);
   void buildTree(std::string &topcellName);
   vArrayString getSubcktNameArray();
   void CheckNetlistError(vArrayString &array);
 private:
   //mHashSSubcktNode  subcktMap;
   //vArraySubcktNode  subcktArray;
   //SubcktNodeArrayPtr subcktArray;
     BaseNodeArrayPtr subcktArray;
   //vArrayString deleteCommentLine(std::string netlistPath);
   vArrayString grepIncludeFileToArray(std::string &netlistPath);
   bool replaceParameter(string &netlistContent);
   //void StringFromNetlist(std::string netlistPath);
   bool deleteCommentWordLine(std::string &spiceLine);
   void SpiceReaderNoneIncludeFile(std::string &netlistPath);
   void replaceSpecialCharactor(string &netlistContent);
   std::string addSubcktKeyWord;
   std::string netlistName;
   mHashSS parameterHash;
   // string lastLine;
};

