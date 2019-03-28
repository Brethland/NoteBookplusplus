#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
  class settings;
}

class settings : public QDialog
{
  Q_OBJECT

public:
  explicit settings(QWidget *parent = 0);
  ~settings();

private slots:
  void on_passConfirm_clicked();

private:
  Ui::settings *ui;
};

#endif // SETTINGS_H
