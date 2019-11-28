/*
*Copyright 2019 Fafnir
*/

#ifndef INCLUDE_CHATOPTION_H_
#define INCLUDE_CHATOPTION_H_
#include "ChatType.h"
#include <string>


class ChatOption {
 public:
  /**
  * A chat option
  * @param titl The option.
  * @param rep The reply to that option.
  * @param tp The chat type, riddle or regular chat.
  * @param id The id of the next chat option, reply to this option.
  */
  ChatOption(std::string titl, std::string rep, ChatType tp, int id);

  /**
  * Destructor for chat option
  */
  virtual ~ChatOption();

  /**
  * The option.
  */
  std::string title;

  /**
  * The reply to the option .
  */
  std::string reply;

  /**
  * Id to next chat option.
  */
  int nextChatId;

  /**
  * Whether chat is a riddle or just chat.
  */
  ChatType type;
};

#endif  // INCLUDE_CHATOPTION_H_

