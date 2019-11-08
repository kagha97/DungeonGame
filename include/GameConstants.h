#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H
#include <string>
#include <map>
#include "Item.h"
#include "NPC.h"
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
const char NPCINTERACT = 'T';


const int ROOMCOUNT = 25;
const int MAXHEALTH = 99;
const int MAXHUNGER = 99;

// Action Record
const int MAXRECORDS = 5;

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
const std::map<Item, std::vector<int>> ITEMS = {
  //Keys
  {Item(100, "Rusty Key", "I wonder if this will unlock a door.", Key, 5), {23}},
  {Item(101, "Iron Key", "I should try eating this.", Key, 24), {5}},
  {Item(102, "Shiny Key", "I wonder if this will unlock a door.", Key, 20), {24}},
  {Item(103, "Gold Key", "I wonder what this tastes like.", Key, 12), {20}},

  //Potions
  {Item(200, "Red Potion", "heals health.", Potion, 15), {2}},
  {Item(201, "Suspicious Potion", "hmm I should try drinking this.", Potion, -10), {2}},

  //Food
  {Item(300, "Burger", "A yummy burger I just found in a dungeon. Sounds good.", Food, 25), {2}},
  {Item(301, "Spider", "Looks tasty.", Food, 3), {2}},
  {Item(302, "Shark Fin Pizza", "Pizza with Shark Fin", Food, 50), {2}},
  {Item(303, "Rotten Apple", "Smells gross. I should eat it.", Food, -10), {2}},
  {Item(304, "Duck", "This is duck.", Food, 100), {2}}

};


// Map containing our NPCs and their locations
const std::map<NPC, std::vector<int>> NPCS = {
  {NPC(100, "Wise Old Man"), {2}}
};




#endif // GAMECONSTANTS_H
