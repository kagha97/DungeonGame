/*
*Copyright 2019 Fafnir
*/

#include <iostream>
#include <cctype>
#include <fstream>
#include "Game.h"
#include "GameConstants.h"
#include "Player.h"
#include "WindowManager.h"
#include "ActionRecord.h"
#include "StringManipulations.h"

void printRecord(struct winsize w,std::vector<std::string> lines) {
  for (int i = 0; i < w.winsize::ws_row; i++) {
    std::cout << lines[i] << std::endl;
  }
}

bool fileAccessible(std::string fileName) {
  std::ifstream file(fileName);
  return file.good();
}

void gameOver(Player p) {
  std::cout << "YOU DIED" << std::endl;
}

void clearScreen() {
  std::cout << std::string( 100, '\n' );
}


int main() {
  std::cout << "\e[8;" << WINDOWHEIGHT << ";"<< WINDOWWIDTH <<"t";
  Game* game;
  WindowManager wm;
  std::cout << "Welcome to Dungeon Game!" << std::endl;
  std::cout << "Developed by Fafnir Studios LTD. All rights reserved." <<
            std::endl << std::endl;

  bool getStart = true;
  while (getStart) {
    std::cout << "Options:" << std::endl;
    std::cout << "Press " << LOADGAME << " to load a save" << std::endl;
    std::cout << "Press " << NEWGAME << " to start a new game" << std::endl;

    char inputChar;
    std::cin >> inputChar;
    clearScreen();
    switch (std::toupper(inputChar)) {
    case LOADGAME : {
      std::string fileName;
      std::cout << "Please enter the file to load." << std::endl;
      std::cin >> fileName;

      if(!(StringManipulations::hasEnding(fileName, FILEEXT))) {
        fileName += FILEEXT;
      }

      if(fileAccessible(fileName)) {
        game = new Game(fileName);
        getStart = false;
        ActionRecord::addRecord(fileName + " loaded.");
        std::cin.clear();
        break;
      }
      std::cout << "File not found or inaccessible. Please try again." << std::endl;
    }
    break;
    case NEWGAME :
      getStart = false;
      game = new Game(ROOMCOUNT);
      std::cin.clear();


      break;
    default :
      std::cout << "Option not recognized. Please try again." << std::endl;
      break;
    }

  }

  // game->draw(std::cout);

  while (true) {
    std::cout << game->state;
    //game->save(AUTOSAVEFILE);
    wm.draw(std::cout, game);
    game->getInput(std::cin);

    //clearScreen();

    if(game->player.dead) {
      gameOver(game->player);
      break;
    }

    //game->draw(std::cout);
  }
  delete game;

  return 0;
}
