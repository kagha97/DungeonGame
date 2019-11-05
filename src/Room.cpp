#include "Room.h"
#include <string>

Room::Room(std::string desc)
{
  description = desc;
}

std::string Room::getDescription()
{
  return description;
}

void Room::setDescription(std::string desc)
{
  description = desc;
}

void Room::addConnection(Room* r)
{
  for (Room* ptr : doors) {
    if(ptr == r) {
        //TODO: Throw exception
      return;
    }
  }
  doors.push_back(r);
}


Room::Room()
{
  //ctor
}

Room::~Room()
{
  //dtor
}
