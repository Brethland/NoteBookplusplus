#ifndef DETAIL_H
#define DETAIL_H

#include <QDialog>
#include "diary.h"

namespace Ui {
  class detail;
}

class detail : public QDialog
{
  Q_OBJECT

public:
  explicit detail(Diary dr,QWidget *parent = 0);
  ~detail();

private:
  Ui::detail *ui;
};

#endif // DETAIL_H
