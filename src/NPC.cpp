/*
*Copyright 2019 Fafnir
*/

#include "NPC.h"
#include <string>

NPC::NPC(std::string n, std::string exm, int cid) {
  name = n;
  examine = exm;
  chatid = cid;
}

bool NPC::operator==(const NPC& n) const {
  return name == n.name && hostile == n.hostile;
}

NPC::~NPC() {
}
