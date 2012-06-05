#include "../include_SP/SpiceNetlistBuilder.h"
//SpiceNetlistBuilder::SpiceNetlistBuilder(string &netlistPath)
SpiceNetlistBuilder::SpiceNetlistBuilder(SpiceNetlistNode *s_node,Cstring *dList)
{
        netNum=0;
        indexOfNode =1;
        deviceList =dList;
        //node=&s_node; 
        subcktNodeTag=0;
        //node =new SpiceNetlistNode; 
        //(*node).init(netlistPath);
        node=s_node;
        //relationshipAndIndex="@I0+0";
}
SpiceNetlistBuilder::~SpiceNetlistBuilder()
{
 //delete node;
}
void SpiceNetlistBuilder::startToBuild(size_t num,Cstring *netData){
        if(topCellName.empty()){
           cout<<"Error: have not topCellName,Can't build"<<endl;
           exit(0);
                                } 
        BaseNodePtr topBaseNodePtr= (*node).getSubcktNodeByName(topCellName);	
        addInformationToAllNode();
        netDataBase=netData;
        //netDataBasePosPtr=netDataBase;
        current_element=0;
        total_element =num;
        BuildNetArray();
}

void SpiceNetlistBuilder::addInformationToBaseNodeAndSubcktNode(SubcktNode &copyNode,SubcktNode &parentNode,child &c){
                       copyNode.tag=++subcktNodeTag; // the tag from 1, tag 0 is original
                       //copyNode.subcktName = new char[strlen(c.cellName)+1];
                       //strcpy(copyNode.subcktName,c.cellName);
                       copyNode.instanceName =new char[strlen(c.instanceName)+1];
                       strcpy(copyNode.instanceName,c.instanceName);
                       int size =strlen(parentNode.relationship) ;
                           size =size +strlen(copyNode.instanceName)+2;
                       copyNode.relationship =new char[size];
                       strcpy(copyNode.relationship,parentNode.relationship);
                       strcat(copyNode.relationship,".");
                       strcat(copyNode.relationship,copyNode.instanceName);
                       copyNode.connection=(ArrayCstring *)malloc(sizeof(ArrayCstring));
                       ArrayCstringCopy(c.connection,copyNode.connection);
}

void SpiceNetlistBuilder::addInformationToAllNode()
{
         cout<<"LOG: start to addInformationToSubcktNode"<<endl;
         string subcktName =topCellName;
	 BaseNodePtr topBaseNodePtr=	 (*node).getSubcktNodeByName(topCellName);	
         SubcktNodePtr topNodePtr(new SubcktNode); 
         topNodePtr->CopyFromBaseNode(*topBaseNodePtr);
         (*topNodePtr).instanceName =new char[3];
         strcpy((*topNodePtr).instanceName,"I0");
         (*topNodePtr).relationship=new char[3];
         strcpy((*topNodePtr).relationship,"I0");
	 arrayForNewSubcktNode.push_back(topNodePtr);
         for(int b=0;(size_t)b<arrayForNewSubcktNode.size();++b){
             if((*arrayForNewSubcktNode[b]).hasChild()){
             ChildrenPtr ch =(*arrayForNewSubcktNode[b]).getChildrenPtr();
	     ChildrenPtrIter childrenPtrIter;
             for(childrenPtrIter=ch.begin();childrenPtrIter!=ch.end();++childrenPtrIter){ 
                     //string bufInstanceName((*(*childrenPtrIter)).instanceName);
                     if(CheckWhetherIsXInstance((*childrenPtrIter)->cellName)){
                       string bufCellName((*(*childrenPtrIter)).cellName);
                       SubcktNodePtr copyNodeFromSubcktNodePtr(new SubcktNode);
                       //*copyNodeFromSubcktNodePtr=*((*node).getSubcktNodeByName(bufCellName)) ;
		       copyNodeFromSubcktNodePtr->CopyFromBaseNode(*((*node).getSubcktNodeByName(bufCellName)));
                       addInformationToBaseNodeAndSubcktNode(*copyNodeFromSubcktNodePtr,(*arrayForNewSubcktNode[b]),(*(*childrenPtrIter)));
                       arrayForNewSubcktNode.push_back(copyNodeFromSubcktNodePtr);
		     }
		     /*else{
		       BaseNodePtr copyNodePtr(new BaseNode);
                       addInformationToBaseNodeAndSubcktNode(*copyNodePtr,(*arrayForNewSubcktNode[b]),(*(*childrenPtrIter)));
                       arrayForNewSubcktNode.push_back(copyNodePtr);
		     }*/
                                 } //for  
                                                  }//if
                              }//for
     cout<<"LOG: end to addInformationToAllNode"<<endl;
}

