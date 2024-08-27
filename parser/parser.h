#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "../model/types.h"

class Parser {
 public:
  virtual ~Parser() = default;
  virtual std::vector<Object> Parse(std::string) = 0;
};

#endif  // PARSER_H
