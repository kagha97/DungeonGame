#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <string>
#include <string>
#include <sstream>
#include <algorithm>
#include "NPC.h"
#include "Item.h"
#include "StringManipulations.h"
#include "GameConstants.h"

class Room {
 public:
  Room(int roomId);
  Room(int roomId, std::string desc);
  Room(std::string inParam);
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
  void removeAllItems ();
  bool tryKey(Item i);
  bool locked;
  int getId();
  virtual ~Room();

 protected:

 private:
  std::vector<Item> items;
  std::vector<NPC> npcs;
  std::string description;
  int id;
};

#endif // ROOM_H