//void SpiceNetlistBuilder::BuildNetArray(SubcktNodePtr &topNodePtr){
void SpiceNetlistBuilder::BuildNetArray(){
/* check time of BuildNetArray */
       clock_t start,finish;
       start =clock(); 
/* check time of BuildNetArray */
           SubcktNodePtr topNodePtr=getNodeFromSubcktNodeArray("I0");
           string parentConnection;
           SubcktNodeArrayPtr array;
           array.push_back(topNodePtr);
          for(int a=0;(size_t)a<array.size();++a){
           char *parent_relationship=(*array[a]).relationship;
          if((strcmp(parent_relationship,"I0"))==0){
                createNetForTopCell(*array[a]); 
                                                  }
          else{
                createNet(*array[a]);
           }
           if((*array[a]).hasChild()){
                ChildrenPtr ch=(*array[a]).getChildrenPtr();
                   //const char *parentConnectionBuf=parentConnection.c_str();
                   cout<<"LOG: the children size is "<<ch.size()<<endl;
                   size_t numOfChildren=ch.size();
                   for(ChildrenPtrIter itOfChildrenPtr=ch.begin();itOfChildrenPtr<ch.end();++itOfChildrenPtr){
		     char *child_instanceName =(*itOfChildrenPtr)->instanceName;
                     int sizeOfC_node_relationship =strlen(parent_relationship)+strlen(child_instanceName)+2;
                     char c_node_relationship[sizeOfC_node_relationship]; 
                     memcpy(c_node_relationship,parent_relationship,strlen(parent_relationship));
                     memcpy(c_node_relationship+strlen(parent_relationship),".",1);
                     memcpy(c_node_relationship+strlen(parent_relationship)+1,child_instanceName,strlen(child_instanceName)+1);
                     //strcpy(c_node_relationship,parent_relationship);
                     //strcat(c_node_relationship,".");
                     //strcat(c_node_relationship,child_instanceName);

                      if(CheckWhetherIsXInstance((*itOfChildrenPtr)->cellName)){
                      SubcktNodePtr c_nodePtr =getNodeFromSubcktNodeArray(c_node_relationship);
                      //(*c_nodePtr).addCstrToParentConneciton(parentConnectionBuf);
                      Global_function::SNPuts("start to BuildNetArray");
                      //c_nodePtr->parentConnection =array[a]->portConnection;
		      CstringCopy(array[a]->portConnection,c_nodePtr->parentConnection);
                      array.push_back(c_nodePtr);
                                                   }
                      else{
                      ArrayCstring *connection=(*(*itOfChildrenPtr)).connection;
                      size_t lengthOfin=strlen(child_instanceName);
                      size_t lengthOfpa=strlen(parent_relationship);
                      size_t lengthOfre=strlen(c_node_relationship);
                      //splitConnectionAndCreateNet(c_node_relationship,lengthOfre,connection,child_instanceName,lengthOfin,parent_relationship,lengthOfpa,parentConnectionBuf);
                      splitConnectionAndCreateNet(c_node_relationship,lengthOfre,connection,child_instanceName,lengthOfin,parent_relationship,lengthOfpa,array[a]->portConnection);
                       }
                       coutNetNum(numOfChildren);
                                                  } 
                                  }
                                    }
                      Global_function::SNPuts("end to BuildNetArray");
/* check time of BuildNetArray */
  finish =clock();
  double totaltime;
  totaltime =(double)(finish-start)/CLOCKS_PER_SEC;
  cout<<"LOG:the run time of BuildNetArray "<<totaltime<<endl;

/* check time of BuildNetArray */
}

