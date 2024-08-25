#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

class MyWindow : public QWidget {
  Q_OBJECT
 public:
  explicit MyWindow(QWidget *parent = nullptr);
  void InitWidgets();
  void InitGroupingComponent();

 signals:
 private:
  // groupingComponent
  QGroupBox *groupingBox;
  groupingBoxLayout;
  mainGroupingBoxLayout;
  groupingSizeWidget;
  btnGroupBySize;
  spbGroupBySize;
  groupByComboBox;
};

#endif  // MYWINDOW_H
