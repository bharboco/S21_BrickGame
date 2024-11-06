#include "game.h"

#include <QDebug>

GameField::GameField() {
  setFixedSize(360, 660);
  setFocusPolicy(Qt::StrongFocus);
  StartNewGame();
}

void GameField::setGameStatus() {
  QString pause_text = "\n\nPAUSE - 'P'";
  QString select_text = "\nQUIT - 'Q'";
  QString start_text = "\nStart - 'A'";
  if (controller->getPause()) {
    pause_text = "\n\nUNPAUSE - 'P'";
  }
  if (game_over) select_text = "\nAGAIN - 'S'";
  QString text = "RECORD: " + QString::number(controller->getMaxScore()) +
                 "\nSCORE: " + QString::number(controller->getScore()) +
                 "\nLEVEL: " + QString::number(controller->getLvl()) +
                 pause_text + select_text + start_text;
  emit ChangeTextSignal(text);
}

void GameField::GameOver() {
  if (controller->getScore() == 196) {
    game_win = true;
  } else {
    game_over = true;
  }
  setGameStatus();
  m_moveSnakeTimer->stop();
  repaint();
  delete controller;
  delete m_moveSnakeTimer;
}

void GameField::StartNewGame() {
  game_win = false, game_start = false;
  game_over = false;
  m_isMoveBlocked = false;
  controller = new s21::Controller();
  m_moveSnakeTimer = new QTimer();
  connect(m_moveSnakeTimer, &QTimer::timeout, this, &GameField::MoveSnakeSlots);
  m_moveSnakeTimer->stop();
  setGameStatus();
}

void GameField::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e)
  QPainter painter;
  painter.begin(this);
  if (game_over) {
    painter.setFont(QFont("Arial", 30, 900));
    painter.drawText(QRect(1, 1, width(), height()), Qt::AlignCenter,
                     "игра проиграна");
    return;
  } else if (game_win == true) {
    painter.setFont(QFont("Arial", 30, 900));
    painter.drawText(QRect(1, 1, width(), height()), Qt::AlignCenter,
                     "Поздравляем с победой");
    return;
  }
  painter.drawRect(30, 30, width() - 60, height() - 60);
  painter.setBrush(Qt::darkGreen);
  for (int i = 0; i < controller->getBody().size(); ++i) {
    painter.drawRect(controller->getBody()[i].x * 30,
                     controller->getBody()[i].y * 30, 30, 30);
  }
  painter.setBrush(Qt::red);
  painter.drawEllipse(controller->getFood().x * 30,
                      controller->getFood().y * 30, 30, 30);
  painter.end();
  m_isMoveBlocked = false;
}

void GameField::keyPressEvent(QKeyEvent *e) {
  if (game_over && e->key() == Qt::Key_S) {
    StartNewGame();
    repaint();
    return;
  }

  if (!game_over && !controller->getPause() && e->key() == Qt::Key_A) {
    game_start = true;
    if (!m_moveSnakeTimer->isActive()) {
      m_moveSnakeTimer->start(controller->getSpeed() / 1000);
    }
  }

  if (game_start) {
    if (!game_over && e->key() == Qt::Key_P) {
      controller->setPause();
      if (controller->getPause()) {
        m_moveSnakeTimer->stop();
      } else
        m_moveSnakeTimer->start(controller->getSpeed() / 1000);
      setGameStatus();
    }
    if (m_isMoveBlocked) {
      return;
    }
    if (e->key() == Qt::Key_Left) {
      controller->changeDirection('a');
    }
    if (e->key() == Qt::Key_Right) {
      controller->changeDirection('d');
    }
    if (e->key() == Qt::Key_Q) {
      GameOver();
    }
    m_isMoveBlocked = true;
  }
}

void GameField::MoveSnakeSlots() {
  controller->moveSnake(m_current_path.toStdString() + m_path.toStdString());
  setGameStatus();
  if (controller->getCheckCollision()) {
    GameOver();
  }
  repaint();
}
