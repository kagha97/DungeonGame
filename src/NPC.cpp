#include "NPC.h"

NPC::NPC(std::string n,std::string exm, int cid){
  name = n;
  examine = exm;
  chatid = cid;
}






//std::string NPC::getName() {
//  return name;
//}

bool NPC::operator==(const NPC& n) const
{
    return name == n.name && hostile == n.hostile;
}

NPC::~NPC()
{
  //dtor
}
