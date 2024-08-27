#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <string>

#include "model.h"
class Controller {
 public:
  Controller();
  void setModel(std::unique_ptr<Model> m);
  void parseObjects(std::string s);

 private:
  std::unique_ptr<Model> model_;
};

#endif  // CONTROLLER_H
