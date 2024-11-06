#include "gamefield.h"

TetrisGameField::TetrisGameField() {
  setFixedSize(306, 606);
  setFocusPolicy(Qt::StrongFocus);
  startNewGame();
}

void TetrisGameField::startNewGame() {
  flag_pause = false, flag_new_game = true, flag_game_over = false;
  m_game_info = new GameInfo_t;
  m_user_action = new UserAction_t;
  *m_user_action = Start;
  m_random = new Figure_t;
  *m_random = randomGenerate();
  m_random_next = new Figure_t;
  *m_random_next = randomGenerate();
  start(m_game_info, *m_random, *m_random_next,
        m_current_path.toStdString() + m_path.toStdString());
  m_tetris_timer = new QTimer();
  m_move_figure_down_timer = new QTimer();
  connect(m_tetris_timer, &QTimer::timeout, this,
          &TetrisGameField::move_tetris_slot);
  connect(m_move_figure_down_timer, &QTimer::timeout, this,
          &TetrisGameField::move_figure_slot);
  m_tetris_timer->stop();
  m_move_figure_down_timer->stop();
  emit gameOverFieldSignal("");
  setGameStatus();
}

void TetrisGameField::gameOver() {
  flag_new_game = false, flag_game_over = true;
  emit gameOverFieldSignal("GAME OVER");
  setGameStatus();
  m_tetris_timer->stop();
  m_move_figure_down_timer->stop();
  delete m_game_info;
  delete m_user_action;
  delete m_random;
  delete m_random_next;
  delete m_tetris_timer;
  delete m_move_figure_down_timer;
}

void TetrisGameField::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e);
  QPainter painter;
  painter.begin(this);
  QImage image_background(":/new/prefix1/background.png");
  QImage image(":/new/prefix1/pixil-frame-1.png");
  painter.drawImage(0, 0, image_background, 0, 0, 306, 606, Qt::AutoColor);
  if (flag_game_over) return;
  // draw field
  for (int rows = 0; rows < HEIGHT; ++rows) {
    for (int cols = 0; cols < WIDTH; ++cols) {
      if (m_game_info->field[rows][cols] == 3) {
        painter.drawImage((cols - 1) * 30 + 2, (rows - 1) * 30 + 2, image, 2, 2,
                          30, 30, Qt::AutoColor);
      }
    }
  }

  painter.end();
}

void TetrisGameField::keyPressEvent(QKeyEvent *e) {
  if (!flag_new_game && !flag_game_over) {
    if (e->key() == Qt::Key_Left) key = 0404;
    if (e->key() == Qt::Key_Right) key = 0405;
    if (e->key() == Qt::Key_Down && !flag_key) key = 0402, flag_key = true;
    if (e->key() == Qt::Key_Space) key = 32;
    if (e->key() == 'b' || e->key() == 'B') key = 'b';
    if (e->key() == 'q' || e->key() == 'Q') key = 'q';
    if (e->key() == 'p' || e->key() == 'P') key = 'p';
    if (*m_user_action != Terminate) setGameStatus();
  } else if (!flag_new_game && (e->key() == 'a' || e->key() == 'A')) {
    startNewGame();
    return;
  }
}

void TetrisGameField::keyReleaseEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Down && !flag_key) flag_key = false;
}

void TetrisGameField::move_figure_slot() {
  int count = 19, n = 1;
  updateCurrentState(m_game_info, m_user_action, &count, &n, m_random,
                     m_random_next,
                     m_current_path.toStdString() + m_path.toStdString());
  m_move_figure_down_timer->start(m_game_info->speed / 100 * 2);
}

void TetrisGameField::move_tetris_slot() {
  int count = 0;
  setGameStatus();
  for (int i = 0, n = 19; i < n && *m_user_action != Terminate; ++i) {
    m_game_info->direction = 0;
    userInput(m_user_action, key);
    key = 0;
    updateCurrentState(m_game_info, m_user_action, &count, &n, m_random,
                       m_random_next,
                       m_current_path.toStdString() + m_path.toStdString());
    if (m_game_info->previos_speed == m_game_info->speed) flag_key = false;
    m_tetris_timer->start(5);
    repaint();
    ++count;
  }
  setGameStatus();
  if (*m_user_action == Terminate) {
    gameOver();
  }
}

void TetrisGameField::setGameStatus() {
  QString pause_text = "\nPAUSE - 'P'";
  QString select_text = "\nQUIT - 'Q'";
  if (m_game_info->pause && *m_user_action != Terminate)
    pause_text = "\nUNPAUSE - 'P'";
  if (*m_user_action == Terminate) select_text = "\nAGAIN - 'A'";
  QString text = "RECORD: " + QString::number(m_game_info->high_score) +
                 "\nSCORE: " + QString::number(m_game_info->score) +
                 "\nLEVEL: " + QString::number(m_game_info->level) +
                 "\n\n\n\n\n\n\nBOOST - 'B'\nROTATE - 'SPACE'" + pause_text +
                 select_text;
  emit changeTextSignal(text, m_game_info->next);
}

void TetrisGameField::onButtStartClicked() {
  if (flag_game_over) {
    startNewGame();
    return;
  }
  if (!m_tetris_timer->isActive()) {
    m_tetris_timer->start(m_game_info->speed / 1000);
    m_move_figure_down_timer->start(m_game_info->speed / 100 * 2);
    flag_new_game = false;
  }
}
