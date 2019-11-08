#include "NPC.h"

NPC::NPC(int npcID, std::string n){
  name = n;
  id = npcID;
}

void NPC::addItem(Item i)
{
  inventory.push_back(i);
}

NPC::~NPC()
{
  //dtor
}
