#include "Game.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

void Game::draw(std::ostream& os) {

  int roomCount = rooms.size();
  if (roomCount < 1)
    return;

  int tmpNewLine = 0;
  for (int i = 0; i < roomCount; i++) {
    if (currentRoom == i) {
      std::cout << '[' << "Player" << ']';
    } else {
      std::cout << '[' << rooms[i].getDescription() << ']';
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
  switch (std::toupper(dir)) {
  case 'U' :
    if (currentRoom < mapWidth) {
      std::cout << "You cannot go that way." << std::endl;
      break;
    }
    moveInt = -mapWidth;
    break;
  case 'D' :
    if (currentRoom + mapWidth >= rooms.size() ) {
      std::cout << "You cannot go that way." << std::endl;
      break;
    }
    moveInt = mapWidth;
    break;
  case 'L' :
    if (currentRoom % mapWidth == 0 ) {
      std::cout << "You cannot go that way." << std::endl;
      break;
    }
    moveInt = -1;
    break;
  case 'R' :
    if ((currentRoom + 1) % mapWidth == 0 ) {
      std::cout << "You cannot go that way." << std::endl;
      break;
    }
    moveInt = 1;
    break;
  default :

    break;
  }
  if (!rooms[currentRoom + moveInt].locked) {
    currentRoom += moveInt;
  } else {
    std::cout << "That room is locked" << std::endl;
  }
}

Game::~Game() {

}
