#ifndef NPC_H
#define NPC_H
#include <vector>
#include <string>
#include <sstream>
#include "Item.h"


class NPC
{
  public:
    NPC(std::string n, std::string exm, int cid);
    bool hostile;
    virtual ~NPC();
    int chatid;
    std::string examine;
    std::string name;


  protected:

  private:
    int health = 100;
};

#endif // NPC_H
