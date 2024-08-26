#include "mywindow.h"

MyWindow::MyWindow(QWidget *parent) : QWidget(parent) { InitComponents(); }

// группы
// если больше 2 в группе то выделяем отдельную группу, если нет то суем в
// разное

void MyWindow::InitComponents() {
  StartPage();
  // InitMainComponent();
  // InitGroupingComponent();
  // InitFilteringComponent();
  // InitItemsComponent();
}

void MyWindow::InitGroupingComponent() {
  groupingBox = new QGroupBox("grouping", this);
  groupingBoxLayout = new QHBoxLayout();
  mainGroupingBoxLayout = new QVBoxLayout();

  groupingBox->setLayout(mainGroupingBoxLayout);

  groupingSizeWidget = new QWidget(groupingBox);
  groupingSizeWidget->setLayout(groupingBoxLayout);
  btnGroupBySize = new QPushButton("make type groups by size!", groupingBox);
  spbGroupBySize = new QSpinBox(groupingBox);
  groupingBoxLayout->addWidget(btnGroupBySize);
  groupingBoxLayout->addWidget(spbGroupBySize);

  groupByComboBox = new QComboBox();
  mainGroupingBoxLayout->addWidget(groupingSizeWidget);
  mainGroupingBoxLayout->addWidget(groupByComboBox);
  mainGroupingBoxLayout->addStretch();

  leftLayout->addWidget(groupingBox);
}

void MyWindow::InitFilteringComponent() {
  filteringBox = new QGroupBox("Filters", this);
  filteringBoxLayout = new QVBoxLayout(filteringBox);

  filteringBox->setLayout(filteringBoxLayout);

  typesGB = new QGroupBox("types", filteringBox);
  typesCheckboxesLayout = new QVBoxLayout(typesGB);
  int mockTypesCount = 10;
  for (int i = 0; i < mockTypesCount; i++) {
    QCheckBox *cb = new QCheckBox("checky boxy", typesGB);
    typesCheckboxesLayout->addWidget(cb);
  }
  typesCheckboxesLayout->addStretch();
  filteringBoxLayout->addWidget(typesGB);

  namesGB = new QGroupBox("names", filteringBox);
  namesCheckboxesLayout = new QVBoxLayout(namesGB);
  int mockNamesCount = 30;
  for (int i = 0; i < mockNamesCount; i++) {
    QCheckBox *cb = new QCheckBox("name letter box", namesGB);
    namesCheckboxesLayout->addWidget(cb);
  }
  namesCheckboxesLayout->addStretch();
  filteringBoxLayout->addWidget(namesGB);

  distancesGB = new QGroupBox("distances", filteringBox);
  distancesCheckboxesLayout = new QVBoxLayout(distancesGB);
  int distancesCount = 30;
  for (int i = 0; i < distancesCount; i++) {
    QCheckBox *cb = new QCheckBox("distance box", distancesGB);
    distancesCheckboxesLayout->addWidget(cb);
  }
  distancesCheckboxesLayout->addStretch();
  filteringBoxLayout->addWidget(distancesGB);

  datesGB = new QGroupBox("dates", filteringBox);
  datesCheckboxesLayout = new QVBoxLayout(datesGB);
  int datesCount = 2;
  for (int i = 0; i < datesCount; i++) {
    QCheckBox *cb = new QCheckBox("dates box", datesGB);
    datesCheckboxesLayout->addWidget(cb);
  }
  datesCheckboxesLayout->addStretch();
  filteringBoxLayout->addWidget(datesGB);

  leftLayout->addWidget(filteringBox);
}

void MyWindow::InitMainComponent() {
  leftWidget = new QWidget(this);
  leftLayout = new QVBoxLayout(leftWidget);

  rightWidget = new QWidget(this);
  rightLayout = new QVBoxLayout(rightWidget);

  leftScrollArea = new QScrollArea(this);
  leftScrollArea->setWidget(leftWidget);
  leftScrollArea->setWidgetResizable(true);

  rightScrollArea = new QScrollArea(this);
  rightScrollArea->setWidget(rightWidget);
  rightScrollArea->setWidgetResizable(true);

  windowLayout = new QHBoxLayout(this);
  windowLayout->addWidget(leftScrollArea);
  windowLayout->addWidget(rightScrollArea);

  this->setLayout(windowLayout);
  this->setWindowTitle("C++ OBJECTS GROUPING");
  this->resize(800, 600);
}

void MyWindow::InitItemsComponent() {
  for (int i = 0; i < 20; ++i) {
    QLabel *label = new QLabel(
        QString("Name\nDistance\nType\nTime\n %1").arg(i), rightWidget);

    rightLayout->addWidget(label);
  }
}

void MyWindow::StartPage() {
  QGridLayout *startLayout = new QGridLayout();
  QPushButton *btnSelectPath =
      new QPushButton("select file with objects", this);
  connect(btnSelectPath, &QPushButton::clicked, this,
          &MyWindow::openDirectoryDialog);

  btnSelectPath->setFixedHeight(50);
  startLayout->addWidget(btnSelectPath, 0, 0);

  this->setLayout(startLayout);
  this->resize(360, 80);
}

void MyWindow::openDirectoryDialog() {
  // Open a directory selection dialog
  QString directory =
      QFileDialog::getExistingDirectory(this, "Select Directory");

  // Show the selected directory (for demonstration purposes)
  if (!directory.isEmpty()) {
    QMessageBox::information(this, "Selected Directory",
                             "You selected: " + directory);
  }
}
