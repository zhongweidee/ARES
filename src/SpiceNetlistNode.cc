/* File : example.c */
#include "../include_SP/SpiceNetlistNode.h"
//#include "ExtractDeviceList.c"
//#define logMode 0 // 0 will print all log to stdout, 1 will not print log
//#define true 1
//#define false 0
//#######################################################################################
//  spice Netlist --> array of SubcktNode 
//  spicePaser Version 0.1
//  property of Node "cellName"
//  Author: Wei.Zhong
//  Copyright(C) 2011 All Rights Reserved
//  Version History:
//  ver 0.1 orignal version   2011/11/28
//  toDo:
//      a.write the debug mode and product mode
//          debug mode: print the full log
//        product mode: print the simple log
//      b.add query mode  (if desgin no change ,no need to run again)
//      c.add child and parent property
//      d.handle the "\n+"
//  finish toDo:
//
//#######################################################################################

////////////////////////////////////////////////////////////////
//  Notice:
//        1.this script don't handle the "include" in include 
////////////////////////////////////////////////////////////////
// STL extention
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// String Class
////////////////////////////////////////////////////////////////
// Global Function Define
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//SpiceNetlistNode::SpiceNetlistNode(std::string netlistPath)
void SpiceNetlistNode::init(std::string netlistPath,Cstring *deviceList,const char *calibreLvsRulePath)
{
    if(!Global_function::file_exists(netlistPath)){
    string Comment="Error:Can't find the netlist " + netlistPath;
    cout<<Comment<<endl;
    exit(0);
                                        }
    else
    {
     cout<<"LOG:start to reading "<<netlistPath<<endl;
    }
    vArrayString arrayOfNetlist=grepIncludeFileToArray(netlistPath);
    vIterString iter;
    for(iter=arrayOfNetlist.begin();iter!=arrayOfNetlist.end();++iter){
       //string path="LOG:reading "+*iter;
       Global_function::SNPuts("LOG:reading "+*iter);
       cout<<"LOG:reading "+*iter<<endl;;
       SpiceReaderNoneIncludeFile(*iter);
                                                                      }//for
     cout<<"LOG:finish to reading "<<netlistPath<<endl;
     printf("LOG:start to extract DeviceList from svrf Rule\n");
     //const char *svrfRulePath=
     //"/project/tsmc40lp/1P7M4X2Z/techs/calibre/TSMC_lvs/V_1.2H/MAIN_DECK/CALIBRE_FLOW/DFM_LVS_RC_CALIBRE_N40LP_LPG_1p7M_4X2Z_ALRDL.v12h";
     ED::ExtractDeviceList(calibreLvsRulePath,deviceList);
     printf("LOG:end to extract DeviceList from svrf Rule\n");
}

void   SpiceNetlistNode::replace_all_distinct(string&   str,const   string&   old_value,const   string&   new_value)   
{   
    for(string::size_type   pos(0);   pos!=string::npos;   pos+=new_value.length())   {   
        if(   (pos=str.find(old_value,pos))!=string::npos   )   
            str.replace(pos,old_value.length(),new_value);   
        else   break;   
    }   
}   

bool SpiceNetlistNode::deleteCommentWordLine(std::string &spiceLine)
{
  vArrayString array;
  Global_function::vStringSplit(spiceLine,array); 
  if(array.size()>0){
  std::string firstValue = array[0];
  if((firstValue.find("*")!=string::npos)||(firstValue.find("$")!=string::npos)){
     return false;
                                        }
  else{
     return true;
                     }//if
  //cout<<"LOG: end to deleteCommentWordLine"<<endl;
       }
 else{
     return false;
      }
}
std::string SpiceNetlistNode::getNetlistName()
{
  return netlistName; 
}
BaseNodeArrayPtr& SpiceNetlistNode::getSubcktArray()
{
  return subcktArray;
}
/*std::string SpiceNetlistNode::getSubcktList()
{
   string subcktNameList;
   size_t size =subcktArray.size();
   for(int a=0;(size_t)a<size;++a){
      SubcktNode node =subcktArray[a];
      subcktNameList.append(" ");
      subcktNameList.append(node.getSubcktName());
                          }
   return subcktNameList;
}*/


