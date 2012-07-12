#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#define checkSqliteResult if( rc!=SQLITE_OK ){\
      fprintf(stderr, "SQL error: %s\n", zErrMsg);\
      sqlite3_free(zErrMsg);\
    }

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
int i;
 for(i=0; i<argc; i++){
 printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
 }
 printf("\n");
 return 0;
}



int main(int argc, char **argv){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    sqlite3_stmt *stmt;
    char *relationship="I0/I1/Ix13";
    char *connectedPin="PinC";
    char *createDB_sql= "create table vdd ( id integer primary key,relationship text,connectedPin text);"; 
    //char *insertDB_sql= "insert into foods values(null,"relationship","connectionPin")";
    char *insertDB_sql= "insert into vdd values(?,?,?)";
    
  
    if( argc!=2 ){
      fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
      return(1);
    }
    rc = sqlite3_open(argv[1], &db);
    if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      return(1);
    }
    //rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);
    //rc = sqlite3_exec(db, createDB_sql, callback, 0, &zErrMsg);
    //checkSqliteResult;
    sqlite3_prepare(db,insertDB_sql,strlen(insertDB_sql),&stmt,NULL);
    sqlite3_bind_int(stmt,1,NULL); 
    sqlite3_bind_text(stmt,2,relationship,strlen(relationship),NULL); 
    sqlite3_bind_text(stmt,3,connectedPin,strlen(connectedPin),NULL); 
    int flag=sqlite3_step(stmt);
    printf("LOG: flag is %d\n",flag);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    sqlite3_stmt *statement;
    sqlite3 *db1;
    sqlite3_open(argv[1], &db1);
    char *query_sql="select * from vdd";
    sqlite3_prepare(db1,query_sql,strlen(query_sql),&statement,NULL);
    int re; 
    sqlite3_step(statement);
    //while(re==SQLITE_ROW){
    printf("LOG: result is %s\n",sqlite3_column_text(statement,0));
    printf("LOG: result is %s\n",sqlite3_column_text(statement,1));
    printf("LOG: result is %s\n",sqlite3_column_text(statement,2));
    sqlite3_step(statement);
    printf("LOG: result is %s\n",sqlite3_column_text(statement,0));
    printf("LOG: result is %s\n",sqlite3_column_text(statement,1));
    printf("LOG: result is %s\n",sqlite3_column_text(statement,2));
     //                      }
    sqlite3_finalize(statement);
    //rc = sqlite3_exec(db, insertDB_sql, callback, 0, &zErrMsg);
    //checkSqliteResult;
    sqlite3_close(db1);
    return 0;
}