/*inline bool SpiceNetlistBuilder::CheckWhetherIsXInstance(string instanceName){
     if(instanceName.find(" ")!=string::npos){
       cout<<"Error: find the space in instanceName. "<<instanceName<<endl;
       exit(0);
                                                                 }
     //cout<<"LOG:end to checkWhetherIsXInstance"<<endl;
     if((instanceName.find("X")==0)||(instanceName.find("x")==0)){
          return true; 
                                                                 }
     else{
          return false;
          }
}*/

/*inline bool SpiceNetlistBuilder::CheckWhetherIsXInstance(const char* c){
           if((c[0]=='X')or(c[0]=='x')){
              return true;
                                  }
              return false;
}*/


inline bool SpiceNetlistBuilder::CheckWhetherIsXInstance(const char* c){
           //if((c[0]=='X')or(c[0]=='x')){
           char devicePattern[strlen(c)+3];
           GF::joinStr(devicePattern,3,"(",c,")");
           //if(Global_function::strstr(deviceList->elems,strlen(deviceList->elems),c,strlen(c))){
           if(strstr(deviceList->elems,devicePattern)){
              return false;
                                                                                               } 
              return true;
}


inline bool SpiceNetlistBuilder::CheckWhetherIsDevice(const char* c){
           if((c[0]=='X')or(c[0]=='x')){
              return false;
                                  }
              return true;
}

inline SubcktNodePtr &SpiceNetlistBuilder::getNodeFromSubcktNodeArray(const char *relationship){
        for(SubcktNodeArrayPtrIter it=arrayForNewSubcktNode.begin();it!=arrayForNewSubcktNode.end();++it){
         if(strcmp((*(*it)).relationship,relationship)==0){
               return *it;
                              }
             }
           //cout<<"Error:all relationship is "<< relationshipAndIndex<<endl;
           cout<<"Error: can't find the "<<relationship<<endl;
           assert(1);
} 

inline bool SpiceNetlistBuilder::isConnectedByParent(pairSS &parentPinsPair,string &ownPin){
		 if(parentPinsPair.first ==ownPin){
                         
			 return true;
			                 }
                  else{
	                 return false;
		          }
}

inline bool SpiceNetlistBuilder::isConnectedByBrother(pairSS &brotherPinsPair,string &ownPin){
	//pairArraySSIter it;
	//for(it=brotherPinsPair.begin();it!=brotherPinsPair.end();++it){
		 if((brotherPinsPair).second ==ownPin){
			 return true;
			                 }
                  else{
	                 return false;
		          }
}

inline bool SpiceNetlistBuilder::CheckWhetherIsChild(SubcktNode &refN,string &relationship){
    string refNrelationship(refN.relationship);
    if((refNrelationship.find(relationship)!=string::npos)&&(relationship!=refNrelationship)){
       return true;
    }
    else{
       return false;
    }
       
}

