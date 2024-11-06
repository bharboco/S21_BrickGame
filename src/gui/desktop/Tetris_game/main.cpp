#include <QApplication>

#include "tetriswindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  TetrisWindow w;
  w.show();
  QPalette pal = QPalette();
  pal.setColor(QPalette::Window, QColor(124, 91, 0));
  w.setAutoFillBackground(true);
  w.setPalette(pal);
  return a.exec();
}
