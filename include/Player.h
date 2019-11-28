/*
*Copyright 2019 Fafnir
*/
#ifndef INCLUDE_PLAYER_H_
#define INCLUDE_PLAYER_H_
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "GameConstants.h"
#include "ActionRecord.h"
#include "Room.h"
#include "Item.h"
#include "ItemType.h"
#include "StringManipulations.h"

class Player {
 public:
  /**
  * Holds player info
  */
  Player();

  /**
   * Player info from save file
   * @param inParam used for loading from file
   */
  explicit Player(std::string inParam);

  /**
   * Deconstructor for player
   */
  virtual ~Player();

  /**
   * Add item to inventory
   * @param i Item to add
   */
  void addItem(Item i);

  /**
   * Consume item with item object
   * @param i Item to consume, will use item value
   * @return Whether item was consumed
   */
  bool consumeItem(Item it);

  /**
   * Consume item with index
   * @param it Index of item in inventory
   * @return Whether item was consumed
   */
  bool consumeItem(int it);

  /**
  * Remove item from inventory with object
  * @param it Item object
  * @return Whether item was removed
  */
  bool removeItem(Item it);

  /**
  * Remove item from inventory with item index
  * @param it Index of item
  * @return Whether item was removed
  */
  bool removeItem(int it);

  /**
  * Drop item into room
  * @param it Index of item from inventory
  * @param room what room to drop in
  * @return Whether item was dropped
  */
  bool dropItem(int it, Room *room);

  /**
  * Examine item
  * @param it Index of item in inventory
  * @return Item examine text
  */
  std::string examineItem(int it);

  /**
  * Update player values
  */
  void updateValues();

  /**
  * Player death status
  */
  bool dead = false;

  /**
  * Move player to different room
  * @param i index to move player
  */
  void moveTo(int i);

  /**
  * Current room
  * @return index of room player is in
  */
  int getCurrentRoom();

  /**
  * Add riddle to finished riddles
  * @param id of riddle
  */
  void finishRiddle(int id);

  /**
    * Whether player has completed riddle
    * @return true if player completed riddle
    */
  bool checkRiddle(int id);

  /**
  * Player inventory
  * @return list of items in inventory
  */
  std::vector<Item> getInventory();

  /**
  * List of string of items
  * @return items in string
  */
  std::vector<std::string> getInventoryList();

  /**
    * List of completed riddles
    * @return list of completed riddles
    */
  std::vector<int> getCompletedRiddles();

  /**
  * Player hp
  * @return player HP
  */
  int getHP();

  /**
  * Player hunger
  * @return player hunger
  */
  int getHunger();

 private:
  /**
  * Player max health
  */
  int health = MAXHEALTH;

  /**
    * Current health of player
    */
  int hunger = 0;

  /**
  * Room player is in
  */
  int currentRoom = 0;

  /**
  * Completed riddles
  */
  std::vector<int> completedRiddles;

  /**
  * Items in inventory
  */
  std::vector<Item> inventory;
};

#endif  // INCLUDE_PLAYER_H_
