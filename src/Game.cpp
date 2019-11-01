#include "Game.h"
#include <iostream>
#include <sstream>
#include <vector>

void Game::draw(std::ostream& os) {

  int roomCount = rooms.size();
  if (roomCount < 1)
    return;

  for (int i = 0; i < roomCount; i++) {
    std::cout << rooms[i].getDescription();
    if (currentRoom == i) {
      std::cout << " Player here" << std::endl;
    } else {
      std::cout << std::endl;
    }
  }

//  for (int i = 0; i < roomCount; i++) {
//    for (int j = 0; j < roomCount; j++) {
//      std::cout << '[' << roomLinks[i][j] << ']';
//    }
//    std::cout << std::endl;
//  }

}

Game::Game(std::string filePath) {

}

Game::Game(int roomCount) {
  currentRoom = 0;

  for (int i = 0; i < roomCount; i++) {
    std::stringstream ss;
    ss << "Room" << i;
    rooms.push_back(Room(ss.str()));
    std::vector<int> temp;
    for (int j = 0; j < roomCount; j++) {
      temp.push_back(0);
    }
    roomLinks.push_back(temp);
  }
}

void Game::movePlayer(char dir) {
  if (roomLinks.size() > 0) {
    switch (std::toupper(dir)) {
    case 'U' :
      currentRoom ++;
      break;
    case 'D' :

      break;
    case 'L' :

      break;
    case 'R' :

      break;
    default :

      break;
    }
  }
}

Game::~Game() {

}
