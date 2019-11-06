#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <string>
#include "NPC.h"
#include "Item.h"


class Room
{
  public:
    Room();
    Room(std::string desc);
    std::string getDescription();
    void setDescription(std::string desc);
    void addNPC(NPC npc);
    void addItem(Item item);
    void interact(int npcIndex);
    void pickUpItem(int itemIndex);

    bool locked;

    virtual ~Room();

  protected:

  private:
    std::vector<Item> items;
    std::vector<NPC> npcs;
    std::string description;
};

#endif // ROOM_H
