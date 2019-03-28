#include "settings.h"
#include "ui_settings.h"
#include "qpalette.h"
#include "qmenu.h"
#include <fstream>
#include <QString>
#include <cstring>
#include <string>
#include "base64.h"
#include <iostream>
using namespace std;

settings::settings(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::settings)
{
  ui->setupUi(this);

  //设置按钮窗口样式
  setWindowFlags(Qt::SplashScreen);
  setStyleSheet("QPushButton{border:none;}QToolButton{border:none;}");
  ui->about->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //垂直滚动条
  ui->about->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //水平滚动条
  QPalette pl = palette();
  pl.setColor(QPalette::Background, QColor::fromRgb(255,255,255));
  setAutoFillBackground(true);
  setPalette(pl);
}

settings::~settings()
{
  delete ui;
}

void settings::on_passConfirm_clicked()
{
     ofstream fout;
     fout.open("C:/Users/ycy12/Documents/Workspace/Notebook/doc/crypto.txt");
     QString input_ = ui->pass->toPlainText();
     string input = input_.toStdString();
     unsigned char *st1 = (unsigned char *)(input.c_str());
     int len = input.length();
     string crypto = base64_encode(st1,len);
     fout << crypto;
     fout.close();
}
