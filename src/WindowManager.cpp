#include "WindowManager.h"

WindowManager::WindowManager() {
  //ctor
}

void WindowManager::draw(std::ostream& os, Game& game) {
  os << std::endl << std::endl;

  // Initial values for drawing
  struct winsize win;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
  int width = win.ws_col;
  int height = win.ws_row - 1;
  int pos = game.player.getCurrentRoom();
  int arOffsetY = height - MAXRECORDS;

  std::vector<std::string> mMap = game.miniMap();

  int offset = width - mMap[0].length() - 1;
  std::string hunStr = "Hunger: " + std::to_string(game.player.getHunger());
  std::string hpStr = "HP: " + std::to_string(game.player.getHP());
  int roomDescH = 50;
  std::vector<std::string> roomDesc = boxString(game.getRoomDescription(pos), offset, roomDescH);
  std::vector<std::string> updateBox = generateUpdateBox(&game, offset, MAXRECORDS);
  std::vector<std::string> invList = game.player.getInventoryList();

  for(int y = 0; y < height; y++) {
    for(int x = 0; x < width; x++) {
      // Set up some variables so we know where we are in the window.
      bool aboveMinimap = y < mMap.size();
      bool rightOfMinimap = x >= offset;
      bool charDrawn = false;

      // Draw UpdateBox
      if (!aboveMinimap && !rightOfMinimap && y > arOffsetY && !charDrawn) {
        if(updateBox.size() > 0) {
        int tmpY = y - arOffsetY;
          if(x < updateBox[tmpY].length() && tmpY < updateBox.size()) {
            os << updateBox[tmpY][x];
            charDrawn = true;
          }
        }
      }

      // Draw Room Description in top left corner
      if(x < offset && y < roomDescH && !charDrawn) {

        os << roomDesc[y][x];
        charDrawn = true;
      }

      // Draw minimap in top right corner
      if(aboveMinimap && rightOfMinimap && !charDrawn) {
        os << mMap[y][x - offset];
        charDrawn = true;
      }

      // Draw stats & inventory below minimap
      if (!aboveMinimap && rightOfMinimap && !charDrawn) {
        int tmpY = y + mMap.size();
        int tmpX = x - offset;
        switch(tmpY) {
        case SSTR_D:
          if(tmpX < SSTR.length()) {
          os << SSTR[tmpX];
          charDrawn = true;
          }
          break;
        case HP_D:
          if(tmpX < hpStr.length()) {
          os << hpStr[tmpX];
          charDrawn = true;
          }
          break;
        case HUN_D:
          if(tmpX < hunStr.length()) {
          os << hunStr[tmpX];
          charDrawn = true;
          }
          break;
        case ISTR_D:
          if(tmpX < ISTR.length()) {
          os << ISTR[tmpX];
          charDrawn = true;
          }
          break;
        default:
          break;
        }

        int invItemIndex = tmpY - ISTR_D - 1;
        if(tmpY > ISTR_D && tmpY < IEND_D && invItemIndex < invList.size() && !charDrawn) {
          int r = invList[invItemIndex].length();
          if(tmpX < r) {
            os << invList[invItemIndex][tmpX];
            charDrawn = true;
          }
        }
      }

      if (aboveMinimap && !rightOfMinimap && !charDrawn) {
        os << " ";
        charDrawn = true;
      }

      // Draw empty space
      if(!charDrawn) {
        os << " ";
        charDrawn = true;
      }

    }
    os << std::endl;
  }
  os << "Enter Option: ";
}

std::vector<std::string> WindowManager::wrapAR(std::vector<std::string> v, int w, int h) {
  std::vector<std::string> outVec;
  std::string s(w, ' ');
  if(v.size() == 0) {
    return outVec;
  }
  while(outVec.size() + v.size() < h) {
   outVec.push_back(s);
  }
  for (int i = v.size(); i --> 0; ) {
    outVec.push_back(v[i].length() > w ? v[i].substr(0, w) : v[i]);
  }
  return outVec;
}

std::vector<std::string> WindowManager::boxString(std::string s, int w, int h) {
  std::vector<std::string> outVec;
  s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
  std::stringstream ss;
  int tmp = 0;
  for(int y = 0; y < h; y++) {
    for(int x = 0; x < w; x++) {
      if(tmp < s.length()) {
        ss << s[tmp];
        tmp++;
      } else {
        ss << ' ';
      }
    }
    outVec.push_back(ss.str());
    ss.str("");
  }
  return outVec;
}

std::vector<std::string> WindowManager::generateUpdateBox(Game* game, int w, int h) {
  std::vector<std::string> outVec;
  std::vector<std::string> v;

  switch (game->state) {
  case MainMenu:
    break;
  case Play:
    v = ActionRecord::getFullRecord();
    break;
  case Inventory:
    v.push_back(ActionRecord::getLatest());
    v.push_back("");
    break;
  case ItemUse:
    v.push_back("Which item could you like to use?");
    break;
  case ItemDrop:
    v.push_back("Which item could you like to drop?");
    break;
  case ItemExamine:
    v.push_back("Which item could you like to examine?");
    break;
    }
    std::string s(w, ' ');
    if(v.size() == 0) {
      return outVec;
    }
    while(outVec.size() + v.size() < h) {
      outVec.push_back(s);
    }
    for (int i = v.size(); i --> 0; ) {
      outVec.push_back(v[i].length() > w ? v[i].substr(0, w) : v[i]);
    }
    return outVec;

}


WindowManager::~WindowManager() {
  //dtor
}
