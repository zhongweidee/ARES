#ifndef HEADFILE_
#define HEADFILE_
#include "../include_SP/HeadFile.h"
#endif
#ifndef CSTRING_
#define CSTRING_
#include "../include_SP/Cstring.h"
#endif
#ifndef SPICENETLISTNODE_
#define SPICENETLISTNODE_
#include "../include_SP/SpiceNetlistNode.h"
#endif
#ifndef SPICENETLISTBUILDER_
#define SPICENETLISTBUILDER_
#include "../include_SP/SpiceNetlistBuilder.h"
#endif
#ifndef HASH_H_
#define HASH_H_
#include "../include_SP/Hash.h"
#endif

int main(int argc, char** argv)
{
	if(argc!=4){
        cout<<"Error: the number of argument is 3"<<endl;
        cout<<"Usage: + SpiceNetlist+ topCellName + CalibreLvsRule"<<endl;
	exit(0);
                   }
        const char *netlistPath_c=argv[1];	
        const char *topCellName_c=argv[2];	
        const char *calibreLvsRulePath=argv[3];
	string topCellName(topCellName_c);
	string netlistPath(netlistPath_c);
        SpiceNetlistNode *node =new SpiceNetlistNode; 
        Cstring *deviceList=(Cstring *)malloc(sizeof(Cstring));
        CstringNew(deviceList);  
        (*node).init(netlistPath,deviceList,calibreLvsRulePath);
	SpiceNetlistBuilder builder(node,deviceList);
	builder.setTopCellName(topCellName);
	cout<<"LOG:start SpiceNetlistBuilder "<<endl;
        size_t total_element=100;
        Cstring *netDataBase =(Cstring *)malloc(sizeof(Cstring));
        CstringNewWithNum(netDataBase,100);
	builder.startToBuild(total_element,netDataBase);
	cout<<"LOG:end SpiceNetlistBuilder "<<endl;
	cout<<"LOG:start to netDataBase"<<endl;
        //delete node;
        netDataBase=builder.netDataBase;
	//cout<<(builder.netDataBase)->elems<<endl;
       /* start to use hash to build net database */ 
       Hash *netHash = (Hash *)malloc(sizeof(Hash *));
       GF::splitDataBaseToHash(netDataBase,'{','}','@',netHash);
       HashPrintKeys(netHash);
       char *value =(char *)HashValueAtKey(netHash,"vdd_ao"); 
       printf("LOG:value is %s",value);
       
       HashFree(netHash);
       free(netDataBase);
       delete node;
       free(deviceList);
}
