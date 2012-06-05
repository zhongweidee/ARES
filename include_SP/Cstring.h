typedef struct {
   size_t allocMem;
   size_t total_element;
   char* elems;
   char* buf;
} Cstring;
void CstringNew(Cstring *s);
void CstringNewWithNum(Cstring *s,size_t allocNum);
char *CstringFind(Cstring *s,char *str);
void CstringAppendMutiArg(Cstring *s,int numOfStr, ...);
void CstringAppend(Cstring *s,const void* str,int lengthOfStr);
void CstringAppend(Cstring *s,const char * str);
void CstringCopy(Cstring *s, Cstring *c);
void CstringToUpper(Cstring *s);
void CstringDelete(Cstring *s);
void CstringUpperCase(Cstring *s);
