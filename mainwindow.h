#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"
#include "func.h"
#include "diary.h"
#include "edit.h"
#include "detail.h"
#include <list>
#include <QVector>
#include <QCheckBox>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  settings *sett;
  edit *editor;
  detail *detail_;
  void showDiary(int filterName);
  list<Diary> nowList;
  void sortTime(int sortMethod);
  void showDiarysorted();
  //void editDiary(int sid);
  //void printDiary(int sid);

private:
  Ui::MainWindow *ui;

public slots:
  void on_btn1_clicked();
  //void editShow(Diary dr);
  void filte0();
  void filte1();
  void filte2();
  void sort1();
  void sort2();
  void sort3();
  void sort4();
private slots:
  void on_pushButton_3_clicked();
};


#endif // MAINWINDOW_H
