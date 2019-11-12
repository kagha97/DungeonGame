#ifndef NPC_H
#define NPC_H
#include "Item.h"
#include <vector>
#include <string>

class NPC
{
  public:
    NPC(std::string n);
    bool hostile;
    virtual ~NPC();
    void addItem(Item i);
    std::string name;

  protected:

  private:
    int health = 100;
    std::vector<Item> inventory;
};

#endif // NPC_H
