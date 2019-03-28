#include "mainwindow.h"
#include <QApplication>
#include "func.h"
#include <iostream>
#include <QFont>
#include "password.h"
using namespace std;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  string pass = lockMainWindow();
  QFont font = a.font();
  font.setFamily("Iosevka Light");
  a.setFont(font);
  if(pass!=""){
  password ps(pass);
  if(ps.exec() == QDialog::Accepted){
  MainWindow w;
  w.show();
  return a.exec();
    }
  else{
      return 0;
    }
    }
  else{
      MainWindow w;
      w.show();
      return a.exec();
    }
}
