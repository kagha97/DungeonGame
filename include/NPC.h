/*
*Copyright 2019 Fafnir
*/

#ifndef INCLUDE_NPC_H_
#define INCLUDE_NPC_H_
#include <vector>
#include <string>
#include <sstream>
#include "Item.h"


class NPC {
 public:
  NPC(std::string n, std::string exm, int cid);
  bool hostile;
  virtual ~NPC();
  int chatid;
  bool operator==(const NPC& n) const;
  std::string examine;
  std::string name;

 private:
  int health = 100;
};

#endif  // INCLUDE_NPC_H_
