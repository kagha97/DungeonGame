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
#include "Item.h"

bool fileAccessible(std::string fileName) {
  std::ifstream file(fileName);
  return file.good();
}

void gameOver(Player p) {
  std::string s(100, '\n');
  std::cout << s;
  std::cout << ActionRecord::getLatest() <<std::endl;
  std::cout << "YOU DIED" << std::endl;
}

void win(Player p) {
  std::cout << "You escape the dungeon and win the game!" << std::endl;
  int score = 0;
  for(Item i : p.getInventory()) {
    score += i.value;
    score += p.getHP();
    score -= p.getHunger();
  }
  std::cout << "Your final score is " << score << std::endl;
  std::cout << "Thanks for playing!" << std::endl;
  char c;
  std::cin >> c;
}

void show_ascii(std::string loc) {
  std::ifstream open(loc);
  std::string out;
  if (open.is_open()) {
    while (open.eof() == false) {
      getline(open, out);
      std::cout << "\x1B[31m" << out << "\x1B[0m" << std::endl;
    }
  }
}

int main() {
  std::cout << "\e[8;" << WINDOWHEIGHT << ";"<< WINDOWWIDTH <<"t";
  Game* game;
  WindowManager wm;
  show_ascii("logo.txt");
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
        std::cout << fileName << " loaded." << std::endl;
        std::cin.clear();
        break;
      }
      std::cout << "File not found or inaccessible. Please try again." << std::endl;
    }
    break;
    case NEWGAME :
      getStart = false;
      game = new Game(ROOMCOUNT);
      std::cout << "New game started with " << ROOMCOUNT << " rooms." << std::endl;
      std::cin.clear();
      break;
    default :
      std::cout << "Option not recognized. Please try again." << std::endl;
      break;
    }

  }

  while (true) {
    //game->save(AUTOSAVEFILE);
    wm.draw(std::cout, game);
    game->getInput(std::cin);
    if(game->player.dead) {
      gameOver(game->player);
      break;
    }

    if(game->state == Win) {
      win(game->player);
      break;
    }
  }
  delete game;

  return 0;
}
