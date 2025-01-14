#ifndef OBJECTSPARSER_H
#define OBJECTSPARSER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../model/types.h"
#include "parser.h"

class ObjectsParser : public Parser {
 public:
  ObjectsParser();
  std::vector<Object> Parse(std::string filePath) override;
};

#endif  // OBJECTSPARSER_H
