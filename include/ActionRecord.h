#ifndef ACTIONRECORD_H
#define ACTIONRECORD_H
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include "GameConstants.h"
#include "GameState.h"

class ActionRecord {
 public:
  static void addRecord(std::string text);
  static std::string getRecords();
  static std::vector<std::string> getFullRecord();
  static std::string getLatest();

 private:
  static std::vector<std::string> record;
};

#endif // ACTIONRECORD_H
