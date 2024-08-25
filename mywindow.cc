#include "mywindow.h"

MyWindow::MyWindow(QWidget *parent) : QWidget(parent) { InitWidgets(); }

// группы
// если больше 2 в группе то выделяем отдельную группу, если нет то суем в
// разное

void MyWindow::InitWidgets() {
  QWidget *leftWidget = new QWidget(this);
  QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);

  QGroupBox *groupingBox = new QGroupBox("Group by size", this);
  QGroupBox *filteringBox = new QGroupBox("Filters", this);
  QGroupBox *sortingBox = new QGroupBox("Sort", this);
  QHBoxLayout *groupingBoxLayout = new QHBoxLayout(groupingBox);
  QHBoxLayout *filteringBoxLayout = new QHBoxLayout(filteringBox);
  QHBoxLayout *sortingBoxLayout = new QHBoxLayout(sortingBox);

  // Types
  // Names
  // Distance
  // Date

  groupingBox->setLayout(groupingBoxLayout);
  filteringBox->setLayout(filteringBoxLayout);
  sortingBox->setLayout(sortingBoxLayout);

  QPushButton *btnGroupBySize = new QPushButton("group by size!", groupingBox);
  QSpinBox *spbGroupBySize = new QSpinBox(groupingBox);
  groupingBoxLayout->addWidget(btnGroupBySize);
  groupingBoxLayout->addWidget(spbGroupBySize);

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
  leftLayout->addWidget(filteringBox);
  leftLayout->addWidget(sortingBox);

  // Создаем основной виджет для правой области
  QWidget *rightWidget = new QWidget(this);
  QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
  for (int i = 0; i < 20; ++i) {
    QPushButton *button =
        new QPushButton(QString("Right Button %1").arg(i), rightWidget);

    rightLayout->addWidget(button);
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
  this->setWindowTitle("Two Scroll Areas Example");
  this->resize(800, 600);
}
