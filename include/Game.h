/*
*Copyright 2019 Fafnir
*/

#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_
#include <math.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Room.h"
#include "Player.h"
#include "GameConstants.h"
#include "Exceptions.h"
#include "GameState.h"
#include "ActionRecord.h"
#include "StringManipulations.h"

class Game {
 public:

    /**
   * A new game object
   * @param roomCount Number of rooms in game.
   */
  explicit Game(int roomCount);

   /**
   * Game object with loaded data
   * @param filePath The path to save file.
   */
  explicit Game(std::string filePath);

   /**
   * Saves game
   * @param filePath Path to save game.
   */
  void save(std::string filePath);

 /**
   * Get input from user
   * @param inStr input stream from user.
   */
  void getInput(std::istream& inStr);

   /**
   * A new game object
   * @param loc Path to ascii file
   */
  void show_ascii(std::string loc);
  void solveRiddle(std::string inp);
  Player player;
  std::string getRoomDescription(int r);
  std::string examineNPC(int id);
  State state;
  virtual ~Game();
  std::vector<std::string> miniMap();
  std::vector<std::string> getRoomItemNames();
  std::vector<std::string> getNpcOptions(int id, int width);
  std::vector<std::string> getRoomNPCNames();
  int currentChat;
  int nextChat;

 private:
  int currentChatNpc;
  void movePlayer(char dir);
  void lootRoom();
  std::vector<Room> rooms;
};

#endif  // INCLUDE_GAME_H_
