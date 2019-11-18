/*
*Copyright 2019 Fafnir
*/

#include "StringManipulations.h"
#include <string>
#include <vector>

std::vector<std::string> StringManipulations::Split(std::string inStr,
    char delim) {
  std::vector<std::string> outVec;
  size_t last = 0;
  size_t next = 0;
  while ((next = inStr.find(delim, last)) != std::string::npos) {
    outVec.push_back(inStr.substr(last, next-last));
    last = next + 1;
  }
  outVec.push_back(inStr.substr(last));
  return outVec;
}

bool StringManipulations::hasEnding(std::string const &fullString,
                                     std::string const &ending) {
  if (fullString.length() >= ending.length()) {
    return (0 == fullString.compare (fullString.length() - ending.length(),
                                     ending.length(), ending));
  } else {
    return false;
  }
  return false;
}
