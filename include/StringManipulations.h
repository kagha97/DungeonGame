#ifndef STRINGMANIPULATIONS_H
#define STRINGMANIPULATIONS_H
#include <string>
#include <vector>
#include <sstream>

class StringManipulations {
 public:
  //StringManipulations();
  //virtual ~StringManipulations();
  static std::vector<std::string> Split(std::string inStr, char delim);
  static bool hasEnding (std::string const &fullString, std::string const &ending);
 protected:

 private:
};

#endif // STRINGMANIPULATIONS_H