inline bool SpiceNetlistBuilder::CheckWhetherIsBrother(SubcktNode &refN,string &relationship){
     string refNrelationship(refN.relationship);
     size_t thisLastPointPos=relationship.rfind(".");
     size_t nodeLastPointPos=refNrelationship.rfind(".");
     string compareThisRelationship =relationship.substr(0,thisLastPointPos);
     string compareNodeRelationship =refNrelationship.substr(0,nodeLastPointPos);
     if(compareThisRelationship==compareNodeRelationship){
	     return true;
     }
     else{
	     return false;
     }

}
void SpiceNetlistBuilder::createNetForTopCell(SubcktNode &s){
     //if((strcmp(s.subcktName,topCellName.c_str()))==0){
     if(!Global_function::strcmp(s.subcktName,topCellName.c_str())){
        vArrayString portList; 
        string bufVportList(s.vportList);
        Global_function::vStringSplit(portList,bufVportList);
        size_t sizeOfPortList =portList.size();
        //s.portConnection=(Cstring *)malloc(sizeof(Cstring));
        //CstringNew(s.portConnection);
        //s.parentConnection=(Cstring *)malloc(sizeof(Cstring));
        //CstringNew(s.parentConnection);
        for(int a=0;(size_t)a<sizeOfPortList;++a){
	   const char *addNetNameBuf[7]={"{","I0","/",portList[a].c_str(),"@",portList[a].c_str(),"}"};	 
	   size_t lengthOfaddNetName =7+2*(portList[a].length());
	   char addNetName[lengthOfaddNetName];
	   joinChar(addNetNameBuf,7,addNetName);
          
           //addElementToDataBase(netDataBase,addNetName,lengthOfaddNetName-1);
     //printf("Debug: CstringAppend(netDataBase,addNetName,lengthOfaddNetName)\n");
           //CstringAppend(netDataBase,addNetName,lengthOfaddNetName);
           CstringAppend(netDataBase,addNetName);
           const char *portList_c= portList[a].c_str();
     //printf("Debug: CstringAppend(s.portConnection,)\n");
           CstringAppendMutiArg(s.portConnection,5,"{",portList_c,"@",portList_c,"}");
           /*CstringAppend(s.portConnection,"{",2);
     //printf("Debug: CstringAppend(s.portConnection,)\n");
           CstringAppend(s.portConnection,portList_c,portList[a].length()+1);
     //printf("Debug: CstringAppend(s.portConnection,)\n");
           CstringAppend(s.portConnection,"@",2);
     //printf("Debug: CstringAppend(s.portConnection,)\n");
           CstringAppend(s.portConnection,portList_c,portList[a].length()+1);
     //printf("Debug: CstringAppend(s.portConnection,)\n");
           CstringAppend(s.portConnection,"}",2);*/
                                        }
                                                  }
}

inline void SpiceNetlistBuilder::joinChar(const char *array[],size_t sizeOfArray,char *str)
{
  char *buf=str;
  for(size_t a=0;a<sizeOfArray-1;++a){
      memcpy(buf,array[a],strlen(array[a])); 
      buf=buf+strlen(array[a]);
                                } 
      memcpy(buf,array[sizeOfArray-1],strlen(array[sizeOfArray-1])+1);
}


