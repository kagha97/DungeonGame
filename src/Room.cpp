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

Room::Room()
{
  //ctor
}

Room::~Room()
{
  //dtor
}
