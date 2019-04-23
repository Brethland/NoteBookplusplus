#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpalette.h"
#include "qmenu.h"
#include <list>
#include <cstring>
#include "func.h"
#include <QFrame>
#include <iostream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QListWidgetItem>
#include <QListWidget>
#include <QWidget>
#include <cstring>
#include <QString>
#include <QCheckBox>
#include <QPushButton>
#include <QSize>
#include <QFont>
#include "edit.h"
#include <QList>

bool sortEditDecrease(Diary a,Diary b){
  return long(a.timeLastEdit) > long(b.timeLastEdit);
}
string cutStr(string original){
  if(original.length()<100){
      return original;
    }else {
      return original.substr(0,100);
    }
}
void MainWindow::on_btn1_clicked()
{
    exit(0);
}

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  //设置按钮窗口样式
  setWindowFlags(Qt::SplashScreen);
  setStyleSheet("QPushButton{border:none;}QToolButton{border:none;}");
  setFont(QFont("Century"));
  QPalette pal = palette();
  pal.setColor(QPalette::Background, QColor::fromRgb(248,248,255));
  setPalette(pal);

  //菜单
  QMenu
   *pMenu = new QMenu();
  QMenu
   *chooseMenu = new QMenu();
  QAction
   *sort = new QAction(pMenu);
  QAction
   *choose = new QAction(pMenu);
  QAction
   *setting = new QAction(pMenu);
  QAction
   *filterDiary = new QAction(chooseMenu);
  QAction
   *filterTodo = new QAction(chooseMenu);
  QAction
   *filterAll = new QAction(chooseMenu);
//添加
   pMenu->addAction(sort);
   pMenu->addAction(choose);
   pMenu->addSeparator();
   pMenu->addAction(setting);

   chooseMenu->addAction(filterAll);
   chooseMenu->addAction(filterDiary);
   chooseMenu->addAction(filterTodo);
//设置选项
   sort->setText(tr("最近修改"));
   sort->setIcon(QIcon(":/src/sort.png"));
   choose->setText(tr("筛选"));
   choose->setIcon(QIcon(":/src/filter.png"));
   filterAll->setText(tr("全部记事"));
   filterDiary->setText(tr("日记"));
   filterTodo->setText(tr("待办事项"));
   choose->setMenu(chooseMenu);
   setting->setText(QString("偏好设置"));
   setting->setIcon(QIcon(":/src/settings.png"));
   sett = new settings;
   connect(setting,SIGNAL(triggered()), sett, SLOT(show()));
   pMenu->setStyleSheet("QMenu{background:#f8f8ff;}QMenu::item{color:rgb(105,105,105);}\
                          QMenu::item:selected{background-color:rgb(220,220,220);}");
   chooseMenu->setStyleSheet("QMenu{background:#f8f8ff;}QMenu::item{color:rgb(105,105,105);}\
                          QMenu::item:selected{background-color:rgb(220,220,220);}");
   connect(filterAll,SIGNAL(triggered()),this,SLOT(filte0()));
   connect(filterDiary,SIGNAL(triggered()),this,SLOT(filte1()));
   connect(filterTodo,SIGNAL(triggered()),this,SLOT(filte2()));
   connect(sort,SIGNAL(triggered()),this,SLOT(sort1()));


   //关联菜单按钮
   ui->pMenuButton->setMenu(pMenu);
   ui->pMenuButton->setStyleSheet("QPushButton::menu-indicator{image:None;}");

   //主界面样式
   ui->showBox->setStyleSheet("border:none;background-color:rgb(248,248,255);");
   Diary bf(0,"","",0);
   editor = new edit(bf);
   connect(ui->pushButton,SIGNAL(clicked()),editor,SLOT(show()));
   showDiary(0);

}

void MainWindow::showDiary(int filterName){
  list<Diary> newList;
  if(!filterName){
    newList = fetchAll();
    }
  else{
      newList = filterByMethod(filterName);
    }
  list<Diary>::iterator it;
  for(it = newList.begin();it != newList.end();it++) {
      //布局
      QWidget *wid = new QWidget;
      QWidget *textShow = new QWidget(wid);
      QWidget *optionBar = new QWidget(wid);
      QWidget *checkBar = new QWidget(wid);
      QHBoxLayout *mainLayout = new QHBoxLayout();
      QVBoxLayout *textLayout = new QVBoxLayout();
      QVBoxLayout *optionLayout = new QVBoxLayout();
      QVBoxLayout *checkLayout = new QVBoxLayout();

      //控件
      QCheckBox *checkDelete = new QCheckBox();
      QLabel *title = new QLabel(textShow);
      QLabel *cuttedText = new QLabel(textShow);
      QPushButton *moreDetail = new QPushButton(optionBar);
      QPushButton *editOption = new QPushButton(optionBar);

      //设置控件
      title->setStyleSheet("font-size:13pt;");
      char *st1 = const_cast<char *>(it->title.c_str());
      title->setText(QString(st1));
      cuttedText->setStyleSheet("font-size:10pt;");
      char *st2 = const_cast<char *>(cutStr(it->txt).c_str());
      cuttedText->setText(QString(st2));
      moreDetail->setFixedSize(100,70);
      moreDetail->setStyleSheet("font-size:11pt;");
      moreDetail->setText(tr("More"));
      editOption->setText(tr("Edit"));
      editOption->setStyleSheet("font-size:11pt;");
      editOption->setFixedSize(100,70);
      editor = new edit(*it);
      connect(editOption,SIGNAL(clicked()),editor,SLOT(show()));
      detail_ = new detail(*it);
      connect(moreDetail,SIGNAL(clicked()),detail_,SLOT(show()));

      //设置布局
      checkLayout->setMargin(20);
      textLayout->setMargin(20);
      optionLayout->setMargin(20);

      mainLayout->setContentsMargins(0,0,0,0);
      textLayout->setContentsMargins(0,0,0,0);
      optionLayout->setContentsMargins(0,0,0,0);
      optionLayout->setMargin(0);
      //放置控件
      checkLayout->addWidget(checkDelete);
      textLayout->addWidget(title);
      textLayout->addWidget(cuttedText);
      textLayout->addSpacing(5);
      optionLayout->addWidget(moreDetail);
      optionLayout->addWidget(editOption);
      textShow->setLayout(textLayout);
      optionBar->setLayout(optionLayout);
      checkBar->setLayout(checkLayout);
      mainLayout->addWidget(checkBar);
      mainLayout->addWidget(textShow);
      mainLayout->addStretch();
      mainLayout->addWidget(optionBar);
      wid->setLayout(mainLayout);

      //最终添加
      QListWidgetItem *qm = new QListWidgetItem;
      qm->setSizeHint(QSize(980,150));
      wid->setSizeIncrement(QSize(980,150));
      ui->showBox->addItem(qm);

      ui->showBox->setItemWidget(qm,wid);
    }
  ui->showBox->setStyleSheet("QListWidget{background-color:#f8f8ff;border:none;}");
  ui->showBox->setSpacing(30);
  ui->showBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  nowList = newList;
}

