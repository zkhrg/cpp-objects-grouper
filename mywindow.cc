#include "mywindow.h"

MyWindow::MyWindow(QWidget *parent) : QWidget(parent) {
  InitComponents();
  currentGroup = "";
  page = 1;
}

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
  groupByComboBox->addItems(QStringList{"No grouping", "By type size",
                                        "By name", "By date", "By distance"});
  connect(groupByComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, &MyWindow::onComboBoxIndexChanged);
  mainGroupingBoxLayout->addWidget(groupingSizeWidget);
  mainGroupingBoxLayout->addWidget(groupByComboBox);
  mainGroupingBoxLayout->addStretch();

  leftLayout->addWidget(groupingBox);
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
  QPushButton *btnNextPage = new QPushButton("next page");
  QPushButton *btnPrevPage = new QPushButton("prev page");
  connect(btnPrevPage, &QPushButton::clicked, this, &MyWindow::DecrementPage);
  connect(btnNextPage, &QPushButton::clicked, this, &MyWindow::IncrementPage);

  windowLayout->addWidget(leftScrollArea);
  windowLayout->addWidget(rightScrollArea);
  windowLayout->addWidget(btnPrevPage);
  windowLayout->addWidget(btnNextPage);

  this->setLayout(windowLayout);
  this->setWindowTitle("C++ OBJECTS GROUPING");
  this->resize(800, 600);
}

void MyWindow::InitItemsComponent(eGrouping grouping) {
  int pageSize = 20;
  if (!rightWidget) return;

  // Получаем указатель на текущий layout
  QLayout *layout = rightWidget->layout();

  if (layout) {
    // Проходим по всем виджетам в layout и удаляем их
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
      QWidget *childWidget = item->widget();
      if (childWidget) {
        childWidget->deleteLater();
      }
      QLayout *childLayout = item->layout();
      if (childLayout) {
        removeLayoutAndWidgets(childLayout->parentWidget());
      }
      delete item;
    }
  }

  auto v = controller_->getObjects(grouping, pageSize, page);
  for (auto it = v.begin(); it != v.end(); ++it) {
    if (QString::fromStdString(it->groupName) != currentGroup) {
      QLabel *l = new QLabel(QString::fromStdString(it->groupName));
      currentGroup = QString::fromStdString(it->groupName);
      rightLayout->addWidget(l);
    }

    QLabel *label = new QLabel(QString("%1\n%2\n%3\n%4\n%5")
                                   .arg(QString::fromStdString(it->name))
                                   .arg(it->xCoord)
                                   .arg(it->yCoord)
                                   .arg(QString::fromStdString(it->gType))
                                   .arg(it->timeStamp),
                               rightWidget);

    rightLayout->addWidget(label);
  }
  currentGroup = "";
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
  QString directory = QFileDialog::getOpenFileName(this, "Select Directory");

  // Show the selected directory (for demonstration purposes)
  if (!directory.isEmpty()) {
    QMessageBox::information(this, "Selected Directory",
                             "You selected: " + directory);
    controller_->parseObjects(directory.toStdString());
    removeLayoutAndWidgets(this);
    InitMainComponent();
    InitGroupingComponent();
    // InitItemsComponent();
  }
}

void MyWindow::SetController(std::unique_ptr<Controller> controller) {
  controller_ = std::move(controller);
}

void MyWindow::removeLayoutAndWidgets(QWidget *widget) {
  if (!widget) return;

  // Получаем указатель на текущий layout
  QLayout *layout = widget->layout();

  if (layout) {
    // Проходим по всем виджетам в layout и удаляем их
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
      QWidget *childWidget = item->widget();
      if (childWidget) {
        childWidget->deleteLater();
      }
      QLayout *childLayout = item->layout();
      if (childLayout) {
        removeLayoutAndWidgets(childLayout->parentWidget());
      }
      delete item;
    }
    delete layout;
  }
}

void MyWindow::onComboBoxIndexChanged(int index) {
  QString selectedText = groupByComboBox->currentText();

  switch (index) {
    case 0:
    case 1:
      InitItemsComponent(eGrouping::Type);
      break;
    case 2:
      InitItemsComponent(eGrouping::Name);
      break;
    case 3:
      InitItemsComponent(eGrouping::Date);
      break;
    case 4:
      InitItemsComponent(eGrouping::Distance);
      break;
  }
}

void MyWindow::IncrementPage() {
  page++;
  onComboBoxIndexChanged(groupByComboBox->currentIndex());
}
void MyWindow::DecrementPage() {
  if (page == 1) {
    return;
  }
  page--;
  onComboBoxIndexChanged(groupByComboBox->currentIndex());
}
