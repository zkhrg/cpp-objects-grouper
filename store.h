#ifndef STORE_H
#define STORE_H

#include "types.h"

class Store {
 public:
  virtual ~Store() = default;

  virtual bool InitStore(std::string &dbPath) = 0;
  // virtual void InsertObject(Object obj) = 0;
  // virtual vvv GetTypesGroups() = 0;
  // virtual vvv GetDatesGroups() = 0;
  // virtual vvv GetDistancesGroups() = 0;
  // virutal vvv Get
};

#endif  // STORE_H
