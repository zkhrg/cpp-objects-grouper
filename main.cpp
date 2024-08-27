#include <QApplication>
#include <QWidget>

#include "controller.h"
#include "model.h"
#include "mywindow.h"
#include "objectsparser.h"
#include "sqlitestore.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MyWindow w;

  QString qdbPath =
      QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

  std::unique_ptr<Model> model = std::make_unique<Model>();
  std::unique_ptr<Store> store = std::make_unique<SqliteStore>();
  std::unique_ptr<Controller> controller = std::make_unique<Controller>();
  std::unique_ptr<Parser> parser = std::make_unique<ObjectsParser>();

  std::string dbPath = qdbPath.toStdString();
  store->InitStore(dbPath);

  std::vector<Object> v;
  v.push_back({.name = "фыва",
               .xCoord = 13.13,
               .yCoord = 1313.222,
               .gType = "asddd",
               .timeStamp = 99.3});

  store->InsertData(v);
  model->SetStore(std::move(store));
  model->SetParser(std::move(parser));

  controller->setModel(std::move(model));
  w.SetController(std::move(controller));

  w.show();

  return app.exec();
}
