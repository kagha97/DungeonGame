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
#include "ChatOption.h"

class Game {
 public:
  /**
  * A new game object
  * @param roomCount Number of rooms in game.
  * @throw room_count_not_square_error if \a roomCount is not square.
  * @throw room_count_too_large_error if \a roomCount is > 25.
  */
  explicit Game(int roomCount);

  /**
  * Game object with loaded data
  * @param filePath The path to save file.
  * @exception
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
  * Handle input from user while game state is Play
  * @param inChar input char from user.
  */
  void handleInputPlay(char inChar);

  /**
  * Handle input from user while game state is Inventory
  * @param inChar input char from user.
  */
  void handleInputInventory(char inChar);

  /**
  * Handle input from user while game state is Pause
  * @param inChar input char from user.
  */
  void handleInputPause(char inChar);

  /**
  * Handle input from user while game state is NPCMenu
  * @param inChar input char from user.
  */
  void handleInputNPCMenu(char inChar);

  /**
  * Displays ascii from textfile
  * @param loc Path to ascii file
  */
  void show_ascii(std::string loc);

  /**
  * Checks if riddle answer from user is correct
  * @param inp User input.
  */
  void solveRiddle(std::string inp);

  /**
  * Player object
  */
  Player player;

  /**
  * Room description
  * @param r Index of room.
  * @return Room description
  */
  std::string getRoomDescription(int r);

  /**
    * Examines npc
    * @param id Npc id
    * @return npc examine
    */
  std::string examineNPC(int id);

  /**
  * Game state
  */
  State state;

  /**
    * Deconstructor for game
    */
  virtual ~Game();

  /**
    * The minimap in game
    * @return the minimap
    */
  std::vector<std::string> miniMap();

  /**
  * List of all items in room
  * @return list of all items in room
  */
  std::vector<std::string> getRoomItemNames();

  /**
    * Get the chat options of npc
    * @param id The id of chat in map
    * @param Used to make sure text that is displayed is not too wide, and is wrapped
    * @return list of chat options
    */
  std::vector<std::string> getNpcOptions(int id, int width);

  /**
  * List of NPC's in room
  * @return list of NPC's in room
  */
  std::vector<std::string> getRoomNPCNames();

  /**
  * Id of current chat
  */
  int currentChat;

  /**
   * Id of next chat currentChat points to
   */
  int nextChat;

 private:
  /**
  * Current npc player is speaking to
  */
  int currentChatNpc;

  /**
   * Moves player to direction user wants
   * @param dir Direction user wants player to move
   */
  void movePlayer(char dir);

  /**
   * Add all items in room to inventory
   */
  void lootRoom();

  /**
   * List of all rooms in game
   */
  std::vector<Room> rooms;
};

#endif  // INCLUDE_GAME_H_
