#include "Player.h"
#include "ItemType.h"

void Player::addItem(Item i)
{
  inventory.push_back(i);
}

bool Player::consumeItem(ItemType t)
{
  for (int i = 0; i < inventory.size(); i++) {
      if (inventory[i].type == t) {
          switch(t)
          {
          case Potion:
          case Food:
             inventory.erase(inventory.begin() + i);
            health += inventory[i].value;
            return true;
          case Treasure:

            break;
          case Weapon:
            break;
          case Key:
            inventory.erase(inventory.begin() + i);
            return true;
          }

      }
  }
  return false;
}



Player::~Player()
{
  //dtor
}
