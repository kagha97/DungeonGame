#include "Game.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

void Game::draw(std::ostream& os) {

  int roomCount = rooms.size();
  if (roomCount < 1)
    return;

//  for (int i = 0; i < roomCount; i++) {
//    std::cout << rooms[i].getDescription();
//    if (currentRoom == i) {
//      std::cout << " Player here" << std::endl;
//    } else {
//      std::cout << std::endl;
//    }
//  }
  if (rooms.size() !=0) {

    int tmpNewLine = 0;
    for (int i = 0; i < roomCount; i++) {
      if (currentRoom == i) {
        std::cout << '[' << "Player" << ']';
      } else {
        std::cout << '[' << rooms[i].getDescription() << ']';
      }
      //std::cout << '[' << rooms[i].getDescription() << ']';
      tmpNewLine++;
      if (tmpNewLine == sqrt(roomCount)) {
        std::cout << std::endl;
        tmpNewLine=0;
      }

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
    rooms.push_back(Room(ss.str()));

  }

  // Connect rooms
  for (int i = 0; i < roomCount; i++) {

  }
}

void Game::movePlayer(char dir) {
  switch (std::toupper(dir)) {
  case 'U' :
    currentRoom -= sqrt(rooms.size());
    break;
  case 'D' :
    currentRoom += sqrt(rooms.size());
    break;
  case 'L' :
    currentRoom -= 1;
    break;
  case 'R' :
    currentRoom += 1;
    break;
  default :

    break;
  }
}

Game::~Game() {

}
