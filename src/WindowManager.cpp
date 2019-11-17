#include "WindowManager.h"

WindowManager::WindowManager() {
  //ctor
}

void WindowManager::draw(std::ostream& os, Game& game) {

  // Initial values for drawing
  std::vector<TextBox> contents;
  struct winsize win;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
  int width = win.ws_col;
  int height = win.ws_row - 1;
  char output[height][width];

  switch (game.state) {
  case MainMenu:
    break;
  case Pause:
  case Save:
    generatePauseMenu(game, contents, width, height);
    break;
  case Play:
  case Inventory:
  case ItemUse:
  case ItemDrop:
  case ItemExamine:
    generatePlayContents(game, contents, width, height);
    break;
  case InteractNPC:
    break;
  case Win:
    break;
  default: {
    std::vector<std::string> optVec = getOptionsVector(game);
    TextBox defaultBox(width / 2 - 10, height / 2 - 5, 20, 10);
    defaultBox.fillTopDown(optVec);
    contents.push_back(defaultBox);
    os << game.state << std::endl;
  }
  break;
  }

  os << std::endl << std::endl;
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

void WindowManager::generatePlayContents(Game& game, std::vector<TextBox>& contents, int width, int height) {
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
  int statsX = mMapX;
  int statsY = mMapY + mMapH + 1;
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
  for (std::string s : invList) {
    statVec.push_back(s);
  }
  stats.fillTopDown(statVec);

  // Set up room description
  int rDescX = 0;
  int rDescY = 0;
  int rDescW = mMapX - 1;
  int rDescH = height / 5;
  int pos = game.player.getCurrentRoom();
  TextBox rDesc(rDescX, rDescY, rDescW, rDescH);
  rDesc.fillTopDown(game.getRoomDescription(pos));

  // Set up room item list
  std::vector<std::string> itemVec = game.getRoomItemNames();
  int rItemX = 0;
  int rItemY = rDescH + 1;
  int rItemW = rDescW;
  int rItemH = itemVec.size();
  TextBox rItem(rItemX, rItemY, rItemW, rItemH);
  if (itemVec.size() > 0) {
    itemVec.insert(itemVec.begin(), "You see the following items within the room:");
  } else {
    itemVec.clear();
  }
  rItem.fillTopDown(itemVec);

  // Set up room NPC list
  int rNpcX = 0;
  int rNpcY = 0;
  int rNpcW = width / 2;
  int rNpcH = height / 4;
  TextBox rNpc(rNpcX, rNpcY, rNpcW, rNpcH);
  std::vector<std::string> npcVec = game.getRoomNPCNames();
  //rNpc.fillTopDown();

  // Set up action record
  int arX = 0;
  int arW = rDescW;
  int arH = MAXRECORDS;
  int arY = height - arH;
  TextBox ar(arX, arY, arW, arH);
  ar.fillBottomUp(ActionRecord::getFullRecord());

  // Show available options
  std::vector<std::string> options = getOptionsVector(game);
  int optX = 0;
  int optY = rDescH + 1;
  int optW = rDescW;
  int optH = 8;
  TextBox opt(optX, optY, optW, optH);
  opt.fillTopDown(options);

  // Set up border things
  TextBox border(mMapX - 1, 0, 1, height);
  border.fillChar('|');
  TextBox border2(0, rDescH, mMapX - 1, 1);
  border2.fillChar('-');

  // Add textboxes to vector
  contents.push_back(rDesc);
  contents.push_back(minimap);
  contents.push_back(stats);
  contents.push_back(ar);
  contents.push_back(border);
  contents.push_back(border2);
  contents.push_back(opt);
  contents.push_back(rItem);
}

void WindowManager::generatePauseMenu(Game& game, std::vector<TextBox>& contents, int width, int height) {
  std::vector<std::string> optVec = getOptionsVector(game);
  int tbW = 30;
  int tbH = 12;
  TextBox tb((width / 2) - (tbW / 2), (height / 2) - (tbH / 2), tbW, tbH);
  tb.fillTopDown(optVec);
  contents.push_back(tb);
}

std::vector<std::string> WindowManager::getOptionsVector(Game& game) {
  std::vector<std::string> outVec;
  outVec.push_back("Commands:");
  switch (game.state) {
    case MainMenu: {

    }
    //break;
    case Play: {
      std::string ss = "Enter " +
                       std::string(1, UP) + ", " +
                       std::string(1, DOWN) + ", " +
                       std::string(1, LEFT) + ", or " +
                       std::string(1, RIGHT) + " to move north, south, west, or east.";

      outVec.push_back(ss);
      outVec.push_back(std::string(1, PICK) + " to pick up items in the room, if there are any.");
      outVec.push_back(std::string(1, TALK) + " to see list of NPCS in the room.");
      outVec.push_back(std::string(1, INVENTORY) + " to open your inventory.");
      outVec.push_back(std::string(1, EXIT) + " to open the game menu.");
    }
    break;
    case Pause: {
      outVec.push_back(std::string(1, SAVE) + " to save your game.");
      outVec.push_back(std::string(1, QUIT) + " to quit.");
      outVec.push_back(std::string(1, EXIT) + " to return to the game.");
    }
    break;
    case Save: {
      outVec.push_back("Enter the filename to save.");
      outVec.push_back( std::string(1, EXIT) + " to cancel.");

    }
    break;
    case Load: {
      outVec.push_back("Enter the filename to load.");
    }
    break;
    case Win: {
      outVec.push_back("Not implemented");
    }
    break;
    case Inventory: {
      outVec.push_back(std::string(1, USE) + " to use an item");
      outVec.push_back(std::string(1, DROP) + " to drop an item");
      outVec.push_back(std::string(1, EXAMINE) + " to examine an item");
      outVec.push_back(std::string(1, EXIT) + " to close your inventory.");
    }
    break;
    case ItemUse: {
      outVec.push_back("Enter the number of the item you want to use.");
    }
    break;
    case ItemDrop: {
      outVec.push_back("Enter the number of the item you want to drop.");
    }
    break;
    case ItemExamine: {
      outVec.push_back("Enter the number of the item you want to examine.");
    }
    break;
    case NPCList: {
      outVec.push_back("NPCList Not implemented");
    }
    break;
    case TalkNPC: {
      outVec.push_back("TalkNPC Not implemented");
    }
    break;
    case ExamineNPC: {
      outVec.push_back("Enter the number of the NPC you want to examine.");
    }
    break;
    case Talk: {
      outVec.push_back("Talk Not implemented");
    }
    break;
    case Examine: {
      outVec.push_back("Examine Not implemented");
    }
    break;
    case TalkSecond: {
      outVec.push_back("TalkSecond Not implemented");
    }
    break;
    case NPCOptions: {
      outVec.push_back("NPCOptions Not implemented");
    }
    break;
    case RiddleTalk: {
      outVec.push_back("RiddleTalk Not implemented");
    }
    break;
    case InteractNPC: {
      outVec.push_back("Enter the number of the NPC you want to talk to.");
    }
    break;
    default: {
      outVec.push_back("Unhandled Game State: " + std::to_string(game.state));
    }
  }

  return outVec;
}

void WindowManager::generateNPCMenu(Game& game, std::vector<TextBox>& contents, int width, int height) {

}


WindowManager::~WindowManager() {
  //dtor
}
