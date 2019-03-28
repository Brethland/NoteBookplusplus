#include "diary.h"

Diary::Diary(int sid_,string title_,string txt_,int catagory_,time_t timeCreate_,time_t timeLastEdit_,int isdeleted_){
  sid = sid_;
  title = title_;
  txt = txt_;
  catagory = catagory_;
  timeCreate = timeCreate_;
  timeLastEdit = timeLastEdit_;
  isDeleted = isdeleted_;
}
