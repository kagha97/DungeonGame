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
#include "GameState.h"
#include "TextBox.h"


class WindowManager {
 public:
  WindowManager();
  void draw(std::ostream& os, Game& game);
  virtual ~WindowManager();

 protected:

 private:
  std::vector<std::string> getOptionsVector(Game& game);
   void generatePlayContents(Game& game, std::vector<TextBox>& contents, int width, int height);
   void generatePauseMenu(Game& game, std::vector<TextBox>& contents, int width, int height);
};

#endif // WINDOWMANAGER_H
