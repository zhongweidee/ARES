#include "../include_SP/BaseNode.h"
#include "../include_SP/SubcktNode.h"
// SubcktNode class implement
//SubcktNode::SubcktNode(std::string &content)
BaseNode::BaseNode(){
   tag=0;
   param=0;
   connection =(ArrayCstring *)malloc(sizeof(ArrayCstring));
   ArrayCstringNew(connection,20);
   vportList=0; // for example :  A1 A2 B1 B2 //seperated by space
   subcktName=0; 
}

SubcktNode::SubcktNode(){
   portConnection=(Cstring *)malloc(sizeof(Cstring));
   CstringNew(portConnection);
   parentConnection=(Cstring *)malloc(sizeof(Cstring));
   CstringNew(parentConnection);
   instanceName=0; 
   relationship=0; 
}

/*SubcktNode::SubcktNode(std::string &content){
	readingContent(content);
}*/
void BaseNode::readingContent(std::string &content)
{
  cout<<"LOG: start to setRelationship"<<endl;
  //setRelationship("I0");
  cout<<"LOG: end to setRelationship"<<endl;
  getChildrenFromSubcktContent(content);
  //cout<<"LOG: children num is  "<<children.size()<<endl;
  //cout<<"LOG: yyy cellName is "<<(*(children[0])).cellName<<" instanceName is "<<(*(children[0])).instanceName<<endl;
  //Global_function::Puts("LOG: end to 
}

void BaseNode::PortListExist()
{
  if(vportList ==0){
    cout<<"Error:can't find the PortList cellName:"<<subcktName<<endl;
    exit(0);
                        }
}
void BaseNode::handleParameterInCallByOrder(string &line,pair<charPos,vector<pair<string,string> > > &returnHash)
{
	//cout<<"LOG:start to handleParameterInCallByOrder"<<endl;
    if(line.find("=")==string::npos){
       cout<<"Error: why need to handleParameterInCallByOrder "<<line<<endl;
       exit(0);
                                    }
    //parameterHash hash;
    //mHashSS hash;
    charPos charpos=0;
    size_t charpos_equal =line.find("=");
    size_t varPos =line.find_last_not_of(" ",charpos_equal);
    charpos= line.find_last_not_of(" ",line.find_last_of(" ",varPos));
    size_t posA=0;
    //vArrayString parameterHash; 
    //cout<<"LOG: start to while"<<endl;
    while((posA!=string::npos)&&(line.find("=",posA)!=string::npos)){
	    //cout<<"LOG:posA is "<<posA<<endl;
	    //cout<<"LOG:line is "<<line<<endl;
    string varName,paraValue;
    size_t posB=line.find("=",posA);
    size_t varNamePosB=line.find_last_not_of(" ",posB);
    size_t varNamePosA=line.find_last_of(" ",varNamePosB);
    size_t paraValuePosA=line.find_first_not_of(" ",posB);
    size_t paraValuePosB=line.find_first_of(" \n",paraValuePosA);
    varName =line.substr(varNamePosA,varNamePosB-varNamePosA); 
    paraValue=line.substr(paraValuePosA,paraValuePosB-paraValuePosA);
    returnHash.second.push_back(make_pair(varName,paraValue));
    posA=paraValuePosB;
                                       }
    //cout<<"LOG: end to while"<<endl;
    returnHash.first=charpos;
}
    
ChildrenPtr &BaseNode::getChildrenPtr()
{
    return children;
}
ChildrenPtr &SubcktNode::getChildrenPtr()
{
    return children;
}

