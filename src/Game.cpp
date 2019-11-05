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
    if (i == 4) {
      rooms[i].locked = true;
    }
  }
}

void Game::movePlayer(char dir) {
  int moveInt = 0;
  switch (std::toupper(dir)) {
  case 'U' :
    moveInt = -(sqrt(rooms.size()));
    break;
  case 'D' :
    moveInt = sqrt(rooms.size());
    break;
  case 'L' :
    moveInt = -1;
    break;
  case 'R' :
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
