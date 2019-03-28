#include "edit.h"
#include "ui_edit.h"
#include "diary.h"
#include <string>
#include <cstring>
#include "func.h"
#include <QString>
#include <QRadioButton>
#include <QMessageBox>

edit::edit(Diary dr,QWidget *parent) :
  QDialog(parent),
  ui(new Ui::edit)
{
  ui->setupUi(this);
  setWindowFlags(Qt::SplashScreen);
  ui->text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  char *st1 = const_cast<char *>(dr.title.c_str());
  char *st2 = const_cast<char *>(dr.txt.c_str());
  ui->title->setPlainText(QString(st1));
  ui->text->setPlainText(QString(st2));
  ui->catagory->setStyleSheet("font-size:11pt;\
                              border:none;\
                              QComboBox::down-arrow{\
                              img:url(:/src/expand.png);\
                              }\
                              QComboBox::drop-down{\
                                  subcontrol-origin: padding;\
                                  subcontrol-position: top right;\
                                  width: 20px;\
                                  border-left-width: 1px;\
                                  border-left-color: darkgray;\
                                  border-left-style: solid;\
                                  border-top-right-radius: 3px;\
                                  border-bottom-right-radius: 3px;\
                              }");
  sid = dr.sid;
}


edit::~edit()
{
  delete ui;
}

void edit::on_confirm_clicked()
{
    int catagory = 1;
    if(ui->catagory->currentText() == "日记"){
        catagory = 1;
      }else{
        catagory = 2;
      }
    QString title_ = ui->title->toPlainText();
    QString text_ = ui->text->toPlainText();
    string title = title_.toStdString();
    string text = text_.toStdString();
    if(sid){
        updateDiary(sid,title,text);
      }else{
        addDiary(title,text,catagory);
      }
    edit::close();
}

void edit::on_delete_2_clicked()
{
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this, "警告",QString("确定删除吗?"),
                                   QMessageBox::Yes |
                                   QMessageBox::No );
  if(reply == QMessageBox::Yes){
      deleteDiary(sid);
      edit::close();
    }
}
