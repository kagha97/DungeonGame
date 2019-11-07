#include "Room.h"
#include <string>
#include <sstream>

Room::Room(std::string desc) {
  description = desc;
}

std::string Room::getDescription() {
  std::stringstream ss;

  ss << description << std::endl;
  //ss << "There are " << items.size() << " items in the room." << std::endl;

  if (items.size() > 0) {
    ss << "Lying in the middle of the room, there is ";
    //TODO: Better sentence for multiple items
    for (int i = 0; i < items.size(); i++) {
      ss << "a " << items[i].name;
    }
    ss << std::endl;
  }

  ss << "There are " << npcs.size() << " NPCS in the room." << std::endl;

  return ss.str();
}
void Room::addNPC(NPC npc) {
  npcs.push_back(npc);
}

void Room::addItem(Item item) {
  items.push_back(item);
}

void Room::interact(int npcIndex) {

}

void Room::pickUpItem(int itemIndex) {

}

void Room::setDescription(std::string desc) {
  description = desc;
}

Room::Room() {
  //ctor
}

Room::~Room() {
  //dtor
}
