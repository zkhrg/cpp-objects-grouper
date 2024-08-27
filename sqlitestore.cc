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

  // Создание таблицы 'objects'
  QString createTableQuery =
      "CREATE TABLE IF NOT EXISTS objects ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
      "name TEXT NOT NULL, "
      "x REAL NOT NULL, "
      "y REAL NOT NULL, "
      "group_type TEXT NOT NULL, "
      "time REAL NOT NULL)";
  if (!query.exec(createTableQuery)) {
    qDebug() << "Ошибка создания таблицы:" << query.lastError().text();
    return false;
  }

  return true;
}

void SqliteStore::InsertData(const std::vector<Object> &v) {
  QSqlQuery query;

  for (auto it = v.begin(); it != v.end(); ++it) {
    query.prepare(
        "INSERT INTO objects (name, x, y, group_type, time) "
        "VALUES (:name, :x, :y, :group_type, :time)");

    query.bindValue(":name", QString::fromStdString(it->name));
    query.bindValue(":x", it->xCoord);
    query.bindValue(":y", it->yCoord);
    query.bindValue(":group_type", QString::fromStdString(it->gType));
    query.bindValue(":time", it->timeStamp);

    if (!query.exec()) {
      qDebug() << "Error: Unable to insert data into table.";
      qDebug() << query.lastError().text();
    } else {
      qDebug() << "Data inserted successfully.";
    }
  }
}
