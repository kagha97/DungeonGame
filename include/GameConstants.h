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

//Menu Commands
const char SAVE = 'S';
const char QUIT = 'Q';

//Other room options
const char PICK = 'P';
const char NPCINTERACT = 'T';


const int ROOMCOUNT = 25;
const int MAXHEALTH = 99;
const int MAXHUNGER = 99;
const int HUNGERGAIN = 5;
const int HEALTHLOSS = 10;

// Action Record
const int MAXRECORDS = 10;

// Window Constants
const int WINDOWWIDTH = 90;
const int WINDOWHEIGHT = 35;


// Save file parameters
const char ATTRIBDELIM = ',';
const char OBJDELIM = ';';
const std::string EMPTY = "NULL";
const std::string FILEEXT = ".save";
const std::string AUTOSAVEFILE = "auto" + FILEEXT;

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

// Map containing game items with ID
const std::map<int, Item> ITEMS = {
  //Keys
  {100, Item("Rusty Key", "I wonder if this will unlock a door.", Key, 5)},
  {101, Item("Iron Key", "I should try eating this.", Key, 24)},
  {102, Item("Shiny Key", "I wonder if this will unlock a door.", Key, 20)},
  {103, Item("Gold Key", "I wonder what this tastes like.", Key, 12)},

  //Potions
  {200, Item("Red Potion", "heals health.", Potion, 15)},
  {201, Item("Suspicious Potion", "hmm I should try drinking this.", Potion, -10)},

  //Food
  {300, Item("Burger", "A yummy burger I just found in a dungeon. Sounds good.", Food, 25)},
  {301, Item("Spider", "Looks tasty.", Food, 3)},
  {302, Item("Shark Fin Pizza", "Pizza with Shark Fin", Food, 50)},
  {303, Item("Rotten Apple", "Smells gross. I should eat it.", Food, -10)},
  {304, Item("Duck", "This is duck.", Food, 100)}

};

//Map containing item locations
const std::map<int, std::vector<int>> ITEMLOCATIONS = {
  {100, {23}},
  {101, {5}},
  {102, {24}},
  {103, {20}},

  {200,{2}},
  {201,{2}},

  {300,{2}},
  {301,{2}},
  {302,{2}},
  {303,{2}},
  {304,{2}}
};


// Map containing NPCs with ID
const std::map<int, NPC> NPCS = {
  {100, NPC("Wise Old Man")}
};

// Map containing NPC locations
const std::map<int, std::vector<int>> NPCLOCATIONS = {
  {100, {2}}
};


#endif // GAMECONSTANTS_H
