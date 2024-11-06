#ifndef TETRISGAMEFIELD_H
#define TETRISGAMEFIELD_H

#include <QDebug>
#include <QFontDatabase>
#include <QKeyEvent>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

#include "../../../brick_game/tetris/tetris.h"

#define STRING(x) #x
#define XSTRING(x) STRING(x)

#define WIDTH 12
#define HEIGHT 22

class TetrisGameField : public QWidget {
  friend class TetrisWindow;
  Q_OBJECT

 public:
  TetrisGameField();

 protected:
  QString m_current_path = XSTRING(THREE_LEVELS_UP);
  QString m_path = "/brick_game/tetris/record.txt";
  GameInfo_t *m_game_info;

 private:
  void paintEvent(QPaintEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;
  void keyReleaseEvent(QKeyEvent *e) override;
  QTimer *m_tetris_timer, *m_move_figure_down_timer;
  UserAction_t *m_user_action;
  Figure_t *m_random, *m_random_next;
  bool flag_key = false, flag_boost = false, flag_new_game = false,
       flag_pause = false, flag_game_over = false;
  bool userActionPerformed = false;
  int key = 0;
  void startNewGame();
  void gameOver();
  void setGameStatus();
  void handleKeyPress(QKeyEvent *e);

 public slots:
  void onButtStartClicked();

 private slots:
  void move_tetris_slot();
  void move_figure_slot();

 signals:
  void changeTextSignal(QString text, int matrix[4][4]);
  void gameOverFieldSignal(QString text);
};

#endif  // TETRISGAMEFIELD_H
