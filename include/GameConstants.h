#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H
#include <string>

//Controls
const char UP = 'U';
const char DOWN = 'D';
const char LEFT = 'L';
const char RIGHT = 'R';
const char NEWGAME = 'N';
const char LOADGAME = 'L';


const int ROOMCOUNT = 25;
const std::string ROOMDESC[ROOMCOUNT] = {
  "You are at the dungeon's entrance. The exit has been closed behind you.",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  ""
};

const int KEYCOUNT = 4;
// Decide which rooms to lock
const int LOCKED[KEYCOUNT] = {5, 12, 20, 25};
// Keys to unlock rooms
// Room 5 first, then 25 and 20. 12 is in the centre of the map, so it'll be the last room.
const Item KEYS[KEYCOUNT] = {
  Item("Rusty Key", Key, 5),
  Item("Iron Key", Key, 25),
  Item("Shiny Key", Key, 20),
  Item("Gold Key", Key, 12)
};
const int KEYLOCATIONS[KEYCOUNT] = {23, 5, 25, 20};

#endif // GAMECONSTANTS_H
