#include "Game.h"

void Game::draw(std::ostream& os) {
  switch (state) {
  case Play:
    drawPlay(os);
    break;
  case Inventory:
    drawInventory(os);
    break;
  case ItemUse:
    drawInventorySubMenu(os);
    break;
  }
}

void Game::drawPlay(std::ostream& os) {
  int roomCount = rooms.size();
  if (roomCount < 1)
    return;
  int currentRoom = player.getCurrentRoom();
  std::cout << rooms[currentRoom].getDescription() << std::endl;

  int tmpNewLine = 0;
  for (int i = 0; i < roomCount; i++) {
    if (currentRoom == i) {
      std::cout << '[' << "P" << ']';
    } else {
      std::cout << '[' << " " << ']';
    }
    tmpNewLine++;
    if (tmpNewLine == sqrt(roomCount)) {
      std::cout << std::endl;
      tmpNewLine=0;
    }
  }
  std::cout << getOptionsString() << std::endl;
  std::cout << player.getStatsString() << std::endl;
  std::cout << "Enter Option: ";
}

void Game::drawInventory(std::ostream& os) {
  os << player.showInventory() << std::endl;
  char opt = ' ';
  int number = -1;
  os << "Enter " << USE << " to use an item, " << EXAMINE <<
     " to examine the item, and " << DROP << " to drop an item." << std::endl;
  os << "Enter Option: ";
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
    std::cout << "Which item do you want to examine?" << std::endl;
    break;
  }
}

std::string Game::getOptionsString() {
  std::stringstream ss;

  ss << "Enter " << UP << " , " << DOWN << " , " << LEFT << " , " << RIGHT <<
     " to move north, south, west, or east." << std::endl;
  ss << "Enter " << PICK << " to pick up items in the room, if there are any.";

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

  // Create rooms
  for (int i = 0; i < roomCount; i++) {

    Room newRoom(i, ROOMDESC[i]);
    rooms.push_back(newRoom);

  }


  for (auto const& x : ITEMS) {
    rooms[x.second].addItem(x.first);
    if (x.first.type == Key) {
      // If the item is a key, lock the room corresponding to its value
      rooms[x.first.value].locked = true;
    }
  }

}

void Game::getInput(std::istream& inStr) {

  int inInt;
  char inChar;

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
      break;
    }
    break;
  case ItemUse:
    player.consumeItem(inInt - 1);
    state = Inventory;
    break;
  case ItemDrop:
    //player.dropItem(inInt - 1);
    state = Inventory;
    break;
  case ItemExamine:
    //player.examineItem(inInt - 1);
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
      std::cout << "You cannot go that way." << std::endl;
      break;
    }
    dirString = "north";
    moveInt = -mapWidth;
    moved = true;
    break;
  case DOWN :
    if (currentRoom + mapWidth >= rooms.size() ) {
      std::cout << "You cannot go that way." << std::endl;
      break;
    }
    dirString = "south";
    moveInt = mapWidth;
    moved = true;
    break;
  case LEFT :
    if (currentRoom % mapWidth == 0 ) {
      std::cout << "You cannot go that way." << std::endl;
      break;
    }
    dirString = "west";
    moveInt = -1;
    moved = true;
    break;
  case RIGHT :
    if ((currentRoom + 1) % mapWidth == 0 ) {
      std::cout << "You cannot go that way." << std::endl;
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
          std::cout << "You use " << it.name << " to unlock the room." << std::endl;
          player.consumeItem(it);
        }
      }
    }
    if (!rooms[roomIndex].locked) {
      player.moveTo(roomIndex);
      std::cout << "You move " << dirString << '.' << std::endl;
      //std::cout << "ROOM: " << roomIndex << std::endl;
    } else {
      std::cout << "That room is locked" << std::endl;
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
    std::cout << "You loot the room." << std::endl;
  }
}



//void Game::otherRoomOptions(char op) {
//  int currentRoom = player.getCurrentRoom();
//  std::vector<Item> items = rooms[currentRoom].getItems();
//  switch (std::toupper(op)) {
//  case PICK:
//    if (items.size() > 0) {
//      for (int i = 0; i < items.size(); i++) {
//        player.addItem(items[i]);
//      }
//      rooms[currentRoom].removeAllItems();
//      std::cout << "You loot the room." << std::endl;
//      break;
//    }
//  case INVENTORY :
//    inventoryScreen();
//    //draw(std::cout);
//    break;
//  default :
//
//    break;
//
//  }
//}



//void Game::inventoryScreen() {
//  while (true) {
//    std::cout << player.showInventory() << std::endl;
//    char opt = ' ';
//    int number = -1;
//    std::cout << "Enter " << USE << " to use an item, " << EXAMINE << " to examine the item, and " << DROP << " to drop an item." << std::endl;
//    std::cout << "Enter Option: " << std::endl;
//    std::cin >> opt;
//
//    switch (std::toupper(opt)) {
//    case USE:
//      std::cout << "Which item do you want to use?" << std::endl;
//      std::cin >> number;
//      if(!player.consumeItem(player.getInventory()[number - 1])) {
//        std::cin.clear();
//      return;
//      }
//      break;
//    case DROP:
//      std::cout << "Which item do you want to drop?" << std::endl;
//      std::cin >> number;
//      break;
//    case EXAMINE:
//     std::cout << "Which item do you want to examine?" << std::endl;
//      std::cin >> number;
//      break;
//    case EXIT:
//      std::cin.clear();
//      return;
//      break;
//    default :
//      std::cin.clear();
//      break;
//    }
//  }
//}

Game::~Game() {

}
