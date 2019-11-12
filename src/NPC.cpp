#include "NPC.h"

NPC::NPC(std::string n){
  name = n;
}

void NPC::addItem(Item i)
{
  inventory.push_back(i);
}

std::string NPC::getName() {
  return name;
}

NPC::~NPC()
{
  //dtor
}
