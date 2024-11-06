#ifndef TETRISTEXTFIELD_H
#define TETRISTEXTFIELD_H

#include <QPainter>
#include <QWidget>

class TetrisTextField : public QWidget {
 public:
  class GameField;
  TetrisTextField(int record, int matrix[4][4]);

 protected:
  void paintEvent(QPaintEvent *e) override;

 private:
  QString m_text;
  int m_matrix_next[4][4];
 public slots:
  void changeTextSlot(QString text, int matrix[4][4]);
};

#endif  // TETRISTEXTFIELD_H
