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
const char INVENTORY = 'I';

//Inventory Commands
const char USE = 'U';
const char DROP = 'D';
const char EXAMINE = 'E';
const char EXIT = 'X';

//Other room options
const char PICK = 'P';


const int ROOMCOUNT = 25;
const int MAXHEALTH = 99;
const int MAXHUNGER = 99;


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

// Map containing our items and their locations
const std::map<Item, int> ITEMS = {
  {Item(101, "Rusty Key", Key, 5), 23},
  {Item(102, "Iron Key", Key, 24), 5},
  {Item(103, "Shiny Key", Key, 20), 24},
  {Item(104, "Gold Key", Key, 12), 20},

  {Item(201, "Red Potion", Potion, 15), 2},
  {Item(202, "Suspicious Potion", Potion, -10), 2},


  {Item(301, "Burger", Food, 25), 2},
  {Item(302, "Spider", Food, 3), 2},
  {Item(303, "Shark Fin Pizza", Food, 50), 2},
  {Item(304, "Rotten Apple", Food, -10), 2},
  {Item(305, "Duck", Food, 100), 2}

};


#endif // GAMECONSTANTS_H
