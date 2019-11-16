#include "WindowManager.h"

WindowManager::WindowManager() {
  //ctor
}

void WindowManager::draw(std::ostream& os, Game& game)
{
  os << std::endl << std::endl;
  // Initial values for drawing
  std::vector<TextBox> contents;
  struct winsize win;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
  int width = win.ws_col;
  int height = win.ws_row - 1;
  int pos = game.player.getCurrentRoom();
  int arOffsetY = height - MAXRECORDS;
  char output[height][width];

  // Set up Minimap
  std::vector<std::string> mMap = game.miniMap();
  int mMapW = mMap[0].length();
  int mMapX = width - mMapW;
  int mMapY = 0;
  int mMapH =  mMap.size();
  TextBox minimap(mMapX, mMapY, mMapW, mMapH);
  minimap.fillTopDown(mMap);

  // Set up stats + inventory
  std::vector<std::string> invList = game.player.getInventoryList();
  int statsX = mMapX - 5;
  int statsY = mMapY + mMapH;
  int statsW = width - statsX;
  int statsH = 4 + invList.size() + 1;
  TextBox stats(statsX, statsY, statsW, statsH);
  std::vector<std::string> statVec;
  std::string hunStr = "Hunger: " + std::to_string(game.player.getHunger());
  std::string hpStr = "HP: " + std::to_string(game.player.getHP());
  statVec.push_back("Stats:");
  statVec.push_back(hunStr);
  statVec.push_back(hpStr);
  statVec.push_back("Inventory:");
  for(std::string s : invList) {
    statVec.push_back(s);
  }
  stats.fillTopDown(statVec);

  // Set up room description
  int rDescX = 0;
  int rDescY = 0;
  int rDescW = mMapX - 1;
  int rDescH = height / 3;
  TextBox rDesc(rDescX, rDescY, rDescW, rDescH);
  rDesc.fillTopDown(game.getRoomDescription(pos));

  // Set up action record
  int arX = 0;
  int arW = rDescW;
  int arH = MAXRECORDS;
  int arY = height - arH - 1;
  TextBox ar(arX, arY, arW, arH);
  ar.fillBottomUp(ActionRecord::getFullRecord());

  // Add textboxes to vector
  contents.push_back(rDesc);
  contents.push_back(minimap);
  contents.push_back(stats);
  contents.push_back(ar);

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      output[y][x] = ' ';
    }
  }
  for (TextBox t : contents) {
    for (int y = 0; y < t.height; y++) {
      for (int x = 0; x < t.width; x++) {
        output[y + t.posY][x + t.posX] = t.getAt(x, y);
      }
    }
  }
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      os << output[y][x];
    }
    os << std::endl;
  }

  os << "Enter Option: ";
}

//void WindowManager::generateContents(Game& game)
//{
//
//}

WindowManager::~WindowManager() {
  //dtor
}
