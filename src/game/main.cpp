#include <iostream>
#include <cctype>
#include "Game.h"
#include "GameConstants.h"
#include "Player.h"
#include <fstream>
#include "WindowManager.h"

void printRecord(struct winsize w,std::vector<std::string> lines)
{
    for (int i = 0; i < w.winsize::ws_row; i++)
    {
        std::cout << lines[i] << std::endl;
    }
}


void gameOver(Player p) {
  std::cout << "YOU DIED" << std::endl;
}

void clearScreen() {
  std::cout << std::string( 100, '\n' );
}


int main() {
  Game* game;
  WindowManager wm;
  std::cout << "Welcome to Dungeon Game!" << std::endl;
  std::cout << "Developed by Fafnir Studios LTD. All rights reserved." <<
            std::endl << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "Press " << LOADGAME << " to load a save" << std::endl;
  std::cout << "Press " << NEWGAME << " to start a new game" << std::endl;
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

  // game->draw(std::cout);



  while (true) {
    wm.draw(std::cout, *game);
    game->getInput(std::cin);

    // clearScreen();

    if(game->player.dead){
        gameOver(game->player);
      break;
    }

    // game->draw(std::cout);
  }


  return 0;
}
