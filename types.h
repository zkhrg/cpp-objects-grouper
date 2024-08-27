#ifndef TYPES_H
#define TYPES_H

#include <string>

struct Object {
  std::string name;
  double xCoord;
  double yCoord;
  std::string gType;
  double timeStamp;
};

struct ViewObject : public Object {
  std::string groupName;
};

enum class eGrouping { Type, Name, Date, Distance };

#endif  // TYPES_H
