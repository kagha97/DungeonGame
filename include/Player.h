#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Item.h"
#include "ItemType.h"
#include "string"
#include  <sstream>

class Player
{
  public:
    Player();
    virtual ~Player();
    void addItem(Item i);
    bool consumeItem (ItemType t);
    std::string getStatsString();
    void increaseHunger();
    bool dead = false;
    void moveTo(int i);
    int getCurrentRoom();
    int getInventory();
  protected:

  private:
    int health = 100;
    int hunger = 0;
    int currentRoom = 0;
    std::vector<Item> inventory;
};

#endif // PLAYER_H
