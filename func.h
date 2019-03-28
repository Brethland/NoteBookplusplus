#ifndef FUNCTION_H
#define FUNCTION_H

#include "diary.h"
#include <list>
using namespace std;

  //void sortByMethod(int sortMethod);
  list<Diary> filterByMethod(int catagoryMethod);//筛选日记或者待办事项
  string lockMainWindow();//密码验证
  void addDiary(string title,string text,int catagory);//与文件交互添加日记
  void updateDiary(int sid,string title,string txt);
  void deleteDiary(int sid);
  list<Diary> fetchAll();
#endif // FUNCTION_H
