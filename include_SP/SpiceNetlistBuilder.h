#ifndef HEADFILE_
#define HEADFILE_
#include "HeadFile.h"
#endif
#ifndef BASENODE_
#define BASENODE_
#include "BaseNode.h"
#endif
#ifndef SUBCKTNODE_
#define SUBCKTNODE_
#include "SubcktNode.h"
#endif
#ifndef SPICENETLISTNODE_
#include "SpiceNetlistNode.h"
#define SPICENETLISTNODE_
#endif
#ifndef GF_
#define GF_
#include "../include_SP/GF.h"
#endif

class SpiceNetlistBuilder{
   public:
    //SpiceNetlistBuilder(string &netlistPath);
    SpiceNetlistBuilder(SpiceNetlistNode *s_node,Cstring *dList);
    ~SpiceNetlistBuilder();
    void   setTopCellName(string &c);
    string getTopCellName();
    void  startToBuild(size_t num,Cstring *netData);
    int   getNumOfNet(); 
    /* { relationship / calledPinName+relationship / calledPinName . netName}*/ 
    //string netDataBase;
    //char *netDataBase;
    Cstring *deviceList;
    Cstring *netDataBase;
//    char *netDataBaseDeviceLevel;
    //string netDataBaseDeviceLevel;
   private:
    //SubcktNodePtr topNodePtr;
    size_t current_element;
    size_t total_element;
    size_t indexOfNode;
    char *netDataBasePosPtr;
    int  netNum;
    int  subcktNodeTag;
    //void BuildNetArray(SubcktNodePtr &topNodePtr);
    void BuildNetArray();
    bool CheckWhetherIsXInstance(string instanceName);
    bool isConnectedByBrother(pairSS &brotherPinsPair,string &ownPin);
    bool isConnectedByParent(pairSS &parentPinsPair,string &ownPin);
    void addInformationToBaseNodeAndSubcktNode(SubcktNode &copyNode,SubcktNode &parentNode,child &c);
    void joinChar(const char *array[],size_t sizeOfArray,char *str);
    //void splitConnectionAndCreateNet(string &relationship,char *connection,const char *instanceName);
    bool CheckWhetherIsXInstance(const char* c);
   // void whetherNeedToCreateNet(string &relationship,pair<string,string>&p);
   /* void whetherNeedToCreateNet(string &relationship,
                                char *ownPin,
                                char *calledPin,
                                const char *instanceName);
                                //const char flag);*/
    void splitConnectionAndCreateNet(char *relationship,size_t lengthOfRelationship,
                                     ArrayCstring *conn,
                                     const char *instanceName,size_t lengthOfInstanceName,
                                     const char *parent_relationship,size_t lengthOfpa,
                                     Cstring *parentConn);
    void whetherNeedToCreateNet(const char *relationship,
                                size_t lengthOfr,
                                const char *ownPin,
                                size_t lengthOfo,
                                const char *calledPin,
                                size_t lengthOfc,
                                const char *instanceName,
                                size_t lengthOfi,
                                const char *parent_relationship,
                                size_t lengthOfp);
    BaseNode CreateSubcktNodeForDevice(child &c);
    bool CheckWhetherIsDevice(const char* c);
    SpiceNetlistNode *node;
    SubcktNodeArrayPtr arrayForNewSubcktNode; 
    SubcktNodePtr &getNodeFromSubcktNodeArray(const char *relationship);
    string topCellName;
    string relationshipAndIndex;  //format like: IO.io+20;
    void createNet(SubcktNode &s);
    //void whetherNeedToCreateNet(string &relationship,string &calledPinName);
    void createNetForTopCell(SubcktNode &s);
    void checkPortNumWhetherMatchWithConnectionNum(BaseNode &copyNode,child &c);
    bool CheckWhetherIsChild(SubcktNode &refN,string &relationship);
    bool CheckWhetherIsBrother(SubcktNode &refN,string &relationship);
    void addInformationToAllNode();
    void addInformationToDeviceLevel(BaseNode &copyNode,BaseNode &parentNode,child &c);
    //void addNetIfFindPortPin(string &relationship,
     //                        string &calledPinName,
      //                       string &ownPinName,
       //                      string &s_netName,
         //                    const char *instanceName,
        //                     string &database);
      
    void addNetIfFindPortPin(const char *relationship,
                             size_t &lengthOfre,
                             const char *calledPinName,
                             size_t &lengthOfca,
                             const char *ownPinName,
                             size_t &lengthOfow,
                             const char *s_netName,
                             size_t &lengthOfsn,
                             const char *instanceName,
                             size_t &lengthOfin,
                             char *dataBase,
                             const char *ownNet,
                             const char *calledNet,
		             const char *parent_relationship,
			     size_t &lengthOfpa_re,
                             string &paConn);
    void addNetInformation(const char *calledPinName,
                           const char *ownPinName,
                           char *dataBase,
                           const char *ownNet,
                           const char *calledNet,
                           const char *s_netName);
    void initDataBase();
    void addElementToDataBase(char *database,char *elem,size_t lengthOfelem);
    
    void createNetWhenNoConnectedPort(char *relationship,
                                      size_t lengthOfRe,
                                      char *ownPin,
                                      char *calledPin,
                                      SubcktNode &s);
    void createNetWhenConnectedPort(char *relationship,
                                    size_t lengthOfRe,
                                    char *ownPin,
                                    char *calledPin,
                                    Cstring *parentConn,
                                    SubcktNode &s);
    void createNetWhenConnectedPortDevice(char *relationship,
                                          size_t lengthOfRe,
                                          char *ownPin,
                                          char *calledPin,
                                          Cstring *pa);
   void createNetWhenNoConnectedPortDevice(char *relationship,
                                           size_t lengthOfRe,
                                           char *ownPin,
                                           char *calledPin);
    size_t getParentRelationshipLength(char *relationship);
    void addNetInfToDataBase(char *net1,char* net2,Cstring *dataBase);
    void coutNetNum(size_t tNum);
    
};
