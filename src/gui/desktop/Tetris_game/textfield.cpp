#include "textfield.h"

#include "gamefield.h"

TetrisTextField::TetrisTextField(int record, int matrix[4][4]) {
  setFixedSize(215, 600);
  for (int rows = 0; rows < 4; ++rows) {
    for (int cols = 0; cols < 4; ++cols) {
      m_matrix_next[rows][cols] = matrix[rows][cols];
    }
  }
  m_text = "RECORD: " + QString::number(record) +
           "\nSCORE: 0\nLEVEL: 0\n\n\n\n\n\n\nBOOST - 'B'\nROTATE - "
           "'SPACE'\nPAUSE - "
           "'P'\nQUIT - 'Q'";
}

void TetrisTextField::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e);
  QPainter painter;
  painter.begin(this);
  QImage image_background(":/new/prefix1/color.png");
  QImage image(":/new/prefix1/pixil-frame-1.png");
  painter.drawImage(0, 0, image_background, 0, 0, 215, 600, Qt::AutoColor);
  for (int rows = 0; rows < 4; ++rows) {
    for (int cols = 0; cols < 4; ++cols) {
      if (m_matrix_next[rows][cols] == 3) {
        if (m_matrix_next[2][0] == 3 && m_matrix_next[2][1] == 3 &&
            m_matrix_next[2][2] == 3 && m_matrix_next[2][3] == 3) {
          painter.drawImage((cols - 1) * 30 + 77, (rows - 1) * 30 + 110, image,
                            2, 2, 30, 30, Qt::AutoColor);
        } else {
          painter.drawImage((cols - 1) * 30 + 60, (rows - 1) * 30 + 110, image,
                            2, 2, 30, 30, Qt::AutoColor);
        }
      }
    }
  }
  painter.setPen(QColorConstants::Black);
  painter.setFont(QFont("Arial", 25, 700));
  painter.drawText(QRect(0, 0, width(), height()), Qt::AlignHCenter, m_text);
  painter.end();
}

void TetrisTextField::changeTextSlot(QString text, int matrix[4][4]) {
  m_text = text;
  for (int rows = 0; rows < 4; ++rows) {
    for (int cols = 0; cols < 4; ++cols) {
      m_matrix_next[rows][cols] = matrix[rows][cols];
    }
  }
  repaint();
}