void MainWindow::showDiarysorted(){
  list<Diary> newList = nowList;
  list<Diary>::iterator it;
  for(it = newList.begin();it != newList.end();it++) {
      //布局
      QWidget *wid = new QWidget;
      QWidget *textShow = new QWidget(wid);
      QWidget *optionBar = new QWidget(wid);
      QWidget *checkBar = new QWidget(wid);
      QHBoxLayout *mainLayout = new QHBoxLayout();
      QVBoxLayout *textLayout = new QVBoxLayout();
      QVBoxLayout *optionLayout = new QVBoxLayout();
      QVBoxLayout *checkLayout = new QVBoxLayout();

      //控件
      QCheckBox *checkDelete = new QCheckBox();
      QLabel *title = new QLabel(textShow);
      QLabel *cuttedText = new QLabel(textShow);
      QPushButton *moreDetail = new QPushButton(optionBar);
      QPushButton *editOption = new QPushButton(optionBar);

      //设置控件
      title->setStyleSheet("font-size:13pt;");
      char *st1 = const_cast<char *>(it->title.c_str());
      title->setText(QString(st1));
      cuttedText->setStyleSheet("font-size:10pt;");
      char *st2 = const_cast<char *>(cutStr(it->txt).c_str());
      cuttedText->setText(QString(st2));
      moreDetail->setFixedSize(100,70);
      moreDetail->setStyleSheet("font-size:11pt;");
      moreDetail->setText(tr("More"));
      editOption->setText(tr("Edit"));
      editOption->setStyleSheet("font-size:11pt;");
      editOption->setFixedSize(100,70);
      editor = new edit(*it);
      connect(editOption,SIGNAL(clicked()),editor,SLOT(show()));
      detail_ = new detail(*it);
      connect(moreDetail,SIGNAL(clicked()),detail_,SLOT(show()));

      //设置布局
      checkLayout->setMargin(20);
      textLayout->setMargin(20);
      optionLayout->setMargin(20);

      mainLayout->setContentsMargins(0,0,0,0);
      textLayout->setContentsMargins(0,0,0,0);
      optionLayout->setContentsMargins(0,0,0,0);
      optionLayout->setMargin(0);
      //放置控件
      checkLayout->addWidget(checkDelete);
      textLayout->addWidget(title);
      textLayout->addWidget(cuttedText);
      textLayout->addSpacing(5);
      optionLayout->addWidget(moreDetail);
      optionLayout->addWidget(editOption);
      textShow->setLayout(textLayout);
      optionBar->setLayout(optionLayout);
      checkBar->setLayout(checkLayout);
      mainLayout->addWidget(checkBar);
      mainLayout->addWidget(textShow);
      mainLayout->addStretch();
      mainLayout->addWidget(optionBar);
      wid->setLayout(mainLayout);

      //最终添加
      QListWidgetItem *qm = new QListWidgetItem;
      qm->setSizeHint(QSize(980,150));
      wid->setSizeIncrement(QSize(980,150));
      ui->showBox->addItem(qm);

      ui->showBox->setItemWidget(qm,wid);
    }
  ui->showBox->setStyleSheet("QListWidget{background-color:#f8f8ff;border:none;}");
  ui->showBox->setSpacing(30);
  ui->showBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  nowList = newList;
}
MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    int index = 0;
    while(index < ui->showBox->count()) {
        ui->showBox->takeItem(index);
      }
    showDiary(0);
}

void MainWindow::filte0(){
  int index = 0;
  while(index < ui->showBox->count()) {
      ui->showBox->takeItem(index++);
    }
  showDiary(0);
}
void MainWindow::filte1(){
  int index = 0;
  while(index < ui->showBox->count()) {
      ui->showBox->takeItem(index);
    }
  showDiary(1);
}

void MainWindow::filte2(){
  int index = 0;
  while(index < ui->showBox->count()) {
      ui->showBox->takeItem(index);
    }
  showDiary(2);
}

void MainWindow::sort1(){
  int index = 0;
  while(index < ui->showBox->count()) {
      ui->showBox->takeItem(index);
    }
  nowList.sort(sortEditDecrease);
  showDiarysorted();
}
