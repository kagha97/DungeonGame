#include "TextBox.h"

TextBox::TextBox(int x, int y, int w, int h) {
  posX = x;
  posY = y;
  width = w;
  height = h;
  std::string s(w, ' ');
  for (int i =0; i < h; i++) {
    content.push_back(s);
  }
}

TextBox::~TextBox() {

}

char TextBox::getAt(int x, int y) {
  if (content.size() > y) {
    if (content[y].length() > x) {
      return content[y][x];
    }
  }
  return ' ';
}

void TextBox::fillTopDown(std::string text) {
  int pos = 0;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (pos < text.length()) {
        content[y][x] = text[pos++];
      }
    }
  }
}

void TextBox::fillBottomUp(std::string text) {
  int pos = 0;
  for (int y = height - 1; y > 0; y--) {
    for (int x = 0; x < width; x++) {
      if (pos < text.length()) {
        content[y][x] = text[pos++];
      }
    }
  }
}

void TextBox::fillTopDown(std::vector<std::string>lines) {
  for (int y = 0; y < height; y++) {
    if (y < lines.size()) {
      content[y] = lines[y];
    }
  }
}

void TextBox::fillBottomUp(std::vector<std::string>lines) {
  int pos = 0;
  for (int y = height - 1; y > 0; y--) {
    if (pos < lines.size()) {
      content[y] = lines[pos++];
    }
  }
}

void TextBox::fillChar(char c)
{
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
        content[y][x] = c;
    }
  }
}
void TextBox::shrink()
{

}


