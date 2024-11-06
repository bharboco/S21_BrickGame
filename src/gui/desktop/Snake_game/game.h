#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include "../../../brick_game/snake/Controller.h"

#define STRING(x) #x
#define XSTRING(x) STRING(x)

class Snake;
class GameField;

class GameField : public QWidget {
  friend class SnakeWindow;
  Q_OBJECT
 public:
  GameField();
  s21::Controller *controller;
  QTimer *m_moveSnakeTimer;

 private:
  void setGameStatus();
  bool m_isMoveBlocked;
  void GameOver();
  void StartNewGame();
  bool game_start = false;

 protected:
  void paintEvent(QPaintEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;
  bool game_over = false;
  bool game_win = false;
  QString m_current_path = XSTRING(THREE_LEVELS_UP);
  QString m_path = "/brick_game/snake/record.txt";

 private slots:
  void MoveSnakeSlots();

 signals:
  void ChangeTextSignal(QString text);
};

#endif  // GAME_H
