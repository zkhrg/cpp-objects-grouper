#include "controller.h"

Controller::Controller() {}

void Controller::setModel(std::unique_ptr<Model> m) { model_ = std::move(m); }

void Controller::parseObjects(std::string s) { model_->Parse(s); }

std::vector<ViewObject> Controller::getObjects(eGrouping grouping, int pageSize,
                                               int pageNumber) {
  return model_->getObjects(grouping, pageSize, pageNumber);
}
