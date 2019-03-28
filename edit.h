#ifndef EDIT_H
#define EDIT_H

#include <QDialog>
#include "diary.h"

namespace Ui {
  class edit;
}

class edit : public QDialog
{
  Q_OBJECT

public:
  int sid;
  explicit edit(Diary dr,QWidget *parent = 0);
  ~edit();
public slots:
  //void editShow(Diary dr);

private slots:
  void on_confirm_clicked();

  void on_delete_2_clicked();

private:
  Ui::edit *ui;
};

#endif // EDIT_H
