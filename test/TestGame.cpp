/*
*Copyright 2019 Fafnir
*/
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "Game.h"
#include "Player.h"
#include "Exceptions.h"
#include "GameConstants.h"

TEST(Game, Create) {
  Game g(25);
}

TEST(Game, CreateTooManyRooms) {
  EXPECT_THROW(Game g(64), room_count_too_large_error);
}

TEST(Game, CreateNonSquare) {
  EXPECT_THROW(Game g(24), room_count_not_square_error);
}

TEST(Game, GetMiniMapH) {
  Game g(9);
  std::vector<std::string> mm = g.miniMap();
  EXPECT_EQ(mm.size(), 3);
}

TEST(Game, GetMiniMapW) {
  Game g(9);
  g.player = Player();
  std::vector<std::string> mm = g.miniMap();
  EXPECT_EQ(mm[0].length(), 9);
}
