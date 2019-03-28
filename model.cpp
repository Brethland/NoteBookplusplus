#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "diary.h"

int addNewDiary(){
      const char *sql_create_table="create table t(id int primary key,msg varchar(128))";
      sqlite3 *db;
      char *errmsg = 0;
      int ret = sqlite3_open("C:/Users/ycy12/Documents/Workspace/Notebook/database/diary.db",&db);
      if(ret != SQLITE_OK) {
              fprintf(stderr,"Cannot open db: %s\n",sqlite3_errmsg(db));
              return 1;
      }
      sqlite3_free(errmsg);
      sqlite3_close(db);
      printf("Succeed.\n");
      return 0;
}
