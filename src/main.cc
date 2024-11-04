#include <qlocale.h>

#include <QApplication>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::ControllerObject controller(&model);
  s21::MainWindow w(&controller);
  setlocale(LC_NUMERIC, "C");
  w.show();

  return a.exec();
}
