/*
*Copyright 2019 Fafnir
*/

#include "gtest/gtest.h"
#include "Player.h"
#include "Item.h"
#include "GameConstants.h"

TEST(Player, PlayerTest) {
  Player p();
}

TEST(Player, TestStrConLocation) {
  Player p("{99,5,1,{NULL},{NULL}}");
  EXPECT_TRUE(p.getCurrentRoom() == 1);
}

TEST(Player, TestStrConHP) {
  Player p("{99,5,1,{100},{NULL}}");
  EXPECT_TRUE(p.getHP() == 99);
}

TEST(Player, TestStrConHUN) {
  Player p("{99,5,1,{100},{NULL}}");
  EXPECT_TRUE(p.getHunger() == 5);
}

TEST(Player, TestStrConInv) {
  Player p("{99,5,1,{100},{NULL}}");
  EXPECT_TRUE(p.getInventory().size() == 1);
}

TEST(Player, TestStrConCRid) {
  Player p("{99,5,1,{100},{3}}");
  EXPECT_TRUE(p.getCompletedRiddles().size() == 1);
}

TEST(Player, TestStrConInvList) {
  Player p("{99,5,1,{100},{NULL}}");
  EXPECT_TRUE(p.getInventoryList().size() == 1);
}

TEST(Player, RemoveItem) {
  Player p("{99,5,1,{100},{NULL}}");
  Item i = ITEMS.at(100);
  p.removeItem(i);
  EXPECT_TRUE(p.getInventoryList().size() == 0);
}

TEST(Player, TryRemoveItem) {
  Player p("{99,5,1,{NULL},{NULL}}");
  Item i = ITEMS.at(100);
  EXPECT_FALSE(p.removeItem(i));
}

TEST(Player, DropItem) {
  Player p("{99,5,1,{100},{NULL}}");
  Room r(0);
  bool b = p.dropItem(0, &r);
  Item i = ITEMS.at(100);
  Item o = r.getItems()[0];
  EXPECT_TRUE(b && i == o);
}

TEST(Player, AddItem) {
  Player p("{99,5,1,{100},{NULL}}");
  Item i = ITEMS.at(100);
  p.addItem(i);
  EXPECT_TRUE(p.getInventoryList().size() == 2);
}

TEST(Player, EatKey) {
  Player p("{99,5,1,{100},{NULL}}");
  Item i = ITEMS.at(100);
  p.consumeItem(i);
  bool b = p.dead;
  EXPECT_TRUE(b);
}

TEST(Player, EatWeapon) {
  Player p("{99,5,1,{100},{NULL}}");
  Item w("", "", Weapon, 1);
  p.addItem(w);
  p.consumeItem(1);
  bool b = p.dead;
  EXPECT_TRUE(b);
}

TEST(Player, TryConsume) {
  Player p("{99,5,1,{100},{NULL}}");
  Item w("", "", Weapon, 1);
  p.addItem(w);
  bool b = p.consumeItem(-1);
  EXPECT_FALSE(b);
}

TEST(Player, EatTreasure) {
  Player p("{99,5,1,{100},{NULL}}");
  Item w("", "", Treasure, 1);
  p.addItem(w);
  p.consumeItem(1);
  bool b = p.dead;
  EXPECT_TRUE(b);
}

TEST(Player, EatFood) {
  Player p("{99,5,1,{NULL},{NULL}}");
  Item w("", "", Food, 5);
  p.addItem(w);
  p.consumeItem(0);
  EXPECT_EQ(p.getHunger(), 0);
}

TEST(Player, EatFoodFull) {
  Player p("{99,5,1,{NULL},{NULL}}");
  Item w("", "", Food, 6);
  p.addItem(w);
  p.consumeItem(0);
  EXPECT_EQ(p.getHunger(), 0);
}

TEST(Player, DrinkPotion) {
  Player p("{50,5,1,{NULL},{NULL}}");
  Item w("", "", Potion, 5);
  p.addItem(w);
  p.consumeItem(0);
  EXPECT_EQ(p.getHP(), 55);
}

TEST(Player, DrinkPotionFull) {
  Player p("{50,5,1,{NULL},{NULL}}");
  Item w("", "", Potion, 50);
  p.addItem(w);
  p.consumeItem(0);
  EXPECT_EQ(p.getHP(), MAXHEALTH);
}

TEST(Player, DrinkBadPotion) {
  Player p("{50,5,1,{NULL},{NULL}}");
  Item w("", "", Potion, -50);
  p.addItem(w);
  p.consumeItem(0);
  EXPECT_EQ(p.getHP(), 0);
}

TEST(Player, MoveTo) {
  Player p("{99,5,1,{100},{NULL}}");
  p.moveTo(3);
  EXPECT_TRUE(p.getCurrentRoom() == 3);
}

TEST(Player, HungerMove) {
  Player p("{99,5,1,{100},{NULL}}");
  p.moveTo(3);
  EXPECT_TRUE(p.getHunger() == 5 + HUNGERGAIN);
}

TEST(Player, MoveHPLoss) {
  Player p("{99,99,1,{100},{NULL}}");
  p.moveTo(3);
  EXPECT_TRUE(p.getHP() == 99 - HEALTHLOSS);
}

TEST(Player, MoveDie) {
  Player p("{0,0,1,{100},{NULL}}");
  p.moveTo(3);
  EXPECT_TRUE(p.dead);
}

TEST(Player, ExamineItem) {
  Player p("{50,5,1,{NULL},{NULL}}");
  Item w("", "P", Potion, 50);
  p.addItem(w);
  EXPECT_EQ(p.examineItem(0), "P");
}
