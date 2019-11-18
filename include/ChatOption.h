/*
*Copyright 2019 Fafnir
*/

#ifndef INCLUDE_CHATOPTION_H_
#define INCLUDE_CHATOPTION_H_
#include "ChatType.h"
#include <string>


class ChatOption {
 public:
  ChatOption(std::string titl, std::string rep, ChatType tp, int id);
  virtual ~ChatOption();
  std::string title;
  std::string reply;
  int nextChatId;
  ChatType type;

 private:
};

#endif  // INCLUDE_CHATOPTION_H_

