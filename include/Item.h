/*
*Copyright 2019 Fafnir
*/
#ifndef INCLUDE_ITEM_H_
#define INCLUDE_ITEM_H_
#include "ItemType.h"
#include <string>


class Item {
 public:
  ItemType type;
  Item(std::string n, std::string exam, ItemType t, int val);
  virtual ~Item();
  std::string name;
  int value;
  std::string examine;

  bool operator==(const Item& it) const;

 private:
};

#endif  // INCLUDE_ITEM_H_
