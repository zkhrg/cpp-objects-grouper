#include "controller.h"

Controller::Controller() {}

void Controller::SetStore(std::unique_ptr<Store> s) { store = std::move(s); }
