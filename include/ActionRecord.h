/*
*Copyright 2019 Fafnir
*/

#ifndef INCLUDE_ACTIONRECORD_H_
#define INCLUDE_ACTIONRECORD_H_
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

#endif  // INCLUDE_ACTIONRECORD_H_
