#ifndef ITEM_H
#define ITEM_H
#include <string>
#include "ItemType.h"
#include "GameObject.h"


class Item : public GameObject
{
  public:
    ItemType type;
    Item(int itemId, std::string n, ItemType t, int val);
    virtual ~Item();
    std::string name;
    int value;

  protected:

  private:

};

#endif // ITEM_H
