#include "Snakewindow.h"

#include "./ui_Snakewindow.h"

SnakeWindow::SnakeWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(700, 700);
  controller = new s21::Controller();
  m_gameField = new GameField();
  m_helpField = new HelpField();
  connect(m_gameField, &GameField::ChangeTextSignal, m_helpField,
          &HelpField::ChangeTextSlot);
  m_centralWidget = new QWidget();
  m_gridLayout = new QGridLayout();
  m_gridLayout->addWidget(m_gameField, 0, 0);
  m_gridLayout->addWidget(m_helpField, 0, 1);
  m_centralWidget->setLayout(m_gridLayout);
  setCentralWidget(m_centralWidget);
  QPushButton *exitButton = new QPushButton("Выход", this);
  exitButton->setGeometry(460, 550, 150, 100);
  connect(exitButton, &QPushButton::clicked, this, &SnakeWindow::close);
}

void SnakeWindow::closeEvent(QCloseEvent *event) {
  if (!m_gameField->game_over) m_gameField->GameOver();
  delete m_gameField;
  delete m_helpField;
  delete controller;
  emit snakeWindowClosed();
  event->accept();
}

SnakeWindow::~SnakeWindow() { delete ui; }
