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
   /**
   * Adds record to output in game
   * @param text The string to output.
   */
  static void addRecord(std::string text);

  /**
   * Returns all of the records
   * @return the records
   */
  static std::vector<std::string> getFullRecord();

  /**
   * Returns the last record
   * @return the latest record
   */
  static std::string getLatest();

 private:
   /**
   * All of the records
   */
  static std::vector<std::string> record;
};

#endif  // INCLUDE_ACTIONRECORD_H_
