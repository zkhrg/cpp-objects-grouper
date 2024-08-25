#include "mywindow.h"

MyWindow::MyWindow(QWidget *parent) : QWidget(parent) { InitWidgets(); }

void MyWindow::InitWidgets() {
  QGroupBox *groupingBox = new QGroupBox("grouping", this);

  QWidget *leftWidget = new QWidget(this);
  QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
  leftLayout->addWidget(groupingBox);

  // Создаем основной виджет для правой области
  QWidget *rightWidget = new QWidget(this);
  QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
  for (int i = 0; i < 20; ++i) {
    QPushButton *button =
        new QPushButton(QString("Right Button %1").arg(i), rightWidget);

    rightLayout->addWidget(button);
  }
  QHBoxLayout *la = new QHBoxLayout(leftWidget);
  QPushButton *button1 = new QPushButton("asd", leftWidget);
  la->addWidget(button1);
  groupingBox->setLayout(la);

  // Создаем QScrollArea для левой области
  QScrollArea *leftScrollArea = new QScrollArea(this);
  leftScrollArea->setWidget(leftWidget);
  leftScrollArea->setWidgetResizable(true);

  // Создаем QScrollArea для правой области
  QScrollArea *rightScrollArea = new QScrollArea(this);
  rightScrollArea->setWidget(rightWidget);
  rightScrollArea->setWidgetResizable(true);

  // Создаем основной виджет приложения и добавляем в него QHBoxLayout
  QHBoxLayout *windowLayout = new QHBoxLayout(this);

  // Добавляем оба QScrollArea в основной виджет
  windowLayout->addWidget(leftScrollArea);
  windowLayout->addWidget(rightScrollArea);

  this->setLayout(windowLayout);
  this->setWindowTitle("Two Scroll Areas Example");
  this->resize(800, 600);
}
