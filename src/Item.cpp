#include "Item.h"

Item::Item(std::string n, ItemType t, int val)
{
  name = n;
  type = t;
  value = val;
}

Item::~Item()
{
  //dtor
}
