#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // Создаем основной виджет для левой области
  QWidget *leftWidget = new QWidget;
  QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
  for (int i = 0; i < 20; ++i) {
    QPushButton *button =
        new QPushButton(QString("Left Button %1").arg(i), leftWidget);
    leftLayout->addWidget(button);
  }

  // Создаем основной виджет для правой области
  QWidget *rightWidget = new QWidget;
  QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
  for (int i = 0; i < 20; ++i) {
    QPushButton *button =
        new QPushButton(QString("Right Button %1").arg(i), rightWidget);
    rightLayout->addWidget(button);
  }

  // Создаем QScrollArea для левой области
  QScrollArea *leftScrollArea = new QScrollArea;
  leftScrollArea->setWidget(leftWidget);
  leftScrollArea->setWidgetResizable(true);

  // Создаем QScrollArea для правой области
  QScrollArea *rightScrollArea = new QScrollArea;
  rightScrollArea->setWidget(rightWidget);
  rightScrollArea->setWidgetResizable(true);

  // Создаем основной виджет приложения и добавляем в него QHBoxLayout
  QWidget window;
  QHBoxLayout *windowLayout = new QHBoxLayout(&window);

  // Добавляем оба QScrollArea в основной виджет
  windowLayout->addWidget(leftScrollArea);
  windowLayout->addWidget(rightScrollArea);

  window.setLayout(windowLayout);
  window.setWindowTitle("Two Scroll Areas Example");
  window.resize(800, 600);
  window.show();

  return app.exec();
}
