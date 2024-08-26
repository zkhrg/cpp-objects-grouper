#ifndef SQLITESTORE_H
#define SQLITESTORE_H
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QtSql>
#include <iostream>
#include <string>

#include "store.h"

class SqliteStore : public Store {
 public:
  SqliteStore();
  bool InitStore(std::string &dbPath) override;
  // void InsertData() override;
};

#endif  // SQLITESTORE_H
