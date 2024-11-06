#ifndef TETRISWINDOW_H
#define TETRISWINDOW_H

#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>

#include "gamefield.h"
#include "gameoverfield.h"
#include "textfield.h"

#define STRING(x) #x
#define XSTRING(x) STRING(x)

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class TetrisWindow : public QMainWindow {
  Q_OBJECT

 public:
  TetrisWindow(QWidget *parent = nullptr);
  ~TetrisWindow();

 signals:
  void tetrisWindowClosed();

 private:
  Ui::MainWindow *ui;
  TetrisGameField *m_game_field;
  TetrisTextField *m_text_field;
  TetrisGameOverField *m_game_over_field;
  QPushButton *butt_exit, *butt_start;
  QWidget *m_central_widget;
  QGridLayout *m_grid_layout;
  void closeEvent(QCloseEvent *event);
};
#endif  // TETRISWINDOW_H
