/*
*Copyright 2019 Fafnir
*/

#ifndef INCLUDE_WINDOWMANAGER_H_
#define INCLUDE_WINDOWMANAGER_H_
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
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

 private:
  std::vector<std::string> getOptionsVector(Game& game, int width);
  std::vector<std::string> getNpcOrItemVector(Game& game);
  void generatePlayContents(Game& game,
                            std::vector<TextBox>& contents, int width,
                            int height);
  void generatePauseMenu(Game& game, std::vector<TextBox>& contents, int width,
                         int height);
  void generateNPCMenu(Game& game, std::vector<TextBox>& contents, int width,
                       int height);
};

#endif  // INCLUDE_WINDOWMANAGER_H_
