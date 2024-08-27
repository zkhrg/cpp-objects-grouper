#include "controller.h"

Controller::Controller() {}

void Controller::setModel(std::unique_ptr<Model> m) { model_ = std::move(m); }

void Controller::parseObjects(std::string s) { model_->Parse(s); }