/*Children BaseNode::getChildren()
{
        if(!hasChild()){
          cout<<"Error: no Child in "<<*subcktName<<endl;
          exit(0);
                       }
        //children.clear();
	Children ch_return;
        ChildrenPtrIter it;	
	for(it=children.begin();it!=children.end();++it){
           //child buf_child =**it;
           ch_return.push_back(**it);
       //    cout<<"LOG: push_back "<<(**it).cellName<<endl;
           //cout<<"LOG: getChildren "<<ch[0].cellName<<endl;
	}	
           cout<<"LOG: getChildren "<<ch_return[0].cellName<<endl;
           cout<<"LOG: getChildren "<<ch_return[1].cellName<<endl;

   //transform(children.begin(),children.end(),ch.begin(),Global_function::ChildPtrToChild );
   return ch_return;
}*/
void BaseNode::getChildrenFromSubcktContent(std::string &content)
{
   //cout<<"LOG:start to getChildrenFromSubcktContent"<<endl;
   Global_function::SNPuts("start to getChildrenFromSubcktContent");
   int sizeOfChildren = Global_function::CoutNumOfLineInString(content);
   children.reserve(sizeOfChildren);
   std::string line;
   size_t  numOfBit=0;
   stringstream streamL(content);   
   content.clear();
   string().swap(content);
   while(getline(streamL,line,'\n'))
   {
    if(!line.empty()){
       string instanceName =Global_function::GetFirstElementInLine(line);
     if(Global_function::checkStringHasWhiteSpace(instanceName)){
                 cout<<"Error: the instanceName have white space:"<<instanceName<<endl;
                 exit(0);
     }
     if((line.find("SUBCKT")==string::npos)&&(line.find(".ENDS")==string::npos)){
         if(line.find("$PINS")!=string::npos){ //called by Name
           PortListExist();
	    boost::shared_ptr<child> ptrChild(new child);
            string *cellName=new string(Global_function::GetSecondElementInLine(line));
             
            (*ptrChild).cellName=new char [(*cellName).size() +1]; 
            strcpy((*ptrChild).cellName,(*cellName).c_str());
            delete cellName;
            (*ptrChild).instanceName=new char [instanceName.size() +1]; 
            strcpy((*ptrChild).instanceName,instanceName.c_str());
            (*ptrChild).calledTag=callByName;
            //ArrayCstringNew(ptrChild->connection,2*line.length());
            buildConnectionCallByName((*ptrChild).connection,line);
            children.push_back(ptrChild); 
	 }
         else{ //called by Order
           PortListExist();
	    if(line.find("=")!=string::npos){ //have "=" parameter
	       pair<charPos,vector<pair<string,string> > > *hash= new  pair<charPos,vector<pair<string,string> > >;
	       handleParameterInCallByOrder(line,*hash);
	       boost::shared_ptr<child> ptrChild(new child);
               size_t cellNameStringEndPos= line.find_last_not_of(" ",(*hash).first);
               delete hash;
               size_t cellNameStringStartPos= line.find_last_of(" ",cellNameStringEndPos)+1;
               string cellName =line.substr(cellNameStringStartPos,cellNameStringEndPos-cellNameStringStartPos+1);
               if(Global_function::checkStringHasWhiteSpace(cellName)){
                 cout<<"Error: the cellName have white space:"<<cellName<<endl;
                 exit(0);
                                                      }
                (*ptrChild).cellName=new char [cellName.size() +1]; 
		strcpy((*ptrChild).cellName,cellName.c_str());
                (*ptrChild).instanceName=new char [instanceName.size() +1]; 
		strcpy((*ptrChild).instanceName,instanceName.c_str());
                (*ptrChild).calledTag=callByOrder;
                //ArrayCstringNew(ptrChild->connection,2*line.length());
                buildConnectionCallByOrderWithParameter(ptrChild->connection,line); //for test
                numOfBit=numOfBit + sizeof(*ptrChild);
                children.push_back(ptrChild); // instance name => cellName
                }
           else{//don't have the parameter
                cout<<"LOG:don't have parameter "<<endl;
	        boost::shared_ptr<child> ptrChild(new child);
                (*ptrChild).calledTag=callByOrder;
                string *cellNameBuf =new string(Global_function::GetFirstLastElementInLine(line));
                (*ptrChild).cellName=new char [(*cellNameBuf).size() +1]; 
                strcpy((*ptrChild).cellName,(*cellNameBuf).c_str());
                delete cellNameBuf;
                (*ptrChild).instanceName=new char [instanceName.size() +1]; 
		strcpy((*ptrChild).instanceName,instanceName.c_str());
                //pairArraySS *bufConnection =new pairArraySS;
                //(*ptrChild).connection =new char [Global_function::coutCharNumOfPariArraySS(*bufConnection)];
                //Global_function::assignPairArraySSToCharAddress(*bufConnection,(*ptrChild).connection);
                //delete bufConnection;
                //ArrayCstringNew(ptrChild->connection,2*line.length());
                buildConnectionCallByOrderWithoutParameter(ptrChild->connection,line);
                children.push_back(ptrChild); // instance name => cellName
               }
              }//else
      
                            }//if
    else if(line.find(".ENDS")==string::npos){
    size_t posSubcktA =line.find_first_not_of(" ",line.find("SUBCKT")+6);
    size_t posSubcktB =line.find(" ",posSubcktA)-1;
    string cellName =line.substr(posSubcktA,posSubcktB-posSubcktA+1);
    subcktName = new char[cellName.size()+1];
    strcpy(subcktName,cellName.c_str());
    if(cellName.find(" ")!=string::npos){
    cout<<"Error: subcktName have space. "<<cellName<<" PosA:"<<posSubcktA<<" PosB:"<<posSubcktB<<endl;
    exit(0);
                                          }
    //delete cellName;
    cout<<"LOG: subcktName is "<<subcktName<<endl;
    getvPortList(line); 
         }//else
     }//if 
    }//while
   Global_function::SNPuts("end to getChildrenFromSubcktContent");
}

