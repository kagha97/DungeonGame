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
    void setDescription(std::string desc);
    void addNPC(NPC npc);
    void addItem(Item item);
    void interact(int npcIndex);
    void pickUpItem(int itemIndex);
    std::vector<Item> getItems();
    void removeAllItems ();
    bool tryKey(Item i);
    bool locked;

    virtual ~Room();

  protected:

  private:
    std::vector<Item> items;
    std::vector<NPC> npcs;
    std::string description;
    int id;
};

#endif // ROOM_H
