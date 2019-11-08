#include "Item.h"

Item::Item(std::string n, std::string exam, ItemType t, int val)
{
  name = n;
  type = t;
  value = val;
  examine = exam;
}

Item::~Item()
{
  //dtor
}