void SpiceNetlistBuilder::splitConnectionAndCreateNet(char *relationship,size_t lengthOfRelationship,
                                                      ArrayCstring *conn,
                                                      const char *instanceName,size_t lengthOfInstanceName,
                                                      const char *parent_relationship,size_t lengthOfpa,
                                                      Cstring *parentConn){

     int a;
     int numOfA=conn->numOfElems;
     for(a=0;a<numOfA;++a){
     char *str = ArrayCstringIndex(conn,a);
     char *posOfPoint=strchr(str,'.'); 
     size_t lengthOfOwnPin=posOfPoint-str;
     char ownPin[lengthOfOwnPin];
     memcpy(ownPin,str+1,lengthOfOwnPin-1);
     ownPin[lengthOfOwnPin-1]='\0';
     char *calledPin=posOfPoint+1;
        switch (str[0]){
           case '1':
              //printf("Debug: 1 str is %s\n",str);
              createNetWhenConnectedPortDevice(relationship,lengthOfRelationship,ownPin,calledPin,parentConn);
                  break;
           case '0':
              //printf("Debug: 0 str is %s\n",str);
              createNetWhenNoConnectedPortDevice(relationship,lengthOfRelationship,ownPin,calledPin); 
              //coutNetNum();
                  break;
           default:
             assert(0);
             break;
                       }
                                                }
}
void SpiceNetlistBuilder::coutNetNum(size_t tNum){
                 netNum++;
                if(netNum%100==0){
                    cout<<"LOG:finish the children num is "<<netNum<<endl;
                                  }
}
inline size_t SpiceNetlistBuilder::getParentRelationshipLength(char *relationship) 
{
     char *posBOfParentRelationship = strrchr(relationship,'.');
     //size_t lengthOfpa=posBOfParentRelationship-relationship;
     return posBOfParentRelationship-relationship;
    
}
void SpiceNetlistBuilder::createNetWhenNoConnectedPort(char *relationship,
                                                       size_t lengthOfRe,
                                                       char *ownPin,
                                                       char *calledPin,
                                                       SubcktNode &s)
{
     size_t lengthOfpa=getParentRelationshipLength(relationship);
     char parent_relationship[lengthOfpa+1];
     //parent_relationship[lengthOfpa]='\0';
     memcpy(parent_relationship,relationship,lengthOfpa);
     size_t lengthOfNetName= lengthOfpa+2+strlen(calledPin);
     char netName[lengthOfNetName];
     memcpy(netName,parent_relationship,lengthOfpa);
     memcpy(netName+lengthOfpa,"/",1);
     memcpy(netName+lengthOfpa+1,calledPin,strlen(calledPin)+1);
      
     char calledPinNet[lengthOfRe+2+strlen(calledPin)];
     memcpy(calledPinNet,relationship,lengthOfRe);
     memcpy(calledPinNet+lengthOfRe,"/",1);
     memcpy(calledPinNet+lengthOfRe+1,calledPin,strlen(calledPin)+1);
     if(strlen(ownPin)==strlen(calledPin)){
        if(memcmp(ownPin,calledPin,strlen(ownPin))!=0){
            char ownPinNet[lengthOfRe+2+strlen(ownPin)];
            memcpy(ownPinNet,relationship,lengthOfRe);
            memcpy(ownPinNet+lengthOfRe,"/",1);
            memcpy(ownPinNet+lengthOfRe+1,ownPin,strlen(ownPin)+1);
            addNetInfToDataBase(ownPinNet,netName,netDataBase);
                     }
                                            }
     addNetInfToDataBase(calledPinNet,netName,netDataBase);
     //printf("Debug: CstringAppend(s.portConnection,)\n");
     CstringAppendMutiArg(s.portConnection,5,"{",ownPin,"@",netName,"}");
     /*CstringAppend(s.portConnection,"{",2);
     //printf("Debug: CstringAppend(s.portConnection,)\n");
     CstringAppend(s.portConnection,ownPin,strlen(ownPin)+1);
     //printf("Debug: CstringAppend(s.portConnection,)\n");
     CstringAppend(s.portConnection,"@",2);
     //printf("Debug: CstringAppend(s.portConnection,)\n");
     CstringAppend(s.portConnection,netName,strlen(netName)+1);
     //printf("Debug: CstringAppend(s.portConnection,)\n");
     CstringAppend(s.portConnection,"}",2);*/
}


