#include "password.h"
#include "ui_password.h"
#include <string>
#include <cstring>
#include <QString>
#include <QPalette>
#include "qpalette.h"

password::password(string pass,QWidget *parent) :
  QDialog(parent),
  ui(new Ui::password)
{

  ui->setupUi(this);
  setStyleSheet("QPushButton{border:none;}QToolButton{border:none;}");
  setWindowFlags(Qt::SplashScreen);
  QPalette pal = palette();
  pal.setColor(QPalette::Background, QColor::fromRgb(248,248,255));
  setAutoFillBackground(true);
  setPalette(pal);
  check = pass;
}

password::~password()
{
  delete ui;
}

void password::on_confirm_clicked()
{
   QString input_ =  ui->passinput->toPlainText();
   string input = input_.toStdString();
   if(input != check){
       ui->passinput->setPlainText("");
     }else{
       accept();
     }
}
