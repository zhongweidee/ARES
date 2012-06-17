#ifndef HEADFILE_
#define HEADFILE_
#endif

#ifdef HEADFILE_
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <utility>
#include <stdio.h>
#include <stdarg.h>
#include <cstring>
#include <boost/shared_ptr.hpp>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#define true 1
//#define false 0
#define logMode 1 // 0 will print all log to stdout, 1 will not print log
using namespace std;
//according to the SpiceNetlist Project
//
typedef std::vector<std::string>  vArrayString;
typedef std::vector<std::string>::iterator vIterString; // std container + Iter + typename
typedef std::list<std::string> lArrayString;
typedef std::list<std::string>::iterator lIterString; // std container + Iter + typename
typedef std::deque<std::string> dArrayString;
typedef std::deque<std::string>::iterator dIterString;
typedef std::map<std::string,std::string> mHashSS;    
typedef std::map<std::string,vArrayString> mHashStringvArrayString;
typedef std::map<std::string,std::string>::iterator  sHashSSIter;
typedef size_t charPos;
typedef std::map<charPos,vArrayString> parameterHash;
typedef boost::shared_ptr<string>  stringP;
//typedef boost::shared_ptr<vArrayString>  vArrayStringP;
typedef vector<pair<string,string> > pairArraySS;
typedef pair<string,string> pairSS;
typedef vector<pair<string,string> >::iterator pairArraySSIter;
typedef boost::shared_ptr<pairArraySS>  vPairSP;
typedef boost::shared_ptr<vector<pair<string,string> > >  vPairSSP;
//typedef char charAddressAndSize_t;

class SubcktNode;
class BaseNode;
class child;
//class Net;
typedef vector<pair<string,string> >::iterator pairArraySSIter;
typedef std::vector<child> Children;
typedef std::vector<boost::shared_ptr<child> > ChildrenPtr;
typedef std::vector<boost::shared_ptr<child> >::iterator ChildrenPtrIter;
typedef std::vector<child>::iterator ChildrenIter;
typedef boost::shared_ptr<SubcktNode>  SubcktNodePtr;
typedef boost::shared_ptr<BaseNode>  BaseNodePtr;
typedef std::vector<boost::shared_ptr<SubcktNode> > SubcktNodeArrayPtr;
typedef std::vector<boost::shared_ptr<BaseNode> > BaseNodeArrayPtr;
typedef std::vector<boost::shared_ptr<BaseNode> >::iterator BaseNodeArrayPtrIter;
typedef std::vector<boost::shared_ptr<SubcktNode> >::iterator SubcktNodeArrayPtrIter;
//typedef boost::shared_ptr<Net> NetPtr;
//typedef std::vector<NetPtr> vArrayNetPtr;
//typedef std::vector<NetPtr>::iterator vArrayNetPtrIter;
typedef vector<pair<BaseNodePtr,stringP> > vPairBaseNodePtrCharAddress;
//typedef std::vector <Node> vArrayNode; // std container +Array + typename
typedef std::vector <SubcktNode> vArraySubcktNode; // std container +Array + typename
typedef std::vector <BaseNode> vArrayBaseNode; // std container +Array + typename
typedef std::vector <BaseNode>::iterator vArrayBaseNodeIter; // std container +Array + typename
typedef std::vector <SubcktNode>::iterator vArraySubcktNodeIter; // std container +Array + typename
//typedef std::map<std::string,Node> mHashSN;
typedef std::map<std::string,SubcktNode> mHashSSubcktNode;
//typedef std::vector<stringP> vArrayStringP;
//typedef vector<pair<BaseNodePtr,string> > NetChildren;

#define callByName  0
#define callByOrder 1
#ifndef DEBUG
#define putsLogS(a) printf("Debug:  %s\n",a)
#define putsLogD(a) printf("Debug:  %d\n",a)
#else
#define putsLogS(a)
#define putsLogD(a) 
#endif

#endif
