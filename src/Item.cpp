#include "Item.h"

Item::Item(std::string n, std::string exam, ItemType t, int val)
{
  name = n;
  type = t;
  value = val;
  examine = exam;
}

bool Item::operator==(const Item& it) const
{
  return name == it.name && type == it.type && value == it.value && examine == it.examine;
}


Item::~Item()
{
  //dtor
}
