#include <QApplication>
#include <QWidget>

#include "controller.h"
#include "mywindow.h"
#include "sqlitestore.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QString qdbPath =
      QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
  Controller controller;
  auto store = std::make_unique<SqliteStore>();
  std::string dbPath = qdbPath.toStdString();
  store->InitStore(dbPath);
  controller.SetStore(std::move(store));
  // Model model;

  MyWindow w;
  w.show();

  return app.exec();
}
