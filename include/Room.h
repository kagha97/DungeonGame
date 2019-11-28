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
  /**
  * Room with id
  * @param roomID Id of room.
  */
  explicit Room(int roomId);

  /**
  * Room with id and desc
  * @param id of room
  * @param room description
  */

  explicit Room(int roomId, std::string desc);

  /**
  * Room from save file data
  * @param inParam info from save file
  */
  explicit Room(std::string inParam);

  /**
  * Room details
  * @return room details
  */
  std::string getDescription();

  /**
    * Room description
    * @return description of room
    */
  std::string getDescriptionOnly();

  /**
    * Items in room
    * @return list of items in room
    */
  std::vector<std::string> getItemList();

  /**
  * NPCs in room
  * @return list of npcs in room
  */
  std::vector<std::string> getNPCList();

  /**
  * Set description of room
  * @param desc Description
  */
  void setDescription(std::string desc);

  /**
  * Add npc to room
  * @param npc NPC to add
  */
  void addNPC(NPC npc);

  /**
    * Add item to room
    * @param item Item to add
    */
  void addItem(Item item);

  /**
  * Items in room
  * @return items in room
  */
  std::vector<Item> getItems();

  /**
  * NPCs in room
  * @return npcs in room
  */
  std::vector<NPC> getNPCS();

  /**
  * List of npcs in room
  * @param List of npcs in room
  */
  std::string showNPCS();

  /**
  * Remove all items from room
  */
  void removeAllItems();

  /**
  * Try key
  * @return true of correct key
  */
  bool tryKey(Item i);
  /**
  * room lock status
  */
  bool locked;

  /**
   * Set to true if you've attempted to enter the room
   */
  bool visited;

  /**
  * room id
  */
  int getId();

  /**
  * Room deconstructor
  */
  virtual ~Room();

 private:
  /**
  * items in room
  */
  std::vector<Item> items;

  /**
  * NPCs in room
  */
  std::vector<NPC> npcs;

  /**
  * Room description
  */
  std::string description;

  /**
  * room id
  */
  int id;
};

#endif  // INCLUDE_ROOM_H_
