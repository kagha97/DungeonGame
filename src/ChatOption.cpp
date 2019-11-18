/*
*Copyright 2019 Fafnir
*/

#include "ChatOption.h"
#include <string>

ChatOption::~ChatOption() {
}
ChatOption::ChatOption(std::string titl, std::string rep, ChatType tp, int id) {
  title = titl;
  reply = rep;
  nextChatId = id;
  type = tp;
}
