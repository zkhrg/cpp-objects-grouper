#include "objectsparser.h"

ObjectsParser::ObjectsParser() {}

std::vector<Object> ObjectsParser::Parse(std::string filePath) {
  std::vector<Object> v;
  std::ifstream file(filePath);

  if (!file.is_open()) {
    std::cerr << "Ошибка открытия файла!" << std::endl;
    return v;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    Object o;

    if (!(iss >> o.name >> o.xCoord >> o.yCoord >> o.gType >> o.timeStamp)) {
      std::cerr << "Ошибка чтения данных!" << std::endl;
      continue;
    }
    v.push_back(o);
  }

  file.close();
  return v;
}
