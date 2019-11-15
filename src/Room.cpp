#include "Room.h"

Room::Room(int roomId, std::string desc) {
  description = desc;
  id = roomId;
}

std::string Room::getDescription() {
  std::stringstream ss;

  ss << description << std::endl;
  //ss << "There are " << items.size() << " items in the room." << std::endl;

  if (items.size() > 0) {
    ss << "item size: " << items.size() << std::endl;
    ss << "You find the following items on the ground: " << std::endl;
    //TODO: Better sentence for multiple items
    for (int i = 0; i < items.size(); i++) {
        ss << items[i].name << std::endl;
    }
   // ss << std::endl;
  }

  ss << "There are " << npcs.size() << " NPCS in the room." << std::endl;

  return ss.str();
}

std::string Room::getDescriptionOnly() {
  return description;
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

std::vector<Item> Room::getItems()
{
  return items;
}

void Room::removeAllItems()
{
  items.clear();
}

bool Room::tryKey(Item i)
{
  if(i.type == Key && i.value == id) {
    locked = false;
    return true;
  }
  return false;
}

Room::Room(int roomId) {
  id = roomId;
}

std::vector<std::string> Room::getItemList()
{
    std::vector<std::string> retVec;
    for(Item i : items) {
      retVec.push_back(i.name);
    }
    return retVec;
}

std::vector<std::string> Room::getNPCList()
{
    std::vector<std::string> retVec;
    for(NPC n : npcs) {
      retVec.push_back(n.getName());
    }
    return retVec;
}

std::vector<NPC> Room::getNPCs()
{
    return npcs;
}


int Room::getId()
{
    return id;
}

Room::~Room() {
  //dtor
}
