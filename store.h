#ifndef STORE_H
#define STORE_H

#include <vector>

#include "types.h"

class Store {
 public:
  virtual ~Store() = default;

  virtual bool InitStore(std::string &dbPath) = 0;
  virtual void InsertData(const std::vector<Object> &v) = 0;
  virtual std::vector<ViewObject> getObjects(eGrouping grouping, int pageSize,
                                             int pageNumber) = 0;

  // virtual void InsertObject(Object obj) = 0;
  // virtual vvv GetTypesGroups() = 0;
  // virtual vvv GetDatesGroups() = 0;
  // virtual vvv GetDistancesGroups() = 0;
  // virutal vvv Get
};

#endif  // STORE_H
