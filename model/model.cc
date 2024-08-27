#include "model.h"

Model::Model() {}

void Model::SetStore(std::unique_ptr<Store> s) { store_ = std::move(s); }

void Model::SetParser(std::unique_ptr<Parser> p) { parser_ = std::move(p); }

void Model::Parse(std::string s) {
  auto v = parser_->Parse(s);
  store_->InsertData(v);
}

std::vector<ViewObject> Model::getObjects(eGrouping grouping, int pageSize,
                                          int pageNumber) {
  return store_->getObjects(grouping, pageSize, pageNumber);
}

void setGroupTypeSize(int size) {}