inline bool BaseNode::hasChild()
{
  if(children.empty()){
      return false;
   }
  else{
      return true;
      }
}

bool SubcktNode::hasChild()
{
  if(children.empty()){
      return false;
   }
  else{
      return true;
      }
}
bool SubcktNode::isChild(SubcktNode &node)
{
   string thisRelationship(relationship);
   string nodeRelationship(node.relationship); 
   //Global_function::SNPuts(subcktName+" thisRelationship is "+thisRelationship);
   //Global_function::SNPuts(node.getSubcktName()+" nodeRelationship is "+nodeRelationship);
   //cout<<"LOG: "<<getSubcktName()<<" thisRelationship is "<<thisRelationship<<endl;
   //cout<<"LOG: "<<node.getSubcktName()<<" nodeRelationship is "<<nodeRelationship<<endl;
   if (thisRelationship.empty()){
	   cout<<"Error:"<<subcktName<<"don't have relationship"<<endl;
	   exit(0);
   }
   if (nodeRelationship.empty()){
	   cout<<"Error:"<<node.subcktName<<"don't have relationship"<<endl;
	   exit(0);
   }
    if((thisRelationship.find(nodeRelationship)!=string::npos)&&(thisRelationship!=nodeRelationship)){
       return true;
    }
    else{
       return false;
    }
}
bool SubcktNode::isBrother(SubcktNode &node){
   string thisRelationship(relationship); 
   string nodeRelationship(node.relationship); 

   /*if(thisRelationship.find(".")==string::npos){
	   return false;
   }*/
   if((nodeRelationship.find(".")==string::npos)&&(nodeRelationship!="I0")){
	   cout<<"Error:why send the "<<node.subcktName<<" to isBrother"<<endl;
	   exit(0);
   }
     size_t thisLastPointPos=thisRelationship.rfind(".");
     size_t nodeLastPointPos=nodeRelationship.rfind(".");
     string compareThisRelationship =thisRelationship.substr(0,thisLastPointPos);
     string compareNodeRelationship =nodeRelationship.substr(0,nodeLastPointPos);
     if(compareThisRelationship==compareNodeRelationship){
	     return true;
     }
     else{
	     return false;
     }
}
bool SubcktNode::hasTwoGenerations()
{
   string thisRelationship(relationship); 
   if(thisRelationship.find(".")==string::npos){
	   return false;
   }
   else{
       return true;
        }
}

