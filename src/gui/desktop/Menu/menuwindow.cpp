#include "menuwindow.h"

#include "./ui_menuwindow.h"

MenuWindow::MenuWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(300, 300);

  createSnakeButton();
  connect(m_snake_button, &QPushButton::clicked, this,
          &MenuWindow::openSnakeWindow);

  createTetrisButton();
  connect(m_tetris_button, &QPushButton::clicked, this,
          &MenuWindow::openTetrisWindow);

  createExitButton();
  connect(m_exit_button, &QPushButton::clicked, this, &MenuWindow::close);
}

void MenuWindow::createSnakeButton() {
  m_snake_button = new QPushButton("SNAKE", this);
  m_snake_button->setFont(QFont("Arial", 30, 700));
  m_snake_button->setStyleSheet(
      "QPushButton {"
      "color: black;"
      "background-color: rgb(124, 91, 0);"
      "border: 1px solid black;"
      "}"
      "QPushButton:hover {"
      "background-color: rgb(124, 150, 0);"
      "}"
      "QPushButton:pressed {"
      "background-color: rgb(124, 91, 0);"
      "}");
  m_snake_button->setGeometry(70, 35, 160, 37);
}

void MenuWindow::createTetrisButton() {
  m_tetris_button = new QPushButton("TETRIS", this);
  m_tetris_button->setFont(QFont("Arial", 30, 700));
  m_tetris_button->setStyleSheet(
      "QPushButton {"
      "color: black;"
      "background-color: rgb(124, 91, 0);"
      "border: 1px solid black;"
      "}"
      "QPushButton:hover {"
      "background-color: rgb(124, 150, 0);"
      "}"
      "QPushButton:pressed {"
      "background-color: rgb(124, 91, 0;"
      "}");
  m_tetris_button->setGeometry(70, 85, 160, 37);
}

void MenuWindow::createExitButton() {
  m_exit_button = new QPushButton{"CLOSE", this};
  m_exit_button->setFont(QFont("Arial", 30, 700));
  m_exit_button->setStyleSheet(
      "QPushButton {"
      "color: black;"
      "background-color: rgb(124, 91, 0);"
      "border: 1px solid black;"
      "}"
      "QPushButton:hover {"
      "background-color: rgb(124, 150, 0);"
      "}"
      "QPushButton:pressed {"
      "background-color: rgb(124, 91, 0);"
      "}");
  m_exit_button->setGeometry(70, 135, 160, 37);
}

void MenuWindow::openSnakeWindow() {
  snake_window = new SnakeWindow(this);
  connect(snake_window, &SnakeWindow::snakeWindowClosed, this,
          &MenuWindow::showMenuWindow);
  window_snake = true;
  snake_window->show();
  QPalette pal = QPalette();
  pal.setColor(QPalette::Window, QColor(124, 91, 0));
  snake_window->setAutoFillBackground(true);
  snake_window->setPalette(pal);
  this->hide();
}

void MenuWindow::openTetrisWindow() {
  tetris_window = new TetrisWindow(this);
  connect(tetris_window, &TetrisWindow::tetrisWindowClosed, this,
          &MenuWindow::showMenuWindow);
  window_tetris = true;
  tetris_window->show();
  QPalette pal = QPalette();
  pal.setColor(QPalette::Window, QColor(124, 91, 0));
  tetris_window->setAutoFillBackground(true);
  tetris_window->setPalette(pal);
  this->hide();
}

void MenuWindow::showMenuWindow() {
  if (window_snake == true) {
    delete snake_window;
    window_snake = false;
  }
  if (window_tetris == true) {
    delete tetris_window;
    window_tetris = false;
  }
  this->show();
}

MenuWindow::~MenuWindow() { delete ui; }
