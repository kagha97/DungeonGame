#include "Game.h"

void Game::draw(std::ostream& os) {
  int cr = player.getCurrentRoom();
  switch (state) {
  case Play:
    drawPlay(os);
    os << rooms[cr].getDescription() << std::endl;
    os << ActionRecord::getRecords() << std::endl;
    break;
  case Inventory:
    drawInventory(os);
    os << ActionRecord::getLatest() << std::endl;
    break;
  case ItemUse:
  case ItemDrop:
  case ItemExamine:
    drawInventorySubMenu(os);
    break;
  case InteractNPC:
    break;
  default:
    break;
  }
  os << std::endl;
  os << "Enter Option: ";
}

void Game::drawPlay(std::ostream& os) {
  int roomCount = rooms.size();
  if (roomCount < 1)
    return;
  int currentRoom = player.getCurrentRoom();
  //ActionRecord::addRecord(rooms[currentRoom].getDescription());

  int tmpNewLine = 0;
  for (int i = 0; i < roomCount; i++) {
    if (currentRoom == i) {
      os << '[' << "P" << ']';
    } else {
      os << '[' << " " << ']';
    }
    tmpNewLine++;
    if (tmpNewLine == sqrt(roomCount)) {
      os << std::endl;
      tmpNewLine=0;
    }
  }
  os << getOptionsString() << std::endl;
  os << player.getStatsString() << std::endl;
}

void Game::drawInventory(std::ostream& os) {
  os << player.showInventory() << std::endl;
  char opt = ' ';
  int number = -1;
  os << "Enter " << USE << " to use an item, " << EXAMINE <<
     " to examine the item, and " << DROP << " to drop an item." << std::endl;
}

void Game::drawInventorySubMenu(std::ostream& os) {
  drawInventory(os);
  switch (state) {
  case ItemUse:
    os << "Which item do you want to use?" << std::endl;
    break;
  case ItemDrop:
    os << "Which item do you want to drop?" << std::endl;
    break;
  case ItemExamine:
    os << "Which item do you want to examine?" << std::endl;
    break;
  }
}

std::string Game::getOptionsString() {
  std::stringstream ss;

  ss << "Enter " << UP << " , " << DOWN << " , " << LEFT << " , " << RIGHT <<
     " to move north, south, west, or east." << std::endl;
  ss << "Enter " << PICK << " to pick up items in the room, if there are any." <<
     std::endl;
  ss << "Enter " << NPCINTERACT << " to see list of NPCS in the room." <<
     std::endl;

  return ss.str();
}


Game::Game(std::string filePath) {

}

Game::Game(int roomCount) {
  double sr = sqrt(roomCount);
  if ((sr - floor(sr)) != 0) {
    throw room_count_not_square_error("The number of rooms must be a square number");
  }
  if (roomCount > 25) {
    throw room_count_too_large_error("Cannot have more than 25 rooms");
  }

  state = Play;

  // Create rooms
  for (int i = 0; i < roomCount; i++) {

    Room newRoom(i, ROOMDESC[i]);
    rooms.push_back(newRoom);

  }


  for (auto const& x : ITEMLOCATIONS) {
    for (int i : x.second) {
      rooms[i].addItem(ITEMS.at(x.first));
    }
    if (ITEMS.find(x.first)->second.type == Key) {
      //If the item is a key, lock the room corresponding to its value
      rooms[ITEMS.find(x.first)->second.value].locked = true;
    }
  }

  //add npc to room
  for (auto const& x : NPCLOCATIONS) {
    for (int i : x.second) {
      rooms[i].addNPC(NPCS.at(x.first));
    }
  }

}

