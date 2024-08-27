#include "mywindow.h"

MyWindow::MyWindow(QWidget *parent) : QWidget(parent) {
  InitComponents();
  currentGroup = "";
  page = 1;
}

void MyWindow::InitComponents() {
  StartPage();
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
  QPushButton *btnSavePage = new QPushButton("save page");
  QPushButton *btnChangePage = new QPushButton("change source file");
  connect(btnChangePage, &QPushButton::clicked, this,
          &MyWindow::openDirectoryDialog);
  connect(btnPrevPage, &QPushButton::clicked, this, &MyWindow::DecrementPage);
  connect(btnNextPage, &QPushButton::clicked, this, &MyWindow::IncrementPage);
  connect(btnSavePage, &QPushButton::clicked, this, &MyWindow::saveToFile);

  leftLayout->addWidget(btnChangePage);
  windowLayout->addWidget(leftScrollArea);
  windowLayout->addWidget(rightScrollArea);
  windowLayout->addWidget(btnPrevPage);
  windowLayout->addWidget(btnNextPage);
  windowLayout->addWidget(btnSavePage);

  this->setLayout(windowLayout);
  this->setWindowTitle("C++ OBJECTS GROUPING");
  this->resize(1000, 600);
}

void MyWindow::InitItemsComponent(eGrouping grouping) {
  int pageSize = 20;
  if (!rightWidget) return;

  QLayout *layout = rightWidget->layout();

  if (layout) {
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
  pageContent = "";
  auto v = controller_->getObjects(grouping, pageSize, page);
  for (auto it = v.begin(); it != v.end(); ++it) {
    if (QString::fromStdString(it->groupName) != currentGroup) {
      QString group = QString::fromStdString(it->groupName);
      pageContent += group + "\n\n\n";
      QLabel *l = new QLabel(group);
      currentGroup = QString::fromStdString(it->groupName);
      l->setStyleSheet("font-size: 24px; font-weight: bold;");
      rightLayout->addWidget(l);
    }
    QString obj = QString("name: %1\nx: %2\ny: %3\ntype: %4\nunix_time: %5\n\n")
                      .arg(QString::fromStdString(it->name))
                      .arg(it->xCoord)
                      .arg(it->yCoord)
                      .arg(QString::fromStdString(it->gType))
                      .arg(it->timeStamp);
    pageContent += obj;
    QLabel *label = new QLabel(obj, rightWidget);

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
  }
}

void MyWindow::SetController(std::unique_ptr<Controller> controller) {
  controller_ = std::move(controller);
}

void MyWindow::removeLayoutAndWidgets(QWidget *widget) {
  if (!widget) return;

  QLayout *layout = widget->layout();

  if (layout) {
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

void MyWindow::onComboBoxIndexChanged() {
  page = 1;
  renderObjects();
}

void MyWindow::IncrementPage() {
  page++;
  renderObjects();
}
void MyWindow::DecrementPage() {
  if (page == 1) {
    return;
  }
  page--;
  renderObjects();
}

void MyWindow::renderObjects() {
  switch (groupByComboBox->currentIndex()) {
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

void MyWindow::saveToFile() {
  QString data = pageContent;
  QString directory = QFileDialog::getExistingDirectory(
      nullptr, "Выберите папку для сохранения");

  if (directory.isEmpty()) {
    qDebug() << "Папка не выбрана.";
    return;
  }
  QString filePath = directory + "/output.txt";

  QFile file(filePath);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qDebug() << "Не удалось открыть файл для записи:" << file.errorString();
    return;
  }

  QTextStream out(&file);
  out << data;

  file.close();

  qDebug() << "Данные успешно сохранены в" << filePath;
}
