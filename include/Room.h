#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <string>
#include "NPC.h"
#include "Item.h"
#include <string>
#include <sstream>

class Room
{
  public:
    Room(int roomId);
    Room(int roomId, std::string desc);
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
    std::vector<NPC> getNPCs();
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