/*vArrayString SpiceNetlistNode::getSubcktNameArray()
{
   vArrayString subcktNameList;
   size_t size =subcktArray.size();
   for(int a=0;(size_t)a<size;++a){
      SubcktNode node =subcktArray[a];
      subcktNameList.push_back(node.tSubcktName());
      cout<<"LOG:push "<<node.getSubcktName()<<endl;
                          }
    if(subcktNameList.size()==0){
        cout<<"Error: size of subcktNameList is 0"<<endl;
        exit(0);
                                 }
   return subcktNameList;
}*/
/*string SpiceNetlistNode::getSubcktContentByName(std::string name)
{
   string subcktNameList;
   string returnString;
   size_t size =subcktArray.size();
   int flag=0;
   for(int a=0;a<size;++a){
      SubcktNode node =subcktArray[a];
      string subcktName =node.getSubcktName();
      //cout<<"LOG: "<<subcktName << " vs " << name <<endl;
      if(subcktName.compare(name) ==0){
         flag=1;
         returnString =node.getSubcktContent();
                                     }
                           }
      if(flag==0){
         cout<<"Error: Can't find the cellname->"<<name <<endl;
         exit(0);
           }
       return returnString;
}
*/ 
// for swig  close for memory control
void SpiceNetlistNode::replaceSpecialCharactor(string &netlistContent)
{
  //cout<<"LOG: start to replace include"<<endl;
  Global_function::replaceAll(netlistContent,"include","INCLUDE"); // for performance
  Global_function::replaceAll(netlistContent,"Include","INCLUDE"); // for performance
  Global_function::replaceAll(netlistContent,"INclude","INCLUDE"); // for performance
  Global_function::replaceAll(netlistContent,"INClude","INCLUDE"); // for performance
  Global_function::replaceAll(netlistContent,"'","\""); // for performance
  //cout<<"LOG: end to replace include"<<endl;
}

vArrayString SpiceNetlistNode::grepIncludeFileToArray(std::string &netlistPath)
{
 vArrayString netlistArray; 
 vArrayString preCommandArray; 
 netlistArray.push_back(netlistPath); 
 string preCommand1 = "grep -F \".include \" "; 
 string preCommand2 = "grep -F \".INCLUDE \" "; 
 string preCommand3 = "grep -F \".Include \" "; 
 string preCommand4 = "grep -F \".INclude \" "; 
 preCommandArray.push_back(preCommand1);
 preCommandArray.push_back(preCommand2);
 preCommandArray.push_back(preCommand3);
 preCommandArray.push_back(preCommand4);
  for(int b=0;(size_t)b<netlistArray.size();++b){ 
    for(int a=0;(size_t)a<preCommandArray.size();++a){ 
  //std::cout<<"LOG: netlist in Array->"<<netlistArray[b]<<std::endl;
  //std::cout<<"LOG: command ->"<<preCommandArray[a]<<std::endl;
  string  command = preCommandArray[a]+netlistArray[b];
  string  singleResult;
  //std::cout<<"LOG:preCommandArray "<<preCommandArray[a]<<std::endl;
  //std::cout<<"LOG:netlistArray"<<netlistArray[b]<<std::endl;
  Global_function::linuxCommandResult(command,singleResult);
  stringstream stream(singleResult); 
  string newNetlistPath;
      while(getline(stream,newNetlistPath,'\n')){
       if(deleteCommentWordLine(newNetlistPath)){
       vArrayString arrayLine;
       Global_function::vStringSplit(newNetlistPath,arrayLine);   
       Global_function::replaceAll(arrayLine[1],"'","");
       Global_function::replaceAll(arrayLine[1],"\"","");
       
       //Global_function::SNPuts("push new netlistPath",logMode);
       if(logMode==0){
       std::cout<<"LOG:push new netlistPath "<<arrayLine[1]<<std::endl;
                     }
       
       netlistArray.push_back(arrayLine[1]);
                                              }//if
                                       }//while
                                          }//for
                                          }//for
  cout<<"LOG:Finish grepIncludeFileToArray"<<endl; 
return netlistArray;
}