void SpiceNetlistBuilder::createNetWhenNoConnectedPortDevice(char *relationship,
                                                       size_t lengthOfRe,
                                                       char *ownPin,
                                                       char *calledPin)
{
     size_t lengthOfpa=getParentRelationshipLength(relationship);
     char parent_relationship[lengthOfpa+1];
     //parent_relationship[lengthOfpa]='\0';
     memcpy(parent_relationship,relationship,lengthOfpa);
     size_t lengthOfNetName= lengthOfpa+2+strlen(calledPin);
     char netName[lengthOfNetName];
     memcpy(netName,parent_relationship,lengthOfpa);
     memcpy(netName+lengthOfpa,"/",1);
     memcpy(netName+lengthOfpa+1,calledPin,strlen(calledPin)+1);
      
     char calledPinNet[lengthOfRe+2+strlen(calledPin)];
     memcpy(calledPinNet,relationship,lengthOfRe);
     memcpy(calledPinNet+lengthOfRe,"/",1);
     memcpy(calledPinNet+lengthOfRe+1,calledPin,strlen(calledPin)+1);
     if(Global_function::strcmp(ownPin,calledPin)!=0){
            char ownPinNet[lengthOfRe+2+strlen(ownPin)];
            memcpy(ownPinNet,relationship,lengthOfRe);
            memcpy(ownPinNet+lengthOfRe,"/",1);
            memcpy(ownPinNet+lengthOfRe+1,ownPin,strlen(ownPin)+1);
            addNetInfToDataBase(ownPinNet,netName,netDataBase);
                     }
     addNetInfToDataBase(calledPinNet,netName,netDataBase);
}
void SpiceNetlistBuilder::createNetWhenConnectedPort(char *relationship,
                                                     size_t lengthOfRe,
                                                     char *ownPin,
                                                     char *calledPin,
                                                     Cstring *pa,
                                                     SubcktNode &s)
{
     size_t lengthOfCalledPin=strlen(calledPin);
     char searchPattern[lengthOfCalledPin+3];
     searchPattern[lengthOfCalledPin+2]='\0';
     memcpy(searchPattern,"{",1);
     memcpy(searchPattern+1,calledPin,lengthOfCalledPin);
     memcpy(searchPattern+1+lengthOfCalledPin,"@",1);
     char *parentConn= pa->elems;
     char *posOfAOri=strstr(parentConn,searchPattern);
     assert(posOfAOri!=0);
     char *posOfA=posOfAOri+strlen(searchPattern);
     char *posOfB=strchr(posOfA,'}');
     assert(posOfB!=0);
     char netName[posOfB-posOfA+1];
     netName[posOfB-posOfA]='\0';
     memcpy(netName,posOfA,(posOfB-posOfA));
     char ownPinNet[lengthOfRe+2+strlen(ownPin)];
     memcpy(ownPinNet,relationship,lengthOfRe); 
     memcpy(ownPinNet+lengthOfRe,"/",1); 
     memcpy(ownPinNet+lengthOfRe+1,ownPin,strlen(ownPin)+1); 
     if(Global_function::strcmp(ownPin,calledPin)!=0){
     char calledPinNet[lengthOfRe+2+lengthOfCalledPin];
     memcpy(calledPinNet,relationship,lengthOfRe); 
     memcpy(calledPinNet+lengthOfRe,"/",1); 
     memcpy(calledPinNet+lengthOfRe+1,calledPin,lengthOfCalledPin+1); 
     addNetInfToDataBase(calledPinNet,netName,netDataBase);
     } 
     addNetInfToDataBase(ownPinNet,netName,netDataBase);
     //printf("Debug: CstringAppend(s.portConnection,)\n");
     CstringAppendMutiArg(s.portConnection,5,"{",ownPin,"@",netName,"}");
     /*CstringAppend(s.portConnection,"{",2);
     //printf("Debug: CstringAppend(s.portConnection,)\n");
     CstringAppend(s.portConnection,ownPin,strlen(ownPin)+1);
     //printf("Debug: CstringAppend(s.portConnection,)\n");
     CstringAppend(s.portConnection,"@",2);
     //printf("Debug: CstringAppend(s.portConnection,)\n");
     CstringAppend(s.portConnection,netName,strlen(netName)+1);
     //printf("Debug: CstringAppend(s.portConnection,)\n");
     CstringAppend(s.portConnection,"}",2);*/
}



