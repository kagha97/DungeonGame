/*
*Copyright 2019 Fafnir
*/

#ifndef INCLUDE_GAMECONSTANTS_H_
#define INCLUDE_GAMECONSTANTS_H_
#include "NPC.h"
#include "Item.h"
#include "ChatOption.h"
#include <string>
#include <map>
#include <vector>
// Controls
const char UP = 'U';
const char DOWN = 'D';
const char LEFT = 'L';
const char RIGHT = 'R';
const char NEWGAME = 'N';
const char LOADGAME = 'L';
const char INVENTORY = 'I';

const int WINRAR = 12;

// Inventory Commands
const char USE = 'U';
const char DROP = 'D';
const char EXAMINE = 'E';
const char EXIT = 'X';


// NPC Interaction Commands
const char TALK = 'T';
const char EXMNPC = 'E';

// Menu Commands
const char SAVE = 'S';
const char QUIT = 'Q';

// Other room options
const char PICK = 'P';
const char NPCVIEW = 'T';


const int ROOMCOUNT = 25;
const int MAXHEALTH = 99;
const int MAXHUNGER = 99;
const int HUNGERGAIN = 5;
const int HEALTHLOSS = 10;

// Action Record
const int MAXRECORDS = 10;

// Window Constants
const int WINDOWWIDTH = 100;
const int WINDOWHEIGHT = 35;


// Save file parameters
const char ATTRIBDELIM = ',';
const char OBJDELIM = ';';
const char EMPTY[] = "NULL";
const char FILEEXT[] = ".fafnir";
// const char AUTOSAVEFILE[] = "auto" + FILEEXT;

