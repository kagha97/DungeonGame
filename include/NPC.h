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
  /**
   * NPC
   * @param n Name of npc.
   * @param exm Examine text of npc.
   * @param cid Chat id of npc, starting chat.
   */
  NPC(std::string n, std::string exm, int cid);

  /**
   * Not implemented
   */
  bool hostile;

  /**
   * Deconstructor for npc
   */
  virtual ~NPC();

  /**
   * Chad id
   */
  int chatid;

  /**
   * Comparing NPC
   * @return true if npc is same as one being compared to
   */
  bool operator==(const NPC& n) const;

  /**
   * NPC Examine
   */
  std::string examine;

  /**
   * Name of NPC
   */
  std::string name;

 private:
   /**
   * Not implemented
   */
  int health = 100;
};

#endif  // INCLUDE_NPC_H_
