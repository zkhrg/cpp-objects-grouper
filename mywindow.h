#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

class MyWindow : public QWidget {
  Q_OBJECT
 public:
  explicit MyWindow(QWidget *parent = nullptr);
  void InitWidgets();

 signals:
};

#endif  // MYWINDOW_H
