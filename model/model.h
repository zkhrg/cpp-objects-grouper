#ifndef MODEL_H
#define MODEL_H

#include <memory>

#include "../parser/parser.h"
#include "../store/store.h"

class Model {
 public:
  Model();
  void SetStore(std::unique_ptr<Store> s);
  void SetParser(std::unique_ptr<Parser> p);
  void Parse(std::string s);
  std::vector<ViewObject> getObjects(eGrouping grouping, int pageSize,
                                     int pageNumber);
  void setGroupTypeSize(int size);

 private:
  std::unique_ptr<Store> store_;
  std::unique_ptr<Parser> parser_;
};

#endif  // MODEL_H
