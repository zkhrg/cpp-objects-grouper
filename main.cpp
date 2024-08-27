#include <QApplication>
#include <QWidget>

#include "./controller/controller.h"
#include "./model/model.h"
#include "./parser/objectsparser.h"
#include "./store/sqlitestore.h"
#include "./views/mywindow.h"

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
  model->SetStore(std::move(store));
  model->SetParser(std::move(parser));

  controller->setModel(std::move(model));
  w.SetController(std::move(controller));

  w.show();

  return app.exec();
}
