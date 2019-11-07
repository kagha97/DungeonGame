#include "Game.h"
#include "Exceptions.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>


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
    std::stringstream ss;
    ss << "Room" << i;
    Room newRoom(ss.str());

    rooms.push_back(newRoom);

  }
  rooms[0].setDescription("fancy room");
  Item item("Treasure", Treasure, 9001);
  rooms[0].addItem(item);

  // lock rooms
  for (int i = 0; i < roomCount; i++) {
    if (i == 12 || i == 20 || i == 5 || i == 25) {
      rooms[i].locked = true;
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
    if (!rooms[currentRoom + moveInt].locked) {
      player.moveTo(currentRoom + moveInt);
      std::cout << "You move " << dirString << '.' << std::endl;
      player.increaseHunger();
    } else {
      std::cout << "That room is locked" << std::endl;
    }
  }
}



Game::~Game() {

}
