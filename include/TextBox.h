/*
*Copyright 2019 Fafnir
*/

#ifndef INCLUDE_TEXTBOX_H_
#define INCLUDE_TEXTBOX_H_
#include <string>
#include <vector>
#include "Exceptions.h"

class TextBox {
 public:
  TextBox(int x, int y, int w, int h);
  virtual ~TextBox();

  int posX;
  int posY;
  int width;
  int height;
  char getAt(int x, int y);
  void fillChar(char c);
  void fillTopDown(std::string text);
  void fillBottomUp(std::string text);
  void fillTopDown(std::vector<std::string> lines);
  void fillBottomUp(std::vector<std::string> lines);

 private:
  std::vector<std::string> content;
};

#endif  // INCLUDE_TEXTBOX_H_
