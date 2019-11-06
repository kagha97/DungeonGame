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

  std::cout << rooms[currentRoom].getDescription() << std::endl;

  int tmpNewLine = 0;
  for (int i = 0; i < roomCount; i++) {
    if (currentRoom == i) {
      std::cout << '[' << "P" << ']';
    } else {
      std::cout << '[' << i << ']';
    }
    tmpNewLine++;
    if (tmpNewLine == sqrt(roomCount)) {
      std::cout << std::endl;
      tmpNewLine=0;
    }
  }

}

Game::Game(std::string filePath) {

}

Game::Game(int roomCount) {
  double sr = sqrt(roomCount);
  if ((sr - floor(sr)) != 0) {
    throw room_count_not_square_error("The number of rooms must be a square number");
  }


  currentRoom = 0;

  // Create rooms
  for (int i = 0; i < roomCount; i++) {
    std::stringstream ss;
    ss << "Room" << i;
    Room newRoom(ss.str());

    rooms.push_back(newRoom);

  }

  // lock rooms
  for (int i = 0; i < roomCount; i++) {

  }
}

void Game::movePlayer(char dir) {
  int moveInt = 0;
  int mapWidth = sqrt(rooms.size());
  bool moved = false;
  std::string dirString;
  switch (std::toupper(dir)) {
  case 'U' :
    if (currentRoom < mapWidth) {
      std::cout << "You cannot go that way." << std::endl;
      break;
    }
    dirString = "north";
    moveInt = -mapWidth;
    moved = true;
    break;
  case 'D' :
    if (currentRoom + mapWidth >= rooms.size() ) {
      std::cout << "You cannot go that way." << std::endl;
      break;
    }
    dirString = "south";
    moveInt = mapWidth;
    moved = true;
    break;
  case 'L' :
    if (currentRoom % mapWidth == 0 ) {
      std::cout << "You cannot go that way." << std::endl;
      break;
    }
    dirString = "west";
    moveInt = -1;
    moved = true;
    break;
  case 'R' :
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
      currentRoom += moveInt;
      std::cout << "You move " << dirString << '.' << std::endl;
    } else {
      std::cout << "That room is locked" << std::endl;
    }
  }
}



Game::~Game() {

}
