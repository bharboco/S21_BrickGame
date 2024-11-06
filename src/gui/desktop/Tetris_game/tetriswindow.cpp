#include "tetriswindow.h"

#include "./ui_tetriswindow.h"

TetrisWindow::TetrisWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(575, 660);
  setWindowTitle("Tetris");

  m_game_field = new TetrisGameField();
  m_game_over_field = new TetrisGameOverField();
  m_text_field = new TetrisTextField(m_game_field->m_game_info->high_score,
                                     m_game_field->m_game_info->next);
  connect(m_game_field, &TetrisGameField::changeTextSignal, m_text_field,
          &TetrisTextField::changeTextSlot);
  connect(m_game_field, &TetrisGameField::gameOverFieldSignal,
          m_game_over_field, &TetrisGameOverField::gameOverFieldSlot);
  m_central_widget = new QWidget();
  m_grid_layout = new QGridLayout();

  m_grid_layout->addWidget(m_game_field, 0, 0);
  m_grid_layout->addWidget(m_text_field, 0, 1);
  m_grid_layout->addWidget(m_game_over_field, 0, 0);

  m_central_widget->setLayout(m_grid_layout);
  setCentralWidget(m_central_widget);

  butt_start = new QPushButton{"START", m_central_widget};
  butt_start->setFont(QFont("Arial", 30, 700));
  butt_start->setStyleSheet(
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
  butt_start->setGeometry(365, 390, 165, 37);
  connect(butt_start, &QPushButton::clicked, m_game_field,
          &TetrisGameField::onButtStartClicked);

  butt_exit = new QPushButton{"CLOSE", m_central_widget};
  butt_exit->setFont(QFont("Arial", 30, 700));
  butt_exit->setStyleSheet(
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
  butt_exit->setGeometry(365, 440, 165, 37);

  connect(butt_exit, &QPushButton::clicked, this, &TetrisWindow::close);
}

void TetrisWindow::closeEvent(QCloseEvent *event) {
  if (!m_game_field->flag_game_over) m_game_field->gameOver();
  delete m_game_field;
  delete m_game_over_field;
  delete m_text_field;
  emit tetrisWindowClosed();
  event->accept();
}

TetrisWindow::~TetrisWindow() { delete ui; }
