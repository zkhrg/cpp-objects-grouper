#include "sqlitestore.h"

SqliteStore::SqliteStore() { std::cout << "asd" << std::endl; }

bool SqliteStore::InitStore(std::string &dbPath) {
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  QDir dir(QString::fromStdString(dbPath));
  if (!dir.exists()) {
    if (!dir.mkpath(QString::fromStdString(dbPath))) {
      qDebug() << "Error: Unable to create directory.";
      return 1;
    }
  }

  db.setDatabaseName(QString::fromStdString(dbPath) + "/sqlite.db");

  if (!db.open()) {
    qDebug() << "Ошибка подключения к базе данных:" << db.lastError().text();
    return false;
  }

  QSqlQuery query;

  // Создание таблицы 'people'
  QString createTableQuery =
      "CREATE TABLE IF NOT EXISTS people ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
      "name TEXT NOT NULL, "
      "age INTEGER NOT NULL)";
  if (!query.exec(createTableQuery)) {
    qDebug() << "Ошибка создания таблицы:" << query.lastError().text();
    return false;
  }

  return true;
}
