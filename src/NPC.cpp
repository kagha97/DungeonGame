#include "NPC.h"

NPC::NPC(std::string n,std::string exm, int cid){
  name = n;
  examine = exm;
  chatid = cid;
}






NPC::~NPC()
{
  //dtor
}
