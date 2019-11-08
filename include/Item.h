#ifndef ITEM_H
#define ITEM_H
#include <string>
#include "ItemType.h"
#include "GameObject.h"


class Item : public GameObject
{
  public:
    ItemType type;
    Item(int itemId, std::string n, std::string exam, ItemType t, int val);
    virtual ~Item();
    std::string name;
    int value;
    std::string examine;

  protected:

  private:

};

#endif // ITEM_H
