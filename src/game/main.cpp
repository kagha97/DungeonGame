#include <iostream>
#include <cctype>
#include "Game.h"
#include "GameConstants.h"
#include "Player.h"

void gameOver(Player p) {
  std::cout << "YOU DIED";
}

void clearScreen() {
  std::cout << std::string( 100, '\n' );
}

int main() {
  std::cout << "Welcome to Dungeon Game!" << std::endl;
  std::cout << "Developed by Fafnir Studios LTD. All rights reserved." <<
            std::endl << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "Press " << LOADGAME << " to load a save" << std::endl;
  std::cout << "Press " << NEWGAME << " to start a new game" << std::endl;
  Game* game;
  bool getStart = true;
  while (getStart) {
    char inputChar;
    std::cin >> inputChar;
    clearScreen();
    switch (std::toupper(inputChar)) {
    case LOADGAME :
      getStart = false;
      //TODO: Load GameB

      break;
    case NEWGAME :
      getStart = false;
      game = new Game(ROOMCOUNT);

      break;
    default :
      std::cout << "Option not recognized. Please try again." << std::endl;
      break;
    }

  }

  game->draw(std::cout);

  while (true) {
    char inputChar;
    std::cin >> inputChar;
    clearScreen();

    game->movePlayer(inputChar);
    game->otherRoomOptions(inputChar);
    game->draw(std::cout);
    if(game->player.dead){
        gameOver(game->player);
      break;
    }
  }




  return 0;
}
