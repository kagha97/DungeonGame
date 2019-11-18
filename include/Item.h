/*
*Copyright 2019 Fafnir
*/
#ifndef INCLUDE_ITEM_H_
#define INCLUDE_ITEM_H_
#include "ItemType.h"
#include <string>


class Item {
 public:
   /**
   * Type of item enum
   */
  ItemType type;

  /**
   * Item object
   * @param n Name of item
   * @param exam Item examine text
   * @param t Type of item
   * @param val Value of item
   */
  Item(std::string n, std::string exam, ItemType t, int val);

  /**
   * Item deconstructor
   */
  virtual ~Item();

  /**
   * name of item
   */
  std::string name;

  /**
   * Item value.
   */
  int value;

  /**
   * Item examine text.
   */
  std::string examine;

  /**
   * Whether items is same as item being compared with
   */
  bool operator==(const Item& it) const;
};

#endif  // INCLUDE_ITEM_H_
