typedef struct {
    ENTRY elem;
    ENTRY *retElem; 
    struct hsearch_data *htab; 
    size_t initialNumOfElem; 
    size_t existNumOfElem; 
    ArrayCstring *keys; 
} Hash;
void HashNew(Hash *h,size_t size);
void HashInsertString(Hash *h,char *key,char *value);
void HashInsertPoint(Hash *h,char *key,void *value);
void *HashValueAtKey(Hash *h,const char *key);
void HashFree(Hash *h);