const std::vector<std::string> ROOMDESC = {
  "You are at the dungeon's entrance. The exit has been closed behind you.",
  "This room is completely blank and devoid of detail. "
  "The only things you can see are the doors along its walls.",
  "As you look around the room you see that the "
  "walls are painted with pictures of ducks. "
  "You feel a strange urge to tell the walls all of your "
  "problems, but you manage to restrain yourself.",
  "",
  "",
  "",
  "",
  "From the room to your south you feel a slight breeze. "
  "Could that be the way out?",
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

//  Vector with locked room ids
const std::vector<int> LOCKEDROOMS = {5, 9, 12, 20, 24};

// Map containing game items with ID
const std::map<int, Item> ITEMS = {
  // Keys
  {100, Item("Rusty Key", "I wonder if this will unlock a door.", Key, 12)},
  {101, Item("Iron Key", "I should try eating this.", Key, 24)},
  {102, Item("Shiny Key", "I wonder if this will unlock a door.", Key, 20)},
  {103, Item("Gold Key", "I wonder what this tastes like.", Key, 9)},
  {104, Item("Brass Key", "Unlocks a room.", Key, 5)},

  // Potions
  {200, Item("Red Potion", "heals health.", Potion, 15)},
  {
    201, Item("Suspicious Potion",
    "hmm I should try drinking this.", Potion, -10)
  },

  // Food
  {
    300, Item("Burger",
    "A yummy burger I just found in a dungeon."
    "Sounds good.", Food, 25)
  },
  {301, Item("Spider", "Looks tasty.", Food, 3)},
  {302, Item("Shark Fin Pizza", "Pizza with Shark Fin", Food, 50)},
  {303, Item("Rotten Apple", "Smells gross. I should eat it.", Food, -10)},
  {304, Item("Duck", "This is duck.", Food, 100)},

  //  Collectables
  {400, Item("Gold bar", "It's a bar of gold.", Loot, 100)},
  {401, Item("Gold necklace", "I wonder if this is valuable.", Loot, 100)},
};

// Map containing item locations
const std::map<int, std::vector<int>> ITEMLOCATIONS = {
  {200, {2}},
  {201, {2}},
  {300, {2}},
  {301, {2}},
  {302, {2}},
  {303, {2}},
  {304, {2}},
  {401, {0, 17, 24}}
};

// Map containing NPCs with ID
const std::map<int, NPC> NPCS = {
  {100, NPC("Wise Old Man", "A venerable sage.", 1)},
  {200, NPC("Maggie", "A young witch.", 4)},
  {300, NPC("Gertrude", "A busy housewife.", 7)},
  {400, NPC("Fluffs", "A friendly feline?", 10)},
  {500, NPC("Mysterious Old Man", "A very strange old man.", 12)},
  {600, NPC{"Sherlock", "Master of all clues.", 14}}
};

// Map containing NPC locations
const std::map<int, std::vector<int>> NPCLOCATIONS = {
  {100, {0}},
  {200, {24}},
  {300, {20}},
  {400, {14}},
  {500, {9}},
  {600, {5}}
};


// Chat
const std::map <int, std::string> CHATOPTIONS = {
  // wise old man
  {10000, "How are you?"},
  {10001, "What is this place?"},
  {10002, "Ask about riddle..."},
  {10003, "Okay, let me try."},
  {10004, "I give up."},
  {10005, "No thanks."},

  // Maggie
  {20000, "Hi."},
  {20001, "Bye."},
  {20002, "Give me a random fact."},
  {20003, "Do you have anything for me?"},

  // Gertrude
  {30000, "Hello."},
  {30001, "You don't look so happy."},

  // Fluffs
  {40000, "Hello kitty."},

  // Mystrious Old Man
  {50000, "Hello."},

  // Sherlock
  {60000, "Greetings."}
};

const std::map <int, std::string> CHATREPLIES = {
  // wise old man
  {10000, "I am good, thank you for asking."},
  {
    10001, "It's a dungeon full of rooms, you must find keys "
    "to unlock these rooms. One of the rooms contains the exit. Good luck!"
  },
  {
    10002, "If you solve this riddle for me, "
    "I will give you a key to one of the rooms."
  },
  // riddle
  {10003, "What is 10 + 10?"},
  {10004, "Coward."},

  // Maggie
  {20000, "Hello, what can I do for you, this fine day, cha?"},
  {20001, "Goodbye, and good luck!"},
  {
    20002, "Banging your head against a wall for "
    "one hour burns 150 calories, Don'tcha know."
  },
  {
    20003, "If you solve this riddle for me cha, "
    "I will give a key to one of the rooms."
  },
  {20004, "Aww."},
  {
    20005, "I am the part of the bird that is not in the sky, "
    "who can drown in the ocean and yet remain dry."
    "A last vestige of man that refuses to die. In mourning I "
    "am tossed at your feet to lie; I begin my job early, "
    "devouring your ankles and thighs."
    "I work my way up, eating your legs to your waist."
    "And though around midday away I am chased, I return "
    "quickly to savor the arm of my taste."
    "As evening falls I enter your lungs, spiraling "
    "down past your mouth and your tongue. I feast "
    "on your body, your soul, and your mind,"
    "but as darkness falls you shall find that away I will"
    " go, a relief for some; At least until "
    "tomorrow morning comes. What is 2000 - 3?"
  },

  // Gertrude
  {30000, "Good day."},
  {30001, "I've lost my beloved cat, can you help me find her please?"},
  {30002, "Thank you! Her name is Fluffs and she ran off to one of the rooms "
  "in the dungeon. Would you be a dear and tell me the number of the room she "
  " is in? Hint: You are in room 21."},

  //  Fluffs
  {40000, "Meow."},

  //  Mysterious Old Man
  {50000, "Hey, would you like to solve this riddle for me? I'll reward you"
  " with a key to one of the rooms."},
  {50001, "People buy me to eat, but never eat me. What am I?"},
  {50002, "Your loss."},

  //  Sherlock
  {60000, "I've got a puzzle, if you solve it I'll reward you."},
  {60001, "3 rooms in this dungeon contain Gold necklaces, what is the sum"
  " of the room numbers of these rooms?"},
  {60002, "Come back to me if you want to try again."}
};

//  Riddle chat id, and riddle answer (RANS) id
const std::map <int, int> RIDDLEANSWERS = {
  {3, 1},
  {6, 2},
  {9, 3},
  {13, 4},
  {16, 5}
};

const std::map <int, std::string> RANS = {
  {1, "20"},
  {2, "1997"},
  {3, "15"},
  {4, "plate"},
  {5, "42"}
};

const std::map <int, std::vector<int>> REWARDS = {
  {3, {101, 200}},
  {6, {102, 200}},
  {9, {103, 400}},
  {13, {104}},
  {16, {100}}
};

const std::map <int, std::map <int, ChatOption>> chats = {
  // wise old man chat
  {
    1, {{
        1,
        ChatOption(CHATOPTIONS.at(10000), CHATREPLIES.at(10000), Chat, 1)
      },
      {
        2,
        ChatOption(CHATOPTIONS.at(10001), CHATREPLIES.at(10001), Chat, 1)
      },
      {
        3,
        ChatOption(CHATOPTIONS.at(10002), CHATREPLIES.at(10002), Chat, 2)
      }
    }
  },
  {
    2, {{
        1,
        ChatOption(CHATOPTIONS.at(10003), CHATREPLIES.at(10003), Riddle, 3 )
      },
      {
        2,
        ChatOption(CHATOPTIONS.at(10005), CHATREPLIES.at(10004), Chat, 1 )
      }
    }
  },
  {
    3, {{
        1,
        ChatOption(CHATOPTIONS.at(10004), CHATREPLIES.at(10004), Chat, 1)
      }
    }
  },
  // Maggie chat
  {
    4, {{
        1,
        ChatOption(CHATOPTIONS.at(20000), CHATREPLIES.at(20000), Chat, 4)
      },
      {
        2,
        ChatOption(CHATOPTIONS.at(20001), CHATREPLIES.at(20001), Chat, 0)
      },
      {
        3,
        ChatOption(CHATOPTIONS.at(20002), CHATREPLIES.at(20002), Chat, 4)
      },
      {
        4,
        ChatOption(CHATOPTIONS.at(20003), CHATREPLIES.at(20003), Chat, 5)
      },
    }
  },
  {
    5, {{
        1,
        ChatOption(CHATOPTIONS.at(10003), CHATREPLIES.at(20005), Riddle, 6 )
      },
      {
        2,
        ChatOption(CHATOPTIONS.at(10005), CHATREPLIES.at(20004), Chat, 4 )
      }
    }
  },
  {
    6, {{
        1,
        ChatOption(CHATOPTIONS.at(10004), CHATREPLIES.at(10004), Chat, 4)
      }
    }
  },
  // Gertrude chat
  {
    7, {{
        1,
        ChatOption(CHATOPTIONS.at(30000), CHATREPLIES.at(30000), Chat, 7)
      },
      {
        2,
        ChatOption(CHATOPTIONS.at(30001), CHATREPLIES.at(30001), Chat, 8)
      },
    }
  },
  {
    8, {{
        1,
        ChatOption(CHATOPTIONS.at(10003), CHATREPLIES.at(30002), Riddle, 9)
      },
      {
        2,
        ChatOption(CHATOPTIONS.at(10005), CHATREPLIES.at(30001), Chat, 0)
      },
    }
  },
  {
    9, {{
        1,
        ChatOption(CHATOPTIONS.at(10004), CHATREPLIES.at(10004), Chat, 7)
      }
    }
  },
  {
    10, {{
        1,
        ChatOption(CHATOPTIONS.at(40000), CHATREPLIES.at(40000), Chat, 10)
      }
    }
  },
  //  Mysterious Old Man
  {
    11, {{
        1,
        ChatOption(CHATOPTIONS.at(50000), CHATREPLIES.at(50000), Chat, 12)
      }
    }
  },
  {
    12, {{
        1,
        ChatOption(CHATOPTIONS.at(10003), CHATREPLIES.at(50001), Riddle, 13)
      },
      {
        2,
        ChatOption(CHATOPTIONS.at(10005), CHATREPLIES.at(50002), Chat, 11)
      },
    }
  },
  {
    13, {{
        1,
        ChatOption(CHATOPTIONS.at(10004), CHATREPLIES.at(10004), Chat, 11)
      }
    }
  },
  //  Sherlock
  {
    14, {{
        1,
        ChatOption(CHATOPTIONS.at(60000), CHATREPLIES.at(60000), Chat, 15)
      }
    }
  },
  {
    15, {{
        1,
        ChatOption(CHATOPTIONS.at(10003), CHATREPLIES.at(60001), Riddle, 16)
      },
      {
        2,
        ChatOption(CHATOPTIONS.at(10005), CHATREPLIES.at(60002), Chat, 14)
      },
    }
  },
  {
    16, {{
        1,
        ChatOption(CHATOPTIONS.at(10004), CHATREPLIES.at(10004), Chat, 14)
      }
    }
  }
};

#endif  // INCLUDE_GAMECONSTANTS_H_
