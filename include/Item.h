#ifndef ITEM_H
#define ITEM_H
#include <string>
#include "ItemType.h"


class Item
{
  public:
    ItemType type;
    Item(std::string n, ItemType t, int val);
    virtual ~Item();
    std::string name;
    int value;

  protected:

  private:

};

#endif // ITEM_H
