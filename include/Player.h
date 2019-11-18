#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "GameConstants.h"
#include "ActionRecord.h"
#include "Room.h"
#include "Item.h"
#include "ItemType.h"
#include "StringManipulations.h"

class Player
{
  public:
    Player();
    Player(std::string inParam);
    virtual ~Player();
    void addItem(Item i);
    bool consumeItem (Item it);
    bool consumeItem (int it);
    bool removeItem (Item it);
    bool removeItem (int it);
    bool dropItem (int it, Room *room);
    std::string examineItem(int it);
    std::string getStatsString();
    void updateValues();
    bool dead = false;
    void moveTo(int i);
    int getCurrentRoom();
    void finishRiddle (int id);
    bool checkRiddle (int id);
    std::string showInventory();
    std::vector<Item> getInventory();
    std::vector<std::string> getInventoryList();
    std::vector<int> getCompletedRiddles();
    int getHP();
    int getHunger();
  protected:

  private:
    int health = MAXHEALTH;
    int hunger = 0;
    int currentRoom = 0;
    std::vector<int> completedRiddles;
    std::vector<Item> inventory;
};

#endif // PLAYER_H
