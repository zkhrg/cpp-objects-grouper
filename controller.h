#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "memory.h"
#include "store.h"

class Controller {
 public:
  Controller();
  void SetStore(std::unique_ptr<Store> s);

 private:
  std::unique_ptr<Store> store;
};

#endif  // CONTROLLER_H