/*bool SubcktNode::isFatherBrother(SubcktNode &node){
   if(this->hasTwoGenerations()||node.hasTwoGenerations()){
      cout<<"Error: the two nodes don't have the two generation "<<node.subcktName<<" "<<subcktName);  
                                                         }
   string thisRelationship = this->getRelationship(); 
   string nodeRelationship = node.getRelationship(); 
   size_t firstPointPosInThis = thisRelationship.rfind(".");
   size_t secondPointPosInThis = thisRelationship.rfind(".",firstPointPosInThis-1);
   string thisRelationshipBeforeSecondPoint=thisRelationship.substr(0,secondPointPosInThis);   
   //size_t firstPointPosInNode = nodeRelationship.rfind(".");
   //size_t secondPointPosInNode = nodeRelationship.rfind(".",firstPointPosInNode-1);
   string nodeRelationshipBeforeSecondPoint=nodeRelationship.substr(0,secondPointPosInThis);   
   if(thisRelationshipBeforeSecondPoint==nodeRelationshipBeforeSecondPoint){
        return true;
       }
   else{
        return false;
        }
}
*/
/*bool SubcktNode::isDescendantOf(SubcktNode &node){
   if(this->hasTwoGenerations()||node.hasTwoGenerations()){
      cout<<"Error: the two nodes don't have the two generation "<<node.getSubcktName()<<" "<<this->getSubcktName();  
                                                         }
   string thisRelationship = this->getRelationship(); 
   string nodeRelationship = node.getRelationship(); 
   if(nodeRelationship.find(thisRelationship)!=string::npos){
          return true;
                                           }
   else{
          return false;
       }
}
*/
bool BaseNode::isEmpty()
{
       if(subcktName==0){
         return true;
                             }
       else{
         return false;
           }
}


void BaseNode::buildConnectionCallByName(ArrayCstring *connection,string &line){
    size_t posA=0;
    while((line.find("=",posA)!=string::npos)&&(posA!=string::npos)){
    string ownPin,parentPin;
    size_t posB=line.find("=",posA);
    size_t ownPinPosB=line.find_last_not_of(" ",posB);
    size_t ownPinPosA=line.find_last_of(" ",ownPinPosB)+1;
    size_t parentPinPosA=line.find_first_not_of(" ",posB+1);
    size_t parentPinPosB=line.find_first_of(" \n",parentPinPosA);
    ownPin   =line.substr(ownPinPosA,ownPinPosB-ownPinPosA); 
    parentPin=line.substr(parentPinPosA,parentPinPosB-parentPinPosA);
    size_t lengthOfOwnPin=ownPin.length();
    size_t lengthOfparentPin=parentPin.length();
    const char flag=whetherCalledPinNameIsPortName(parentPin,vportList);
    char addInformation[lengthOfOwnPin+lengthOfparentPin+3]; 
    memcpy(addInformation,&flag,1);
    memcpy(addInformation+1,ownPin.c_str(),lengthOfOwnPin);
    memcpy(addInformation+1+lengthOfOwnPin,".",1);
    memcpy(addInformation+2+lengthOfOwnPin,parentPin.c_str(),lengthOfparentPin+1);
    ArrayCstringPush(connection,addInformation,strlen(addInformation));
    //connection.push_back(make_pair(ownPin,parentPin));
    if(parentPinPosB >posA){
    posA=parentPinPosB;
                           }
    else{
     cout<<"Error:"<<__FILE__<<" line"<<__LINE__<<" parentPinPosB need larger than posA"<<endl;
     cout<<"Error: posA is "<<posA<<" parentPinPosB is "<<parentPinPosB<<endl;
     cout<<"Error: line is "<<line<<endl;
     exit(0);
        }
                                       }
    ArrayCstringPrintAllElems(connection);
}      

const char BaseNode::whetherCalledPinNameIsPortName(string &pinName,char *p){
     size_t lengthOfP=strlen(p);
     size_t lengthOfPortList=lengthOfP+3;
     size_t lengthOfPinName =pinName.length();
     size_t lengthOfSearchPattern=lengthOfPinName+2;
     char portList[lengthOfPortList];
     memcpy(portList," ",1);
     memcpy(portList+1,p,lengthOfP);
     memcpy(portList+lengthOfP+1," ",2);
     char searchPattern[lengthOfSearchPattern];
     memcpy(searchPattern," ",1);
     memcpy(searchPattern+1,pinName.c_str(),lengthOfPinName);
     memcpy(searchPattern+lengthOfPinName+1," ",2);
     /*if(portList.empty()){
     cout<<"Error: the portList is empty!"<<endl;
     exit(0);
                         }*/
     //if(portList.find(searchPattern)!=string::npos){
     if(Global_function::strstr(portList,lengthOfPortList,searchPattern,lengthOfSearchPattern)){
     //printf("Debug: find portlist is %s\n, searchPattern is %s\n",portList,searchPattern);
         return '1';
         //return true;
                                      }
     else{
     //printf("Debug: nofind portlist is %s\n, searchPattern is %s\n",portList,searchPattern);
         //pinName.append("%0");
         return '0';
          }
}


