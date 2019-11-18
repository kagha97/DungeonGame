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
  static std::vector<std::string> Split(std::string inStr, char delim);
  static bool hasEnding(std::string const &fullString,
                         std::string const &ending);

 private:
};

#endif  // INCLUDE_STRINGMANIPULATIONS_H_
