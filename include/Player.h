#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Item.h"
#include "ItemType.h"
#include "string"
#include  <sstream>
#include "GameConstants.h"
#include <iostream>

class Player
{
  public:
    Player();
    virtual ~Player();
    void addItem(Item i);
    bool consumeItem (Item it);
    std::string getStatsString();
    void increaseHunger();
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
