#include "Player.h"

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


bool Player::consumeItem(Item it) {
  for (int i = 0; i < inventory.size(); i++) {
      switch (it.type) {
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
        if(inventory[i] == it) {

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

std::string Player::showInventory()
{
  std::stringstream ss;
  ss << "Inventory:" << std::endl;
  for (int i = 0; i < inventory.size(); i++) {
        ss << i+1 << ". " << inventory[i].name << std::endl;
    }

  return ss.str();
}

std::vector<Item> Player::getInventory()
{
  return inventory;
}

Player::~Player() {
  //dtor
}
