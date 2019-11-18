#ifndef CHATGROUP_H
#define CHATGROUP_H
#include <string>
#include <vector>
#include "ChatOption.h"

class ChatGroup {
 public:
  ChatGroup( std::vector<ChatOption> chtop);
  virtual ~ChatGroup();
  std::vector<ChatOption> chats;
  int cid;
  int npcid;

 protected:

 private:
};

#endif // CHATGROUP_H