void BaseNode::buildConnectionCallByOrderWithParameter(ArrayCstring *c,string &line){
     if(line.find("=")==string::npos){
        cout<<"Error: can't find = in line:"<<line<<endl;   
        exit(0);
                                      }
     size_t posB= line.find_last_of(" ",line.find_last_not_of(" ",line.find_last_of(" ",line.find_last_not_of(" ",line.find("=")))));
     size_t posA =line.find_first_of(" ",line.find_first_not_of(" "));
     
     string *prueConnectionString=new string(line.substr(posA,posB-posA)); 
     if((*prueConnectionString).find("=")!=string::npos){
        cout<<"Error: not clear seperate the line "<<line.substr(0,posB)<<endl;   
        exit(0);
                                                     }
     size_t posBB=0;
     size_t posAA=0;
     int flagTerm=0;
     while((posAA!=string::npos)&&((*prueConnectionString).find_first_not_of(" ",posAA)!=string::npos)){
	  posAA=(*prueConnectionString).find_first_not_of(" ",posAA);
          posBB=(*prueConnectionString).find(" ",posAA) -1;
	  if((posAA!=string::npos)&&(posBB!=string::npos)){
          string calledPinName =(*prueConnectionString).substr(posAA,posBB-posAA+1);
          const char flag=whetherCalledPinNameIsPortName(calledPinName,vportList);
          size_t lengthOfCalledPinName = calledPinName.length();
          char pinInformation[lengthOfCalledPinName+4];
          char ownPin =Global_function::intToChar(flagTerm);
          memcpy(pinInformation,&flag,1);
          memcpy(pinInformation+1,&ownPin,1);
          memcpy(pinInformation+2,".",1);
          memcpy(pinInformation+3,calledPinName.c_str(),lengthOfCalledPinName+1);
	  //c.push_back(make_pair(Global_function::intToString(flagTerm),calledPinName));
          ArrayCstringPush(c,pinInformation,strlen(pinInformation));
	  ++flagTerm;
          posAA=posBB+1; 
	  }
     }
     //cout<<"LOG: end to while"<<endl;
   delete prueConnectionString;
}
void BaseNode::buildConnectionCallByOrderWithoutParameter(ArrayCstring *c,string &line){
     if(line.find("=")!=string::npos){
        cout<<"Error: find = in line:"<<line<<endl;   
        exit(0);
                                      }
     vArrayString array;
     Global_function::vStringSplit(line,array); 
     size_t size =array.size();
     for(int a=1;(size_t)a<size-1;++a){
     //string a_s=Global_function::intToString(a); 
     char ownPin=Global_function::intToChar(a);
     const char flag  =whetherCalledPinNameIsPortName(array[a],vportList);
     char addInformation[4+array[a].length()];
     memcpy(addInformation,&flag,1);
     memcpy(addInformation+1,&ownPin,1);
     memcpy(addInformation+2,".",1);
     memcpy(addInformation+3,array[a].c_str(),array[a].length()+1);
     ArrayCstringPush(c,addInformation,4+array[a].length());  
     //c.push_back(make_pair(a_s,array[a]));
                              }
}

