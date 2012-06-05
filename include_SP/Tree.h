typedef struct {
   void *root;
   int (*compar)(const void *key1,const void *key2);
   void (*action)(const void *node ,const VISIT which,const int depth);
} Tree;
void TreeNew(Tree *tree,int (*compar)(const void *k1,const void *k2));
void TreeInsert(Tree *tree,const void *key);
void TreeFind(Tree *tree,const void *key,void *retElem);
void TreeWalk(Tree *tree,void (*action)(const void *nodep,const VISIT wich,const  int depth));
