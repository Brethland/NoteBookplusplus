#include "func.h"
#include "diary.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <QFile>
#include <QByteArray>
#include <QTextStream>
#include <list>
#include "base64.h"
using namespace std;


string CharToStr(char * contentChar)
{
	string tempStr;
	for (int i=0;contentChar[i]!='\0';i++)
	{
		tempStr+=contentChar[i];
	}
	return tempStr;
}

void addDiary(string title,string text,int catagory) {
  int totalDiaryNumber;
  ifstream fin;
  string thisPath = "doc/metaData.txt";
  fin.open(thisPath);
  string lineCollector;
  fin >> lineCollector;
  char *st1 = const_cast<char *>(lineCollector.c_str());
  sscanf(st1,"TotalDiary:%d",&totalDiaryNumber);
  ofstream fout,changelog;
  fout.open("doc/" + to_string(totalDiaryNumber + 1) + ".txt");
  Diary bufferIn(totalDiaryNumber + 1,title,text,catagory,time(0),time(0),0);
  fout << bufferIn.isDeleted << endl;
  fout << bufferIn.sid << endl;
  fout << bufferIn.catagory << endl;
  fout << (long)bufferIn.timeCreate << endl;
  fout << (long)bufferIn.timeLastEdit << endl;
  fout << bufferIn.title << endl;
  fout << bufferIn.txt;
  changelog.open(thisPath);
  changelog << "TotalDiary:" << totalDiaryNumber + 1;
  fout.close();
  fin.close();
  changelog.close();

}

void updateDiary(int sid,string title,string txt) {
  ifstream fin;
  string changePath = "doc/" + to_string(sid) + ".txt";
  fin.open(changePath);
  string FileOutput = "";
  int line = 1;
  char tmpLineData[1024] = {0};
  while(line<=5) {
      fin.getline(tmpLineData,sizeof(tmpLineData));
      if(line == 5){
          char *nowtm = const_cast<char *>(to_string(time(0)).c_str());
          FileOutput += CharToStr(nowtm);
          FileOutput += "\n";
        }else {
          FileOutput += CharToStr(tmpLineData);
          FileOutput += "\n";
        }
      line++;
    }
  ofstream fout;
  fout.open(changePath);
  fout << FileOutput << title << endl << txt;
  fout.close();
  fin.close();

}

void deleteDiary(int sid){
    string changePath = "doc/" + to_string(sid) + ".txt";
    ifstream fin;
    fin.open(changePath);
    string FileOutput = "";
    int line = 1;
    char tmpLineData[1024] = {0};
    while(fin.getline(tmpLineData,sizeof(tmpLineData))) {
        if(line == 1){
            char *nowtm = const_cast<char *>(to_string(1).c_str());
            FileOutput += CharToStr(nowtm);
            FileOutput += "\n";
          }else {
            FileOutput += CharToStr(tmpLineData);
            FileOutput += "\n";
          }
        line++;
      }
    ofstream fout;
    fout.open(changePath);
    fout << FileOutput;
    fout.close();
    fin.close();

}

list<Diary> fetchAll(){
  int totalDiaryNumber;
  ifstream foc;
  ofstream errorstate;
  string thisPath = "doc/metaData.txt";
  errorstate.open(thisPath);
  foc.open(thisPath);
  errorstate.close();
  string lineCollector;
  foc >> lineCollector;
  foc.close();
  char *st1 = const_cast<char *>(lineCollector.c_str());
  sscanf(st1,"TotalDiary:%d",&totalDiaryNumber);
  int goForNumber = 1;
  list<Diary> DiaryList;
  while(goForNumber<=totalDiaryNumber){
      ifstream fin;
      string nowPath = "doc/" + to_string(goForNumber) + ".txt";
      fin.open(nowPath);
      char tmpLineData[1024] = {0};
      Diary bufferIn(1,"1","1",1,1,1,1);
      fin.getline(tmpLineData,sizeof(tmpLineData));
      if(atoi(tmpLineData)) {
          goForNumber++;
          continue;
        }else{
          bufferIn.isDeleted = 0;
        }
      fin.getline(tmpLineData,sizeof(tmpLineData));
      bufferIn.sid = atoi(tmpLineData);
      fin.getline(tmpLineData,sizeof(tmpLineData));
      bufferIn.catagory = atoi(tmpLineData);
      fin.getline(tmpLineData,sizeof(tmpLineData));
      bufferIn.timeCreate = atol(tmpLineData);
      fin.getline(tmpLineData,sizeof(tmpLineData));
      bufferIn.timeLastEdit = atol(tmpLineData);
      fin.getline(tmpLineData,sizeof(tmpLineData));
      bufferIn.title = CharToStr(tmpLineData);
      string text = "";
      while(fin.getline(tmpLineData,sizeof(tmpLineData))){
          text += CharToStr(tmpLineData);
          text += "\n";
        }
      bufferIn.txt = text;
      DiaryList.push_back(bufferIn);
      goForNumber++;
      fin.close();
    }
  return DiaryList;
}

list<Diary> filterByMethod(int catagoryMethod){
  int totalDiaryNumber;
  ifstream foc;
  string thisPath = "doc/metaData.txt";
  foc.open(thisPath);
  string lineCollector;
  foc >> lineCollector;
  foc.close();
  char *st1 = const_cast<char *>(lineCollector.c_str());
  sscanf(st1,"TotalDiary:%d",&totalDiaryNumber);
  int goForNumber = 1;
  list<Diary> DiaryList;
  while(goForNumber <= totalDiaryNumber){
      ifstream fin;
      string nowPath = "doc/" + to_string(goForNumber) + ".txt";
      fin.open(nowPath);
      char tmpLineData[1024] = {0};
      Diary bufferIn(1,"1","1",1,1,1,1);
      fin.getline(tmpLineData,sizeof(tmpLineData));
      if(atoi(tmpLineData)) {
          goForNumber++;
          continue;
        }else{
          bufferIn.isDeleted = 0;
        }
      fin.getline(tmpLineData,sizeof(tmpLineData));
      bufferIn.sid = atoi(tmpLineData);
      fin.getline(tmpLineData,sizeof(tmpLineData));
      if(catagoryMethod == atoi(tmpLineData)){
          bufferIn.catagory = catagoryMethod;
        }else {
          goForNumber++;
          continue;
        }
      fin.getline(tmpLineData,sizeof(tmpLineData));
      bufferIn.timeCreate = atol(tmpLineData);
      fin.getline(tmpLineData,sizeof(tmpLineData));
      bufferIn.timeLastEdit = atol(tmpLineData);
      fin.getline(tmpLineData,sizeof(tmpLineData));
      bufferIn.title = CharToStr(tmpLineData);
      string text = "";
      while(fin.getline(tmpLineData,sizeof(tmpLineData))){
          text += CharToStr(tmpLineData);
          text += "\n";
        }
      bufferIn.txt = text;
      DiaryList.push_back(bufferIn);
      goForNumber++;
      fin.close();
    }
  return DiaryList;
}

string lockMainWindow(){
  string thisPath = "doc/crypto.txt";
  ifstream fin;
  fin.open(thisPath);
  char tmpData[1024] = {0};
  if(fin.getline(tmpData,sizeof(tmpData))){
      string crypto = CharToStr(tmpData);
      crypto = base64_decode(crypto);
      return crypto;
    }else {
      return "";
    }
}
