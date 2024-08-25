#include "mywindow.h"

MyWindow::MyWindow(QWidget *parent) : QWidget(parent) { InitComponents(); }

// группы
// если больше 2 в группе то выделяем отдельную группу, если нет то суем в
// разное

void MyWindow::InitComponents() {
  QWidget *leftWidget = new QWidget(this);
  QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);

  leftLayout->addWidget(filteringBox);

  // Создаем основной виджет для правой области
  QWidget *rightWidget = new QWidget(this);
  QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
  for (int i = 0; i < 20; ++i) {
    QLabel *label = new QLabel(
        QString("Name\nDistance\nType\nTime\n %1").arg(i), rightWidget);

    rightLayout->addWidget(label);
  }

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
  this->setWindowTitle("C++ OBJECTS GROUPING");
  this->resize(800, 600);
}

void MyWindow::InitGroupingComponent() {
  QGroupBox *groupingBox = new QGroupBox("grouping", this);
  QGroupBox *filteringBox = new QGroupBox("filtering", this);
  QHBoxLayout *groupingBoxLayout = new QHBoxLayout();
  QVBoxLayout *mainGroupingBoxLayout = new QVBoxLayout();
  QVBoxLayout *filteringBoxLayout = new QVBoxLayout(filteringBox);

  // Types
  // Names
  // Distance
  // Date

  groupingBox->setLayout(mainGroupingBoxLayout);
  filteringBox->setLayout(filteringBoxLayout);

  QWidget *groupingSizeWidget = new QWidget(groupingBox);
  groupingSizeWidget->setLayout(groupingBoxLayout);
  QPushButton *btnGroupBySize =
      new QPushButton("make type groups by size!", groupingBox);
  QSpinBox *spbGroupBySize = new QSpinBox(groupingBox);
  groupingBoxLayout->addWidget(btnGroupBySize);
  groupingBoxLayout->addWidget(spbGroupBySize);

  QComboBox *groupByComboBox = new QComboBox();
  mainGroupingBoxLayout->addWidget(groupingSizeWidget);
  mainGroupingBoxLayout->addWidget(groupByComboBox);

  QPushButton *btnResetFilters = new QPushButton("reset filters", leftWidget);
  filteringBoxLayout->addWidget(btnResetFilters);

  QGroupBox *typesGB = new QGroupBox("types", filteringBox);
  QVBoxLayout *typesCheckboxesLayout = new QVBoxLayout(typesGB);
  int mockTypesCount = 10;
  for (int i = 0; i < mockTypesCount; i++) {
    QCheckBox *cb = new QCheckBox("checky boxy", typesGB);
    typesCheckboxesLayout->addWidget(cb);
  }
  typesCheckboxesLayout->addStretch();
  filteringBoxLayout->addWidget(typesGB);

  QGroupBox *namesGB = new QGroupBox("names", filteringBox);
  QVBoxLayout *namesCheckboxesLayout = new QVBoxLayout(namesGB);
  int mockNamesCount = 30;
  for (int i = 0; i < mockNamesCount; i++) {
    QCheckBox *cb = new QCheckBox("name letter box", namesGB);
    namesCheckboxesLayout->addWidget(cb);
  }
  namesCheckboxesLayout->addStretch();
  filteringBoxLayout->addWidget(namesGB);

  QGroupBox *distancesGB = new QGroupBox("distances", filteringBox);
  QVBoxLayout *distancesCheckboxesLayout = new QVBoxLayout(distancesGB);
  int distancesCount = 30;
  for (int i = 0; i < distancesCount; i++) {
    QCheckBox *cb = new QCheckBox("distance box", distancesGB);
    distancesCheckboxesLayout->addWidget(cb);
  }
  distancesCheckboxesLayout->addStretch();
  filteringBoxLayout->addWidget(distancesGB);

  QGroupBox *datesGB = new QGroupBox("dates", filteringBox);
  QVBoxLayout *datesCheckboxesLayout = new QVBoxLayout(datesGB);
  int datesCount = 2;
  for (int i = 0; i < datesCount; i++) {
    QCheckBox *cb = new QCheckBox("dates box", datesGB);
    datesCheckboxesLayout->addWidget(cb);
  }
  datesCheckboxesLayout->addStretch();
  filteringBoxLayout->addWidget(datesGB);
  //
  //
  //

  leftLayout->addWidget(groupingBox);
}