void Game::getInput(std::istream& inStr) {
  int inInt = 0;
  char inChar = ' ';

  switch (state) {
  case MainMenu:
  case Play:
  case Inventory:
    inStr >> inChar;
    inChar = std::toupper(inChar);
    break;
  case ItemUse:
  case ItemDrop:
  case ItemExamine:
    inStr >> inInt;
    break;
  }

  switch (state) {
  case MainMenu:
  case Play:
    switch (inChar) {
    case INVENTORY:
      state = Inventory;
      ActionRecord::addRecord("You open your inventory.");
      break;
    case UP:
    case DOWN:
    case LEFT:
    case RIGHT:
      movePlayer(inChar);
      break;
    case PICK:
      lootRoom();
      break;
    }
    break;
  case Inventory:
    switch (inChar) {
    case USE:
      state = ItemUse;
      break;
    case DROP:
      state = ItemDrop;
      break;
    case EXAMINE:
      state = ItemExamine;
      break;
    case EXIT:
      state = Play;
      ActionRecord::addRecord("You close your inventory.");
      break;
    }
    break;
  case ItemUse:
    player.consumeItem(inInt - 1);
    state = Inventory;
    break;
  case ItemDrop:
    player.dropItem(inInt - 1, &rooms[player.getCurrentRoom()]);
    state = Inventory;
    break;
  case ItemExamine:
    player.examineItem(inInt - 1);
    state = Inventory;
    break;
  }
  inStr.clear();
}

void Game::movePlayer(char dir) {
  int moveInt = 0;
  int currentRoom = player.getCurrentRoom();
  int mapWidth = sqrt(rooms.size());
  bool moved = false;
  std::string dirString;
  switch (std::toupper(dir)) {
  case UP :
    if (currentRoom < mapWidth) {
      ActionRecord::addRecord("You cannot go that way.");
      break;
    }
    dirString = "north";
    moveInt = -mapWidth;
    moved = true;
    break;
  case DOWN :
    if (currentRoom + mapWidth >= rooms.size() ) {
      ActionRecord::addRecord("You cannot go that way.");
      break;
    }
    dirString = "south";
    moveInt = mapWidth;
    moved = true;
    break;
  case LEFT :
    if (currentRoom % mapWidth == 0 ) {
      ActionRecord::addRecord("You cannot go that way.");
      break;
    }
    dirString = "west";
    moveInt = -1;
    moved = true;
    break;
  case RIGHT :
    if ((currentRoom + 1) % mapWidth == 0 ) {
      ActionRecord::addRecord("You cannot go that way.");
      break;
    }
    dirString = "east";
    moveInt = 1;
    moved = true;
    break;
  default :
    return;
    //break;
  }
  if (moved) {
    int roomIndex = currentRoom + moveInt;

    if (rooms[roomIndex].locked) {
      for (Item it : player.getInventory()) {
        if (rooms[roomIndex].tryKey(it)) {
          ActionRecord::addRecord("You use " + it.name + " to unlock the room.");
          player.removeItem(it);
        }
      }
    }
    if (!rooms[roomIndex].locked) {
      player.moveTo(roomIndex);
      ActionRecord::addRecord("You move " + dirString + ".");
    } else {
      ActionRecord::addRecord("That room is locked");
    }
  }
  player.updateValues();
}

void Game::lootRoom() {
  int currentRoom = player.getCurrentRoom();
  std::vector<Item> items = rooms[currentRoom].getItems();
  if (items.size() > 0) {
    for (int i = 0; i < items.size(); i++) {
      player.addItem(items[i]);
    }
    rooms[currentRoom].removeAllItems();
    ActionRecord::addRecord("You loot the room.");
  }
}

void Game::show_ascii(std::string loc) {
  std::ifstream open(loc);
  std::string out;
  if (open.is_open()) {
    while (open.eof() == false) {
      getline(open, out);
      std::cout << out << std::endl;
    }
  }
}

std::vector<std::string> Game::miniMap() {
  int roomCount = rooms.size();
  int s = sqrt(roomCount);

  std::vector<std::string> outVec;
  int currentRoom = player.getCurrentRoom();
  int tempCounter = 0;

  for(int h = 0; h < s; h++) {
    std::stringstream ss;
    for(int w = 0; w < s; w++) {
      if(currentRoom == tempCounter) {
        ss << "[*]";
      } else {
        ss << "[ ]";
      }

      tempCounter++;
    }
    outVec.push_back(ss.str());
  }
  return outVec;
}

std::string Game::getRoomDescription(int r)
{
    return rooms[r].getDescriptionOnly();
}


Game::~Game() {

}
