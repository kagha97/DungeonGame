/*
*Copyright 2019 Fafnir
*/

#include "WindowManager.h"
#include <string>
#include <vector>

WindowManager::WindowManager() {
}

void WindowManager::draw(std::ostream& os, Game* game) {
  // Initial values for drawing
  std::vector<TextBox> contents;
  struct winsize win;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
  int width = win.ws_col;
  int height = win.ws_row - 1;
  char output[height][width];

  switch (game->state) {
  case MainMenu:
    break;
  case Pause:
  case Save:
    generatePauseMenu(game, &contents, width, height);
    break;
  case Win:
    break;
  default: {
    generatePlayContents(game, &contents, width, height);
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
        if (y + t.posY < height && x + t.posX < width) {
          output[y + t.posY][x + t.posX] = t.getAt(x, y);
        }
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

// Style gods demand stupid things. But the green checkmark in GitLab is all th
void WindowManager::generatePlayContents(Game* game,
    std::vector<TextBox>* contents, int width, int height) {
  // Set up Minimap
  std::vector<std::string> mMap = game->miniMap();
  int mMapW = mMap[0].length();

  int splitx = width - mMapW - 6;

  int mMapX = width - mMapW - 3;
  int mMapY = 0;
  int mMapH =  mMap.size();
  TextBox minimap(mMapX, mMapY, mMapW, mMapH);
  minimap.fillTopDown(mMap);
  // Set up stats + inventory
  std::vector<std::string> invList = game->player.getInventoryList();
  int statsX = splitx;
  int statsY = mMapY + mMapH + 1;
  int statsW = width - statsX;
  int statsH = 4 + invList.size() + 1;
  TextBox stats(statsX, statsY, statsW, statsH);
  std::vector<std::string> statVec;
  std::string hunStr = "Hunger: " + std::to_string(game->player.getHunger());
  std::string hpStr = "HP: " + std::to_string(game->player.getHP());
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
  int rDescW = splitx - 1;
  int rDescH = 4;
  int pos = game->player.getCurrentRoom();
  TextBox rDesc(rDescX, rDescY, rDescW, rDescH);
  std::string desc = game->getRoomDescription(pos);
  int npcCount = game->getRoomNPCNames().size();
  if (npcCount == 1) {
    desc += " There is one NPC in the room.";
  }
  if (npcCount > 1) {
    desc += " There are " + std::to_string(npcCount) + " NPCs in the room.";
  }
  rDesc.fillTopDown(desc);

  // Set up room item list
  std::vector<std::string> itemVec = getNpcOrItemVector(game);
  int rItemX = 0;
  int rItemY = rDescH;
  int rItemW = rDescW;
  int rItemH = itemVec.size() + 1;
  TextBox rItem(rItemX, rItemY, rItemW, rItemH);
  rItem.fillTopDown(itemVec);

  // Show available options
  std::vector<std::string> options = getOptionsVector(game, rDescW);
  int optX = 0;
  int optY = rItemY + rItemH + 1;
  int optW = rDescW;
  int optH = 13;
  TextBox opt(optX, optY, optW, optH);
  opt.fillTopDown(options);

  // Set up action record
  int arX = 0;
  int arW = rDescW;
  int arH = MAXRECORDS;
  int arY = height - arH;
  TextBox ar(arX, arY, arW, arH);
  ar.fillBottomUp(ActionRecord::getFullRecord());

  // Set up border things
  TextBox border(splitx - 1, 0, 1, height);
  border.fillChar('|');
  TextBox border2(0, rDescH - 1, splitx - 1, 1);
  border2.fillChar('-');

  // Add textboxes to vector
  contents->push_back(rDesc);
  contents->push_back(minimap);
  contents->push_back(stats);
  contents->push_back(border);
  contents->push_back(border2);
  contents->push_back(opt);
  contents->push_back(rItem);
  contents->push_back(ar);
}

void WindowManager::generatePauseMenu(Game* game,
                                      std::vector<TextBox>* contents,
                                      int width, int height) {
  std::vector<std::string> optVec = getOptionsVector(game, width);
  int tbW = 30;
  int tbH = 12;
  TextBox tb((width / 2) - (tbW / 2), (height / 2) - (tbH / 2), tbW, tbH);
  tb.fillTopDown(optVec);
  contents->push_back(tb);
}

std::vector<std::string> WindowManager::getOptionsVector(Game* game,
    int width) {
  std::vector<std::string> outVec;
  outVec.push_back("Commands:");
  switch (game->state) {
  case MainMenu: {
  }
  case Play: {
    std::string ss = "Enter " +
                     std::string(1, UP) + ", " +
                     std::string(1, DOWN) + ", " +
                     std::string(1, LEFT) + ", or " +
                     std::string(1, RIGHT) + " to move north, south, "
                     "west, or east.";

    outVec.push_back(ss);
    outVec.push_back(std::string(1,
                                 PICK) + " to pick up items in the room, "
                     "if there are any.");
    int npcCount = game->getRoomNPCNames().size();
    if (npcCount > 0) {
      outVec.push_back(std::string(1, TALK) + " to view NPCs.");
    }

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
    outVec.push_back(std::string(1, EXIT) + " to cancel.");
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
    outVec.push_back(std::string(1, TALK) + " to talk to an NPC");
    outVec.push_back(std::string(1, EXMNPC) + " to examine an NPC");
    outVec.push_back(std::string(1, EXIT) + " to cancel.");
  }
  break;
  case TalkNPC: {
    outVec.push_back("Enter the number of the NPC you want to talk to.");
  }
  break;
  case ExamineNPC: {
    outVec.push_back("Enter the number of the NPC you want to examine.");
  }
  break;
  case Talk: {
    outVec = game->getNpcOptions(game->currentChat, width);
  }
  break;
  case Examine: {
    outVec.push_back("Examine Not implemented");
  }
  break;
  case TalkSecond: {
    outVec = game->getNpcOptions(game->nextChat, width);
  }
  break;
  case NPCOptions: {
    outVec.push_back("NPCOptions Not implemented");
  }
  break;
  case RiddleTalk: {
    outVec = game->getNpcOptions(game->nextChat, width);
  }
  break;
  case InteractNPC: {
    outVec.push_back("Enter the number of the NPC you want to talk to.");
  }
  break;
  default: {
    outVec.push_back("Unhandled Game State: " + std::to_string(game->state));
  }
  }

  return outVec;
}
std::vector<std::string> WindowManager::getNpcOrItemVector(Game* game) {
  std::vector<std::string> outVec;
  switch (game->state) {
  case NPCList:
  case TalkNPC:
  case InteractNPC: {
    case ExamineNPC: {
      outVec = game->getRoomNPCNames();
      if (outVec.size() > 0) {
        outVec.insert(outVec.begin(),
                      "You see the following NPC"
                      + (std::string)((outVec.size() > 1) ? "s" : "") +
                      " within the room:");
      } else {
        outVec.clear();
      }
    }
    break;
    default: {
      outVec = game->getRoomItemNames();
      if (outVec.size() > 0) {
        outVec.insert(outVec.begin(),
                      "You see the following item"
                      + (std::string)((outVec.size() > 1) ? "s" : "") +
                      " within the room:");
      } else {
        outVec.clear();
      }
    }
    break;
  }
  }
  return outVec;
}

WindowManager::~WindowManager() {
}
