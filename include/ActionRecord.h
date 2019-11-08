#ifndef ACTIONRECORD_H
#define ACTIONRECORD_H
#include <vector>
#include <string>
#include <sstream>
#include "GameConstants.h"

class ActionRecord {
 public:
  ActionRecord();
  static void addRecord(std::string text);
  static std::string getRecords();
  virtual ~ActionRecord();
 protected:

 private:
  static std::vector<std::string> record;
};

#endif // ACTIONRECORD_H
