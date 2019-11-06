#include "Room.h"
#include <string>
#include <sstream>

Room::Room(std::string desc)
{
  description = desc;
}

std::string Room::getDescription()
{
  std::stringstream ss;

  ss << description << std::endl;
  ss << "There are " << items.size() << " items in the room." << std::endl;
  ss << "There are " << npcs.size() << " NPCS in the room." << std::endl;

  return ss.str();
}
void Room::addNPC(NPC npc)
{
  npcs.push_back(npc);
}

void Room::addItem(Item item)
{
  items.push_back(item);
}

void Room::interact(int npcIndex)
{

}

void Room::pickUpItem(int itemIndex)
{

}

void Room::setDescription(std::string desc)
{
  description = desc;
}

Room::Room()
{
  //ctor
}

Room::~Room()
{
  //dtor
}
