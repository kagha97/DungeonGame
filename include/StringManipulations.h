/*
*Copyright 2019 Fafnir
*/

#ifndef INCLUDE_STRINGMANIPULATIONS_H_
#define INCLUDE_STRINGMANIPULATIONS_H_
#include <string>
#include <vector>
#include <sstream>

class StringManipulations {
 public:
    /**
   * Splitting string so it fits
   */
  static std::vector<std::string> Split(std::string inStr, char delim);

   /**
   * string has Ending
   */
  static bool hasEnding(std::string const &fullString,
                         std::string const &ending);
};

#endif  // INCLUDE_STRINGMANIPULATIONS_H_
