/*
*Copyright 2019 Fafnir
*/

#ifndef INCLUDE_ROOM_H_
#define INCLUDE_ROOM_H_
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "NPC.h"
#include "Item.h"
#include "StringManipulations.h"
#include "GameConstants.h"

class Room {
 public:
  explicit Room(int roomId);
  explicit Room(int roomId, std::string desc);
  explicit Room(std::string inParam);
  std::string getDescription();
  std::string getDescriptionOnly();
  std::vector<std::string> getItemList();
  std::vector<std::string> getNPCList();
  void setDescription(std::string desc);
  void addNPC(NPC npc);
  void addItem(Item item);
  void interact(int npcIndex);
  void pickUpItem(int itemIndex);
  std::vector<Item> getItems();
  std::vector<NPC> getNPCS();
  std::string showNPCS();
  void removeAllItems();
  bool tryKey(Item i);
  bool locked;
  int getId();
  virtual ~Room();

 private:
  std::vector<Item> items;
  std::vector<NPC> npcs;
  std::string description;
  int id;
};

#endif  // INCLUDE_ROOM_H_
