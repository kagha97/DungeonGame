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
    /**
   * Textbox
   * @param x position of tb
   * @param y positon
   * @param w width
   * @param h height
   */
  TextBox(int x, int y, int w, int h);

   /**
   * Deconstructor
   */
  virtual ~TextBox();

   /**
   * position x
   */
  int posX;

   /**
   * position y
   */
  int posY;

   /**
   * width
   */
  int width;

   /**
   * height
   */
  int height;

   /**
   * text at postion
   * @param x of text
   * @param y of text
   */
  char getAt(int x, int y);

  void fillChar(char c);
  void fillTopDown(std::string text);
  void fillBottomUp(std::string text);
  void fillTopDown(std::vector<std::string> lines);
  void fillBottomUp(std::vector<std::string> lines);
  void shrink();

 private:
  std::vector<std::string> content;
};

#endif  // INCLUDE_TEXTBOX_H_
