#include <QApplication>

#include "Snakewindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  SnakeWindow w;
  w.show();
  QPalette pal = QPalette();
  pal.setColor(QPalette::Window, QColor(124, 91, 0));
  w.setAutoFillBackground(true);
  w.setPalette(pal);
  return a.exec();
}
