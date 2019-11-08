#include "Player.h"

Player::Player() {

}

void Player::moveTo(int i) {
  currentRoom = i;
}

int Player::getCurrentRoom() {
  return currentRoom;
}

void Player::addItem(Item i) {
  inventory.push_back(i);
}

void Player::updateValues() {
  if (hunger < MAXHUNGER) {
    hunger ++;
  } else {
    health -=10;
    std::cout << "You are hungry. You need to find food or you will die!" <<
              std::endl;
  }

  if (health < 1) {
    dead = true;
  }

}


bool Player::consumeItem(Item it) {
  for (int i = 0; i < inventory.size(); i++) {
    switch (it.type) {
    case Food:
      inventory.erase(inventory.begin() + i);

      if (hunger - it.value >= 0) {
        hunger -= inventory[i].value;
        std::cout << "You eat the " << it.name << ". It reduces your hunger by " <<
                  inventory[i].value << "." << std::endl;
      } else {
        hunger = 0;
        std::cout << "You eat the " << it.name << ". You are full." << std::endl;
      }


    case Potion:
      inventory.erase(inventory.begin() + i);

      if (health + it.value <= MAXHEALTH) {
        health += inventory[i].value;
        if (it.value < 0) {
          std::cout << "You drink the " << it.name <<
                    ". It tastes like garbage and it hurts you! " << inventory[i].value <<
                    " health." << std::endl;
        } else {
          std::cout << "You drink the " << it.name << ". It refills " <<
                    inventory[i].value << " health." << std::endl;
        }

      } else {
        health = MAXHEALTH;
        std::cout << "You drink the " << it.name << ". You are fully healed." <<
                  std::endl;
      }

      return true;
    case Treasure:
      std::cout << "You attempt to eat the " << it.name << ". You choke and die." <<
                std::endl;
      dead = true;
      return false;
    case Weapon:
      std::cout << "You attempt to eat the " << it.name << ". You choke and die." <<
                std::endl;
      dead = true;
      return false;
    case Key:
      std::cout << "You attempt to eat the " << it.name << ". You choke and die." <<
                std::endl;
      dead = true;
      return false;
    }
  }

  return false;
}
bool Player::consumeItem(int i) {
  switch (inventory[i].type) {
  case Food:
    inventory.erase(inventory.begin() + i);

    if (hunger - inventory[i].value >= 0) {
      hunger -= inventory[i].value;
      std::cout << "You eat the " << inventory[i].name <<
                ". It reduces your hunger by " <<
                inventory[i].value << "." << std::endl;
    } else {
      hunger = 0;
      std::cout << "You eat the " << inventory[i].name << ". You are full." <<
                std::endl;
    }

  return true;
  case Potion:
    inventory.erase(inventory.begin() + i);

    if (health + inventory[i].value <= MAXHEALTH) {
      health += inventory[i].value;
      if (inventory[i].value < 0) {
        std::cout << "You drink the " << inventory[i].name <<
                  ". It tastes like garbage and it hurts you! " << inventory[i].value <<
                  " health." << std::endl;
      } else {
        std::cout << "You drink the " << inventory[i].name << ". It refills " <<
                  inventory[i].value << " health." << std::endl;
      }

    } else {
      health = MAXHEALTH;
      std::cout << "You drink the " << inventory[i].name << ". You are fully healed."
                <<
                std::endl;
    }

    return true;
  case Treasure:
    std::cout << "You attempt to eat the " << inventory[i].name <<
              ". You choke and die." <<
              std::endl;
    dead = true;
    return false;
  case Weapon:
    std::cout << "You attempt to eat the " << inventory[i].name <<
              ". You choke and die." <<
              std::endl;
    dead = true;
    return false;
  case Key:
    std::cout << "You attempt to eat the " << inventory[i].name <<
              ". You choke and die." <<
              std::endl;
    dead = true;
    return false;
  }
  return true;
}



std::string Player::getStatsString() {
  std::stringstream ss;

  ss << "HP: " << health << std::endl << "Hunger: " << hunger << std::endl;

  return ss.str();
}

std::string Player::showInventory() {
  std::stringstream ss;
  ss << "Inventory:" << std::endl;
  for (int i = 0; i < inventory.size(); i++) {
    ss << i+1 << ". " << inventory[i].name << std::endl;
  }

  return ss.str();
}

std::vector<Item> Player::getInventory() {
  return inventory;
}

Player::~Player() {
  //dtor
}
