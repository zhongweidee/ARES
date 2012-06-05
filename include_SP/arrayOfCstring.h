typedef struct {
   int numOfElems;
   int size;
   int allocSize;
   char** elems;
} ArrayCstring;
void ArrayCstringNew(ArrayCstring *s,int allocS);
void ArrayCstringGrow(ArrayCstring *s);
void ArrayCstringPush(ArrayCstring *s,char *elem,int lengthOfElem);
char *ArrayCstringIndex(ArrayCstring *s,int i);
void ArrayCstringCopy(ArrayCstring *s,ArrayCstring *c);
void ArrayCstringPrintAllElems(ArrayCstring *s);
void ArrayCstringDelete(ArrayCstring *s);

