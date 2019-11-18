#include "gtest/gtest.h"
#include "StringManipulations.h"
#include <string>
#include <vector>

TEST(StringManipulations, Split) {
  std::string s = "1,2,3,4,5";
  std::vector<std::string> v = StringManipulations::Split(s, ',');
  EXPECT_EQ(v.size(), 5);
}

TEST(StringManipulations, EndsWith) {
  std::string s = "1,2,3,4,5";
  bool v = StringManipulations::hasEnding(s, "4,5");
  EXPECT_TRUE(v);
}

TEST(StringManipulations, NotEndsWith) {
  std::string s = "1";
  bool v = StringManipulations::hasEnding(s, "4,");
  EXPECT_FALSE(v);
}
