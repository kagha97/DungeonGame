#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H
#include <string>
#include <map>
#include "Item.h"
//Controls
const char UP = 'U';
const char DOWN = 'D';
const char LEFT = 'L';
const char RIGHT = 'R';
const char NEWGAME = 'N';
const char LOADGAME = 'L';

//Other room options
const char PICK = 'P';


const int ROOMCOUNT = 25;

//TODO: Move these to external text file. Possibly in json format.
const std::string ROOMDESC[ROOMCOUNT] = {
  "You are at the dungeon's entrance. The exit has been closed behind you.",
  "This room is completely blank and devoid of detail. The only things you can see are the doors along its walls.",
  "As you look around the room you see that the walls are painted with pictures of ducks. You feel a strange urge to tell the walls all of your problems, but you manage to restrain yourself."
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
const int LOCKED[KEYCOUNT] = {5, 12, 20, 24};

// Map containing our items and their locations
const std::map<Item, int> ITEMS = {
  {Item(101, "Rusty Key", Key, 5), 23},
  {Item(102, "Iron Key", Key, 24), 5},
  {Item(103, "Shiny Key", Key, 20), 24},
  {Item(104, "Gold Key", Key, 12), 20}
};


#endif // GAMECONSTANTS_H
