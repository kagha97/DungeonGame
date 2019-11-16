#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H
#include <string>
#include <map>
#include "NPC.h"
#include "Item.h"
#include "ChatOption.h"
#include <vector>
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


//NPC Interaction Commands
const char TALK = 'T';
const char EXMNPC = 'E';



//Other room options
const char PICK = 'P';
const char NPCVIEW = 'T';


const int ROOMCOUNT = 25;
const int MAXHEALTH = 99;
const int MAXHUNGER = 99;
const int HUNGERGAIN = 5;
const int HEALTHLOSS = 10;

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
  {100, NPC("Wise Old Man", 1)}
};

// Map containing NPC locations
const std::map<int, std::vector<int>> NPCLOCATIONS = {
  {100, {0}}
};


//Chat
const std::map <int, std::string> CHATOPTIONS = {
    //wise old man
    {10000, "How are you?"},
    {10001, "What is this place?"},
    {10002, "Ask about riddle..."},
    {10003, "Okay, let me try."},
    {10004, "I give up."},
    {10005, "No thanks."}


};


const std::map <int, std::string> CHATREPLIES = {
    //wise old man
    {10000, "I am good, thank you for asking."},
    {10001, "It's a dungeon full of rooms, you must find keys to unlock these rooms. One of the rooms contains the exit. Good luck!"},
    {10002, "If you solve this riddle for me, I will give you a key to one of the rooms."},
    //riddle
    {10003, "What is 10 + 10?"},
    {10004, "Coward."},



};


const std::map <int, int> RIDDLEANSWERS = {
    {3, 1},


};

const std::map <int, std::string> RANS = {
    {1, "20"}

};

const std::map <int, std::vector<int>> REWARDS = {
    {3, {100, 200}}

};


const std::map <int, std::map <int, ChatOption>> chats = {
    {1, {{1,
        ChatOption(CHATOPTIONS.at(10000), CHATREPLIES.at(10000), Chat, 1)},
        {2,
        ChatOption(CHATOPTIONS.at(10001), CHATREPLIES.at(10001), Chat, 1)},
        {3,
        ChatOption(CHATOPTIONS.at(10002), CHATREPLIES.at(10002), Chat, 2)}
    }},
     {2, {{1,
        ChatOption(CHATOPTIONS.at(10003), CHATREPLIES.at(10003), Riddle, 3 )},
        {2,
        ChatOption(CHATOPTIONS.at(10005), CHATREPLIES.at(10004), Chat, 1 )}
    }

    },
     {3, {{1,
        ChatOption(CHATOPTIONS.at(10004), CHATREPLIES.at(10004), Chat, 1)}
    }},

};


#endif // GAMECONSTANTS_H
