/*
*Copyright 2019 Fafnir
*/

#include "gtest/gtest.h"
#include "TextBox.h"

TEST(TextBox, TestX) {
  TextBox tb(1, 2, 3, 4);
  EXPECT_EQ(tb.posX, 1);
}

TEST(TextBox, TestY) {
  TextBox tb(1, 2, 3, 4);
  EXPECT_EQ(tb.posY, 2);
}

TEST(TextBox, TestW) {
  TextBox tb(1, 2, 3, 4);
  EXPECT_EQ(tb.width, 3);
}

TEST(TextBox, TestH) {
  TextBox tb(1, 2, 3, 4);
  EXPECT_EQ(tb.height, 4);
}

TEST(TextBox, Fill) {
  TextBox tb(1, 2, 3, 4);
  tb.fillChar('%');
  EXPECT_EQ(tb.getAt(1, 1), '%');
}

TEST(TextBox, FillTDS) {
  TextBox tb(0, 0, 4, 4);
  tb.fillTopDown("%%%%");
  EXPECT_EQ(tb.getAt(3, 0), '%');
}

TEST(TextBox, FillTDV) {
  TextBox tb(0, 0, 4, 4);
  tb.fillTopDown({"%", "%", "%"});
  EXPECT_EQ(tb.getAt(0, 2), '%');
}

TEST(TextBox, FillBUS) {
  TextBox tb(0, 0, 4, 4);
  tb.fillBottomUp("%%%%");
  EXPECT_EQ(tb.getAt(3, 3), '%');
}

TEST(TextBox, FillBUV) {
  TextBox tb(0, 0, 4, 4);
  tb.fillBottomUp({"%", "%", "%"});
  EXPECT_EQ(tb.getAt(0, 1), '%');
}

TEST(TextBox, GetAtOutside) {
  TextBox tb(0, 0, 4, 4);
  tb.fillChar('%');
  EXPECT_EQ(tb.getAt(0, 4), ' ');
}
