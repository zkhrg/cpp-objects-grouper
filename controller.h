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
  std::vector<ViewObject> getObjects(eGrouping grouping, int pageSize,
                                     int pageNumber);

 private:
  std::unique_ptr<Model> model_;
};

#endif  // CONTROLLER_H
