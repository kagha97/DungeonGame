#include <iostream>
#include <cctype>
#include "Game.h"

int main() {
  std::cout << "Welcome to Dungeon Game!" << std::endl;
  std::cout << "Developed by Fafnir Studios LTD. All rights reserved." <<
            std::endl << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "Press L to load a save" << std::endl;
  std::cout << "Press N to start a new game" << std::endl;
  Game game;
  bool getStart = true;
  while (getStart) {
    char inputChar;
    std::cin >> inputChar;

    switch (std::toupper(inputChar)) {
    case 'L' :
      getStart = false;
      //TODO: Load Game
      break;
    case 'N' :
      getStart = false;
      //TODO: Generate New Game
      break;
    default :
      std::cout << "Option not recognized. Please try again." << std::endl;
      break;
    }

  }
  while (true) {
    char inputChar;
    std::cin >> inputChar;



    std::cout << inputChar << std::endl;

  }
  return 0;
}
