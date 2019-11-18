/*
*Copyright 2019 Fafnir
*/
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "ActionRecord.h"


TEST(ActionRecord, GetLatest) {
  ActionRecord::addRecord("1");
  ActionRecord::addRecord("2");
  ActionRecord::addRecord("3");
  std::string s = ActionRecord::getLatest();
  std::string s2 = "3";
  EXPECT_EQ(s, s2);
}

TEST(ActionRecord, GetFull) {
  ActionRecord::addRecord("1");
  ActionRecord::addRecord("2");
  ActionRecord::addRecord("3");
  std::vector<std::string> s = ActionRecord::getFullRecord();
  EXPECT_EQ(s.size(), 9);
}

