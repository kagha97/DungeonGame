#ifndef ITEM_H
#define ITEM_H
#include <string>
#include "ItemType.h"

class Item {
 public:
  ItemType type;
  Item(std::string n, std::string exam, ItemType t, int val);
  virtual ~Item();
  std::string name;
  int value;
  std::string examine;

  bool operator==(const Item& it) const;

 protected:

 private:

};

#endif // ITEM_H
