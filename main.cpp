#include <QApplication>
#include <QWidget>

#include "mywindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MyWindow w;
  w.show();

  return app.exec();
}