void BaseNode::getvPortList(std::string &subcktLine){
        if(subcktLine.find("+")!=string::npos){
              cout<<"Error: error format in "<<subcktName<<endl;
              exit(0);
                                              }     
        if(subcktLine.find("subckt")!=string::npos){ 
              cout<<"Error: error format find subckt or not find SUBCKT in "<<subcktName<<endl;
              exit(0);
                                                   }
        string portLine;
        if(subcktLine.find("=")!=string::npos){
          size_t posB=subcktLine.find_last_of(" ",subcktLine.find_last_not_of(" ",subcktLine.find("=")));
          size_t posA=subcktLine.find(" ",subcktLine.find_first_not_of(" ",subcktLine.find(" ",subcktLine.find("SUBCKT")))); 
          //size_t posA=subcktLine.find(" ",subcktLine.find("SUBCKT")); 
          portLine= subcktLine.substr(posA,posB-posA);
                                              }
        else{
          //size_t posA=subcktLine.find(" ",subcktLine.find("SUBCKT")); 
          size_t posA=subcktLine.find(" ",subcktLine.find_first_not_of(" ",subcktLine.find(" ",subcktLine.find("SUBCKT")))); 
          portLine= subcktLine.substr(posA);
            }
          Global_function::deleteSpaceInStartAndEnd(portLine);
          //setvPortArray(portLine);
          portLine=" "+portLine;//for split later
          vportList = new char[portLine.size()+1];
          strcpy(vportList,portLine.c_str());
          //vArrayString vportList_temp;
          //Global_function::vStringSplit(portLine,vportList_temp);
}

bool  SubcktNode::isSame(SubcktNode &s){
      if(((tag ==0 )&&(relationship==0))||((s.tag==0)&&(s.relationship!=0))){
           cout<<"Error: the tag is 0,haven't be set. cellName:"<<subcktName<<" or cellName: "<<s.subcktName<<endl;
           exit(0);
                   }
         return tag;
      if(tag == s.tag){
           return true;
                                 }    
      else{
          return false;
          }
}

void SubcktNode::CopyFromBaseNode(BaseNode &s){
       children=s.children;
       //connection=(ArrayCstring *)malloc(sizeof(ArrayCstring));
       //ArrayCstringNew(connection,20);
       //ArrayCstringCopy(s.connection,connection);
       vportList =strdup(s.vportList); 
       subcktName =strdup(s.subcktName);
       //tag =s.tag;
       //param=strdup(s.param);
}

SubcktNode::~SubcktNode(){
	if(strcmp(relationship,"I0")!=0){
	ArrayCstringDelete(connection);
        free(connection);
	}
	CstringDelete(parentConnection);
	free(parentConnection);
	CstringDelete(portConnection);
	free(portConnection);
	delete [] instanceName;
	delete [] relationship;
	free(vportList);
	free(subcktName);
	//delete [] subcktName;
}

BaseNode::~BaseNode(){
   delete [] subcktName;
   delete [] vportList;
   ArrayCstringDelete(connection);
   free(connection);
}
void BaseNode::initMemberVar(char *a,char *b){
    if(b==0){
    cout<<" b is NULL"<<endl;
             }
    if(b!=0){
    cout<<" b is not NULL "<<b<<endl;
    a= new char[strlen(b)+2]; 
    strcpy(a,b);
    cout<<" a is "<<a<<endl;
             }
    
}

void SubcktNode::initMemberVar(char *a,char *b){
    if(b==0){
    cout<<" b is NULL"<<endl;
             }
    if(b!=0){
    cout<<" b is not NULL "<<b<<endl;
    a= new char[strlen(b)+2]; 
    strcpy(a,b);
    cout<<" a is "<<a<<endl;
             }
    
}
BaseNode::BaseNode(const BaseNode &b){
      initMemberVar(vportList,b.vportList);
      initMemberVar(subcktName,b.subcktName);
}



SubcktNode::SubcktNode(const SubcktNode &b){
      //initMemberVar(param,b.param);
      //initMemberVar(connection,b.connection);
      //initMemberVar(parentName,b.parentName);
//      initMemberVar(instanceName,b.instanceName);
      initMemberVar(instanceName,b.instanceName);
      CstringCopy(parentConnection,b.parentConnection);
      CstringCopy(portConnection,b.portConnection);
      initMemberVar(relationship,b.relationship);
      initMemberVar(vportList,b.vportList);
 //     initMemberVar(subcktName,b.subcktName);
 //    cout<<"subcktName is "<<b.subcktName<<endl;
 //   cout<<"subcktName is "<<subcktName<<endl;
}
