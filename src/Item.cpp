#include "Item.h"

Item::Item(int itemId, std::string n, std::string exam, ItemType t, int val)
{
  name = n;
  type = t;
  value = val;
  id = itemId;
  examine = exam;
}

Item::~Item()
{
  //dtor
}
