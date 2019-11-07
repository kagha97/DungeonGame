#include "Player.h"
#include "ItemType.h"

Player::Player() {

}

void Player::moveTo(int i)
{
  currentRoom = i;
}

int Player::getCurrentRoom()
{
  return currentRoom;
}

void Player::addItem(Item i) {
  inventory.push_back(i);
}

void Player::increaseHunger() {
  if (hunger < 100) {
    hunger ++;
  } else {
    health -=10;
  }

  if(health < 0) {
    dead = true;
  }

}


bool Player::consumeItem(ItemType t) {
  for (int i = 0; i < inventory.size(); i++) {
    if (inventory[i].type == t) {
      switch (t) {
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

std::string Player::getStatsString() {
  std::stringstream ss;

  ss << "HP: " << health << std::endl << "Hunger: " << hunger << std::endl;

  return ss.str();
}

Player::~Player() {
  //dtor
}
