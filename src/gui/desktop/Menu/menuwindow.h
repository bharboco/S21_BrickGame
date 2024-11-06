#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QApplication>
#include <QDesktopServices>
#include <QMainWindow>
#include <QPushButton>
#include <QUrl>

#include "../Snake_game/Snakewindow.h"
#include "../Tetris_game/tetriswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MenuWindow : public QMainWindow {
  Q_OBJECT

 public:
  MenuWindow(QWidget *parent = nullptr);
  ~MenuWindow();
  bool window_snake = false;
  bool window_tetris = false;

 private:
  Ui::MainWindow *ui;
  QPushButton *m_snake_button, *m_tetris_button, *m_exit_button, *m_developer;
  void createSnakeButton();
  void createTetrisButton();
  void createExitButton();
  void createDeveloperButton();
  void openSnakeWindow();
  void openTetrisWindow();
  void showMenuWindow();
  SnakeWindow *snake_window;
  TetrisWindow *tetris_window;
};
#endif  // MENUWINDOW_H
