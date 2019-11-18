#include "ChatOption.h"


ChatOption::~ChatOption() {
  //dtor
}
ChatOption::ChatOption(std::string titl, std::string rep, ChatType tp, int id) {
  title = titl;
  reply = rep;
  nextChatId = id;
  type = tp;
}