void SpiceNetlistBuilder::createNetWhenConnectedPortDevice(char *relationship,
                                                     size_t lengthOfRe,
                                                     char *ownPin,
                                                     char *calledPin,
                                                     Cstring *pa)
{

     char searchPattern[strlen(calledPin)+3];
     memcpy(searchPattern,"{",1);
     memcpy(searchPattern+1,calledPin,strlen(calledPin));
     memcpy(searchPattern+1+strlen(calledPin),"@",2);
     //memcpy(searchPattern+1+2*strlen(calledPin),calledPin,strlen(calledPin)+1);
     //char *posOfAOri=strstr(parentConn,searchPattern);
     char *parentConn=pa->elems;
     char *posOfAOri=strstr(parentConn,searchPattern);
     if(posOfAOri==0){
     printf("Debug: parentConn is %s \nsearchPattern is %s\n",parentConn,searchPattern);
                     }
     assert(posOfAOri!=0);
     char *posOfA=posOfAOri+strlen(searchPattern);
     char *posOfB=strchr(posOfA,'}');
     assert(posOfB!=0);
     char netName[posOfB-posOfA+1];
     netName[posOfB-posOfA]='\0';
     memcpy(netName,posOfA,(posOfB-posOfA));
     char ownPinNet[lengthOfRe+2+strlen(ownPin)];
     memcpy(ownPinNet,relationship,lengthOfRe); 
     memcpy(ownPinNet+lengthOfRe,"/",1); 
     memcpy(ownPinNet+lengthOfRe+1,ownPin,strlen(ownPin)+1); 
     if(Global_function::strcmp(ownPin,calledPin)){
     char calledPinNet[lengthOfRe+2+strlen(calledPin)];
     memcpy(calledPinNet,relationship,lengthOfRe); 
     memcpy(calledPinNet+lengthOfRe,"/",1); 
     memcpy(calledPinNet+lengthOfRe+1,calledPin,strlen(calledPin)+1); 
     addNetInfToDataBase(calledPinNet,netName,netDataBase);
     } 
     addNetInfToDataBase(ownPinNet,netName,netDataBase);
}

void SpiceNetlistBuilder::addNetInfToDataBase(char *net1,char* net2,Cstring *dataBase){
     size_t lengthOfNet =strlen(net1)+strlen(net2)+4; 
     char net[lengthOfNet];
     const char *netBuf[5]={"{",net1,"@",net2,"}"};
     joinChar(netBuf,5,net);
     //addElementToDataBase(dataBase,net,lengthOfNet-1);
     //printf("Debug:CstringAppend(dataBase,net,lengthOfNet)\n");
     //CstringAppend(dataBase,net,lengthOfNet-1);
     CstringAppend(dataBase,net);
}

void SpiceNetlistBuilder::createNet(SubcktNode &s){
     //s.portConnection=(Cstring *)malloc(sizeof(Cstring));
     //CstringNew(s.portConnection);
     char *relationship=s.relationship;
     //char *instanceName=s.instanceName;
     ArrayCstring *conn=s.connection;
     size_t lengthOfRelationship=strlen(relationship);
     //size_t lengthOfInstanceName=strlen(instanceName);
     char *a_posOfParentRelationship = (char *)memchr(relationship,'.',lengthOfRelationship);
     size_t lengthOfpa=a_posOfParentRelationship-relationship;
     char parent_relationship[lengthOfpa+1];
     parent_relationship[lengthOfpa]='\0';
     memcpy(parent_relationship,relationship,lengthOfpa);
     //memcpy(parent_relationship+lengthOfpa,"\0",1);
     int a;
     int numOfA=conn->numOfElems;
     for(a=0;a<numOfA;++a){
     char *str = ArrayCstringIndex(conn,a);
     char *posOfPoint=strchr(str,'.'); 
     size_t lengthOfOwnPin=posOfPoint-str-1;
     char ownPin[lengthOfOwnPin+1];
     ownPin[lengthOfOwnPin]='\0';
     memcpy(ownPin,str+1,lengthOfOwnPin);
     //memcpy(ownPin,'\0',1);
     char *calledPin=posOfPoint+1;
        switch (str[0]){
           case '1':
              createNetWhenConnectedPort(relationship,lengthOfRelationship,ownPin,calledPin,s.parentConnection,s); 
                  break;
           case '0':
              createNetWhenNoConnectedPort(relationship,lengthOfRelationship,ownPin,calledPin,s); 
              //coutNetNum();
                  break;
           default:
             assert(0);
             break;
                       }
                                                }
}

void SpiceNetlistBuilder::setTopCellName(string &c)
{
        if(!topCellName.empty()){
           cout<<"Error: already have topCellName->"<<topCellName<<endl;
           exit(0);
                                } 
         topCellName=c;
}

string SpiceNetlistBuilder::getTopCellName()
{
        if(topCellName.empty()){
           cout<<"Error: have not topCellName"<<endl;
           exit(0);
                                } 
        return topCellName;
}

