#ifndef TETRISGAMEOVERFIELD_H
#define TETRISGAMEOVERFIELD_H

#include <QPainter>
#include <QWidget>

class TetrisGameOverField : public QWidget {
 public:
  TetrisGameOverField();

 private:
  void paintEvent(QPaintEvent *e1) override;
  QString m_text;

 public slots:
  void gameOverFieldSlot(QString text);
};

#endif  // TETRISGAMEOVERFIELD_H
