#ifndef PASSWORD_H
#define PASSWORD_H

#include <QDialog>
#include <string>
#include <cstring>
using namespace std;

namespace Ui {
  class password;
}

class password : public QDialog
{
  Q_OBJECT

public:
  explicit password(string pass,QWidget *parent = 0);
  ~password();

private slots:
  void on_confirm_clicked();

private:
  Ui::password *ui;
  string check;
};

#endif // PASSWORD_H
