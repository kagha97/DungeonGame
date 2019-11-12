#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#include <iostream>

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Game.h"
#include "GameConstants.h"
#include "Room.h"
#include "ActionRecord.h"


class WindowManager {
 public:
  WindowManager();
  void draw(std::ostream& os, Game& game);
  virtual ~WindowManager();

 protected:

 private:
 std::vector<std::string> boxString(std::string s, int w, int h);
 std::vector<std::string> wrapAR(std::vector<std::string> v, int w, int h);
};

#endif // WINDOWMANAGER_H