vArrayString SpiceNetlistNode::splitStringBy(std::string &str,std::string &delim)
{
  vArrayString array;
  std::string::size_type prev_pos = 0, pos = 0;
    while( (pos = str.find(' ', pos)) != std::string::npos )
    {
        std::string substring( str.substr(prev_pos, pos-prev_pos) );

        //std::cout << substring << '\n';
        array.push_back(substring);
        prev_pos = ++pos;
    }
    std::string substring( str.substr(prev_pos, pos-prev_pos) ); // Last word
    array.push_back(substring);
    return array;
}

bool SpiceNetlistNode::PaserParameter(std::string &netlistContent)
{
     string parameterKeyName=".param";
     string equal("=");
     stringstream stream(netlistContent); 
     string spiceLine;
     while(getline(stream,spiceLine)){
            if(deleteCommentWordLine(spiceLine)){
              vArrayString array;
	      Global_function::vStringSplit(spiceLine,array);           
                 if(strcasecmp(array[0].c_str(),parameterKeyName.c_str())==0){
			 for(int a=1;(size_t)a<array.size()-1;++a){
                                 vArrayString tempArray;
				 Global_function::vStringSplitByString(tempArray,array[a],equal); 
                                 if(tempArray.size()!=2){
                                  cout<<"Error: the parameter have error format"<<spiceLine<<endl; 
				  exit(0);
				 } 
				 else{
                                  parameterHash.insert(std::make_pair(tempArray[0],tempArray[1]));
				 }
			                                  } //for	 
			        return true;
		                                } //if
		 else{
			 return false;
		 }
	                                        }//if
                                       }//while
}

bool SpiceNetlistNode::replaceParameter(string &netlistContent)
{
  string noEqualPattern="0123456789abcdefghijklmnopqrstyvwxyzABCDEFGHIJKLMNOPQRSTYVWXYZ";
  string equalPattern=" ="; 
//don't replace the called by Name
  if(netlistContent.find("$PINS")==string::npos){
  if(PaserParameter(netlistContent)){
     stringstream stream(netlistContent); 
     string spiceLine;
     sHashSSIter iter;
     size_t posA=0;
     size_t posB=0;
     size_t pos=0;
     size_t equalpos=0;
     while(getline(stream,spiceLine)){
       for(iter=parameterHash.begin();iter!=parameterHash.end();++iter){
         while(spiceLine.find((*iter).first,pos)){
	   while(spiceLine.find("=",pos)!=string::npos){
            equalpos=spiceLine.find("=",pos);
            posA =spiceLine.find_first_of(noEqualPattern,equalpos+1);        
            posB =spiceLine.find(" ",posA);        
            spiceLine.replace(posA,posB-posA,(*iter).second);
	    pos=posB;
	           }//while
	 }//while
	    }//for
                                    }//while
      return true;
      }//if
  else{
      return false;
  }
                                                }//while
}

