#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Item.h"
#include "ItemType.h"
#include "string"
#include  <sstream>
#include "GameConstants.h"
#include <iostream>
#include "ActionRecord.h"

class Player
{
  public:
    Player();
    virtual ~Player();
    void addItem(Item i);
    bool consumeItem (Item it);
    bool consumeItem (int it);
    bool removeItem (Item it);
    bool removeItem (int it);
    std::string getStatsString();
    void updateValues();
    bool dead = false;
    void moveTo(int i);
    int getCurrentRoom();
    std::string showInventory();
    std::vector<Item> getInventory();
  protected:

  private:
    int health = MAXHEALTH;
    int hunger = 0;
    int currentRoom = 0;
    std::vector<Item> inventory;
};

#endif // PLAYER_H
