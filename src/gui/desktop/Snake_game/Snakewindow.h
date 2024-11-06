#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>

#include "../../../brick_game/snake/Controller.h"
#include "game.h"
#include "helpfield.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class SnakeWindow : public QMainWindow {
  Q_OBJECT

 public:
  SnakeWindow(QWidget *parent = nullptr);
  ~SnakeWindow();

 signals:
  void snakeWindowClosed();

 private:
  GameField *m_gameField;
  HelpField *m_helpField;
  s21::Controller *controller;
  QWidget *m_centralWidget;
  QGridLayout *m_gridLayout;
  Ui::MainWindow *ui;
  void closeEvent(QCloseEvent *event);
};
#endif  // MAINWINDOW_H
