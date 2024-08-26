#include "objectsparser.h"

ObjectsParser::ObjectsParser() {}

void ObjectsParser::Parse() {
  std::ifstream file(filePath);

  if (!file.is_open()) {
    std::cerr << "Ошибка открытия файла!" << std::endl;
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string str1, str2;
    double num1, num2, num3;

    if (!(iss >> str1 >> num1 >> num2 >> str2 >> num3)) {
      std::cerr << "Ошибка чтения данных!" << std::endl;
      continue;
    }

    std::cout << "Строка 1: " << str1 << std::endl;
    std::cout << "Число 1: " << num1 << std::endl;
    std::cout << "Число 2: " << num2 << std::endl;
    std::cout << "Строка 2: " << str2 << std::endl;
    std::cout << "Число 3: " << num3 << std::endl;
  }

  file.close();
}
