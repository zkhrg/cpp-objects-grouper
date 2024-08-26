#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QCheckBox>
#include <QComboBox>
#include <QFileDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

class MyWindow : public QWidget {
  Q_OBJECT
 public:
  explicit MyWindow(QWidget *parent = nullptr);
  void StartPage();
  void InitComponents();
  void InitMainComponent();
  void InitGroupingComponent();
  void InitFilteringComponent();
  void InitItemsComponent();

 signals:
 private:
  void openDirectoryDialog();
  // main
  QWidget *leftWidget, *rightWidget;
  QVBoxLayout *leftLayout, *rightLayout;
  QScrollArea *leftScrollArea, *rightScrollArea;
  QHBoxLayout *windowLayout;

  // groupingComponent
  QGroupBox *groupingBox;
  QHBoxLayout *groupingBoxLayout;
  QVBoxLayout *mainGroupingBoxLayout;
  QWidget *groupingSizeWidget;
  QPushButton *btnGroupBySize;
  QSpinBox *spbGroupBySize;
  QComboBox *groupByComboBox;

  // filteringComponent
  QGroupBox *filteringBox, *typesGB, *namesGB, *distancesGB, *datesGB;
  QVBoxLayout *filteringBoxLayout, *typesCheckboxesLayout,
      *namesCheckboxesLayout, *distancesCheckboxesLayout,
      *datesCheckboxesLayout;
};

#endif  // MYWINDOW_H
