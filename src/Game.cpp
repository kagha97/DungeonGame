#include "Game.h"
void Game::draw(std::ostream& os) {

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

std::string Game::getOptionsString() {
  std::stringstream ss;

  ss << "Enter " << UP << " , " << DOWN << " , " << LEFT << " , " << RIGHT <<
     " to move north, south, west, or east." << std::endl;
  ss << "Enter " << PICK << " to pick up items in the room, if there are any." << std::endl;
  ss << "Enter " << NPCINTERACT << " to see list of NPCS in the room." << std::endl;

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
      for (int i : x.second) {
        rooms[i].addItem(x.first);
      }
    if (x.first.type == Key) {
      // If the item is a key, lock the room corresponding to its value
      rooms[x.first.value].locked = true;
    }
  }

  //add npc to room
  for (auto const& x : NPCS) {
     for (int i : x.second) {
        rooms[i].addNPC(x.first);
      }
  }

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

    break;
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
      player.increaseHunger();
    } else {
      std::cout << "That room is locked" << std::endl;
    }
  }
}

void Game::otherRoomOptions(char op) {
  int currentRoom = player.getCurrentRoom();
  std::vector<Item> items = rooms[currentRoom].getItems();
  switch (std::toupper(op)) {
  case PICK:
    if (items.size() > 0) {
      for (int i = 0; i < items.size(); i++) {
        player.addItem(items[i]);
      }
      rooms[currentRoom].removeAllItems();
      std::cout << "You loot the room." << std::endl;
      break;
    }
  case INVENTORY :
    inventoryScreen();
    //draw(std::cout);
    break;
  case NPCINTERACT :
    if (rooms[currentRoom].getItems().size() != 0) {

    } else {
      std::cout << "There are no NPC's in this room." << std::endl;
    }
    //draw(std::cout);
    break;
  default :

    break;

  }
}



void Game::inventoryScreen() {
  while (true) {
    std::cout << player.showInventory() << std::endl;
    char opt = ' ';
    int number = -1;
    std::cout << "Enter " << USE << " to use an item, " << EXAMINE << " to examine the item, and " << DROP << " to drop an item." << std::endl;
    std::cout << "Enter Option: " << std::endl;
    std::cin >> opt;

    switch (std::toupper(opt)) {
    case USE:
      std::cout << "Which item do you want to use?" << std::endl;
      std::cin >> number;
      if(!player.consumeItem(player.getInventory()[number - 1])) {
        std::cin.clear();
      return;
      }
      break;
    case DROP:
      std::cout << "Which item do you want to drop?" << std::endl;
      std::cin >> number;
      break;
    case EXAMINE:
     std::cout << "Which item do you want to examine?" << std::endl;
      std::cin >> number;
      std::cout << player.getInventory()[number - 1].examine << std::endl;
      break;
    case EXIT:
      std::cin.clear();
      return;
      break;
    default :
      std::cin.clear();
      break;
    }
  }
}

void Game::show_ascii(std::string loc)
{
    std::ifstream open (loc);
    std::string out;
    if(open.is_open())
    {
        while(open.eof() == false)
        {
            getline(open, out);
            std::cout << out << std::endl;
        }
    }
}

Game::~Game() {

}
