#include "helpfield.h"

HelpField::HelpField() {
  setFixedSize(300, 400);
  m_text = "Старт - A";
}

void HelpField::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e)
  QPainter painter;
  painter.begin(this);
  painter.drawRect(0, 0, width(), height());
  painter.setFont(QFont("Arial", 30, 700));
  painter.drawText(QRect(1, 1, width(), height()), Qt::AlignCenter, m_text);
  painter.end();
}

void HelpField::ChangeTextSlot(QString text) {
  m_text = text;
  repaint();
}
