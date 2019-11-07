#include "Item.h"

Item::Item(int itemId, std::string n, ItemType t, int val)
{
  name = n;
  type = t;
  value = val;
  id = itemId;
}

Item::~Item()
{
  //dtor
}
