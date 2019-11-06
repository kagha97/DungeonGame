#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Item.h"
#include "ItemType.h"

class Player
{
  public:
    Player();
    virtual ~Player();
    void addItem(Item i);
    bool consumeItem (ItemType t);

  protected:

  private:
    int health = 100;
    int hunger = 100;
    std::vector<Item> inventory;
};

#endif // PLAYER_H
