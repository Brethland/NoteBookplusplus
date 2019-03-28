#ifndef DIARY_H
#define DIARY_H
#include <ctime>
#include <cstring>
#include <string>
using namespace std;

class Diary
{
public:
  int sid;
  string title;
  string txt;
  time_t timeCreate,timeLastEdit;
  int catagory;
  int isDeleted;

public:
  Diary(int sid,string title,string txt,int catagory,time_t timeCreate = time(0),time_t timeLastEdit = time(0),int isdeleted = 0);
};
#endif // DIARY_H
