#ifndef OBJECTSPARSER_H
#define OBJECTSPARSER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class ObjectsParser {
 public:
  ObjectsParser();
  void Parse();

 private:
  std::string filePath;
};

#endif  // OBJECTSPARSER_H