void SpiceNetlistNode::SpiceReaderNoneIncludeFile(std::string &netlistPath)
{
     //start to load file
     cout<<"LOG:start1111 to SpiceReaderNoneIncludeFile"<<endl;
      netlistName=netlistPath;
     std::string *netlistContent =new string;
     Global_function::SNPuts("start to replace");
     Global_function::readFileToString(netlistPath.c_str(),*netlistContent);
   
     //end to load file 
     //replace_all_distinct(netlistContent,"\n+"," ");
     //StringReplace(netlistContent,"subckt","SUBCKT");
     Global_function::SNPuts("replace all subckt to SUBCKT");
     Global_function::replaceAll(*netlistContent,"subckt","SUBCKT"); // for performance
     Global_function::SNPuts("finish subckt");
     //StringReplace(netlistContent,"end","END");
     Global_function::replaceAll(*netlistContent,"\n+"," "); //for performance
     Global_function::replaceAll(*netlistContent,"ends","ENDS"); //for performance
     Global_function::SNPuts("start to replace parameter ");
     replaceParameter(*netlistContent); 
     Global_function::SNPuts("finish to end");
     //StringReplace(netlistContent,"\n+"," ");
     //cout<<"LOG:finish return"<<endl;
     stringstream stream(*netlistContent); 
     delete netlistContent;
     //netlistContent.clear();
     //string().swap(netlistContent);
     std::string subcktBlock;
     std::string spiceLine;
     std::string *returnNetlistContent=new string("");
     //returnNetlistContent.reserve(netlistContent.size());
     Global_function::SNPuts("start to restructure");
     while(getline(stream,spiceLine)){
            if(!(spiceLine).empty()){
            if(deleteCommentWordLine(spiceLine)){
               (*returnNetlistContent).append(spiceLine);
	       spiceLine.clear();
               string().swap(spiceLine);
               (*returnNetlistContent).append("\n");
                }//if
                                   }//if
     }//while
     stream.str("");
     Global_function::SNPuts("(*returnNetlistContent) size is "+Global_function::intToString((*returnNetlistContent).size()));
     Global_function::SNPuts("finish restructure netlist");
     vArrayString subckts;
     if(((*returnNetlistContent).find(".SUBCKT")!=string::npos)&&((*returnNetlistContent).find(".ENDS")!=string::npos)){
     Global_function::StringSplitFromAToB((*returnNetlistContent),".SUBCKT",".ENDS",subckts);
     //clear the memory
     delete returnNetlistContent;
     cout<<"LOG: start to build "<<subckts.size()<<" subcktnode"<<endl;
     subcktArray.reserve(subckts.size());
     for(vIterString iterSubckts =subckts.begin();iterSubckts!=subckts.end();++iterSubckts)
     {
     //boost::shared_ptr<SubcktNode> a(new SubcktNode);
     boost::shared_ptr<BaseNode> a(new BaseNode);
     (*a).readingContent(*iterSubckts);
     subcktArray.push_back(a);
     }
     CheckNetlistError(subckts);
     //cout<<"LOG: end to build "<<subckts.size()<<" subcktnode"<<endl;
     }
}
//void SpiceNetlistNode::CheckNetlistError(vArrayString &array)
//1.check whehter have duplicate cell name
//2.check subckt need parent(exclude top cell);
void SpiceNetlistNode::CheckNetlistError(vArrayString &array)
{
    for_each(array.begin(),array.end(),CheckDuplicateCell('.'));
}


BaseNodePtr &SpiceNetlistNode::getSubcktNodeByName(string &name)
{
   string subcktNameList;
   //size_t size =subcktArray.size();
   int flag=0;
   //for(int a=0;a<size;++a){
   BaseNodeArrayPtrIter iter;
      //cout<<"LOG: size of subcktArray is "<<subcktArray.size()<<endl;
   for(iter=subcktArray.begin();iter!=subcktArray.end();++iter){
      //SubcktNode node =*iter;
      //string subcktName((*(*iter)).subcktName);
      //cout<<"LOG: "<<subcktName << " vs " << name <<endl;
      //cout<<"LOG: start to getSubcktNodeByName "<<(*(*iter)).subcktName<<endl;
      //if(subcktName.compare(name) ==0){
      if(strcmp((*(*iter)).subcktName,name.c_str())==0){
         flag=1;
       //  cout<<"LOG: end to getSubcktNodeByName"<<endl;
         return *iter;
                                     }
                           }
      if(flag==0){
         cout<<"Error: Can't find the cellname->"<<name <<endl;
         exit(0);
           }
}


