/*
*Copyright 2019 Fafnir
*/

#include "Game.h"
#include <vector>
#include <string>

Game::Game(std::string filePath) {
  std::ifstream in(filePath);
  std::string str;
  std::vector<std::string> data;
  while (std::getline(in, str)) {
    data.push_back(str);
  }
  in.close();
  player = Player(data[0]);
  for (int i = 1 ; i < data.size(); i++) {
    rooms.push_back(Room(data[i]));
  }
  state = Play;
}

void Game::save(std::string filePath) {
  std::vector<Item> pInv = player.getInventory();
  std::vector<int> compRid = player.getCompletedRiddles();
  std::ofstream out;
  out.open(filePath);
  out <<  "{" << player.getHP() << ATTRIBDELIM << player.getHunger() <<
      ATTRIBDELIM << player.getCurrentRoom() << ATTRIBDELIM << "{";
  if (pInv.size() < 1) {
    out << EMPTY;
  }
  for (int i = 0; i < pInv.size(); i++) {
    for (auto const& mI : ITEMS) {
      if (pInv[i] == mI.second) {
        out << mI.first;
        if (i < pInv.size() - 1) {
          out << OBJDELIM;
        }
        break;
      }
    }
  }
  out << "},{";
  if (compRid.size() < 1) {
    out << EMPTY;
  }
  for (int i = 0; i < compRid.size(); i++) {
    out << compRid[i];
    if (i < compRid.size() - 1) {
      out << OBJDELIM;
    }
  }

  out << "}}" << std::endl;
  for (Room r : rooms) {
    out << "{" << r.getId()
        << ATTRIBDELIM << static_cast<int>(r.locked) << ATTRIBDELIM << "{";
    std::vector<Item> rItems = r.getItems();
    if (rItems.size() < 1) {
      out << EMPTY;
    }
    for (int i = 0; i < rItems.size(); i++) {
      for (auto const& I : ITEMS) {
        if (rItems[i] == I.second) {
          out << I.first;
          if (i < rItems.size() - 1) {
            out << OBJDELIM;
          }
          break;
        }
      }
    }
    out << "}" << ATTRIBDELIM;
    out << "{";
    std::vector<NPC> rNPCs = r.getNPCS();
    if (rNPCs.size() < 1) {
      out << EMPTY;
    }
    for (int i = 0; i < rNPCs.size(); i++) {
      for (auto const& N : NPCS) {
        if (rNPCs[i] == N.second) {
          out << N.first;
          if (i < rNPCs.size() - 1) {
            out << OBJDELIM;
          }
          break;
        }
      }
    }
    out << "}" << ATTRIBDELIM << r.visited;
    out << "}}" << std::endl;
  }
  out.close();
  ActionRecord::addRecord("Game saved as " + filePath);
}

Game::Game(int roomCount) {
  double sr = sqrt(roomCount);
  if ((sr - floor(sr)) != 0) {
    throw room_count_not_square_error("The number of rooms "
                                      "must be a square number");
  }
  if (roomCount > 25) {
    throw room_count_too_large_error("Cannot have more than 25 rooms");
  }

  state = Play;

  // Create rooms
  for (int i = 0; i < roomCount; i++) {
    Room newRoom(i, ROOMDESC[i]);
    rooms.push_back(newRoom);
  }


  for (auto const& x : ITEMLOCATIONS) {
    for (int i : x.second) {
      if (i < rooms.size()) {
        rooms[i].addItem(ITEMS.at(x.first));
      }
    }
    /*if (ITEMS.find(x.first)->second.type == Key) {
      // If the item is a key, lock the room corresponding to its value
      int roomIndex = ITEMS.find(x.first)->second.value;
      std::cout << "locked: " << roomIndex << std::endl;
      if (roomIndex < rooms.size()) {
        rooms[roomIndex].locked = true;
      }
    } */
  }

  //  lock rooms
  for (int id : LOCKEDROOMS) {
    for (int i = 0; i < rooms.size(); i++) {
      if (id == i) {
        rooms[id].locked = true;
      }
    }
  }

  // add npc to room
  for (auto const& x : NPCLOCATIONS) {
    for (int i : x.second) {
      if (i < rooms.size()) {
        rooms[i].addNPC(NPCS.at(x.first));
      }
    }
  }
}

void Game::getInput(std::istream& inStr) {
  int inInt = 0;
  char inChar = ' ';
  std::string inString = "";

  // Determine input style based on game state
  switch (state) {
  case MainMenu:
  case Play:
  case Inventory:
  case Pause:
  case NPCList:
    inStr >> inChar;
    inChar = std::toupper(inChar);
    break;
  case Save:
  case Load:
  case RiddleTalk:
    inStr >> inString;
    break;
  // Most inputs require int.
  default:
    inStr >> inInt;
    std::cout << inInt <<std::endl;
    break;
  }

  // Change state and call methods based on input
  switch (state) {
  case MainMenu:
  case Play:
    // Handle inputs while playing
    handleInputPlay(inChar);
    break;
  case Inventory:
    // Handle inputs while in inventory
    handleInputInventory(inChar);
    // end
    break;
  case ItemUse:
    player.consumeItem(inInt - 1);
    state = Inventory;
    break;
  case ItemDrop:
    player.dropItem(inInt - 1, &rooms[player.getCurrentRoom()]);
    state = Inventory;
    break;
  case ItemExamine:
    player.examineItem(inInt - 1);
    state = Inventory;
    break;
  case Pause:
    // Handle inputs while in "Pause" menu
    handleInputPause(inChar);
    break;
  case Save: {
    char s = std::toupper(inString[0]);
    if (s != EXIT) {
      if (!(StringManipulations::hasEnding(inString, FILEEXT))) {
        inString += FILEEXT;
      }
      save(inString);
    }
    state = Pause;
  }
  break;

  case NPCList:
    // Handle inputs while in NPCList menu
    handleInputNPCMenu(inChar);
    break;
  case TalkNPC:
    {
      if (rooms[player.getCurrentRoom()].getNPCS().size() >= inInt) {
        currentChatNpc = inInt;
        currentChat = inInt;
        state = Talk;
      } else {
        ActionRecord::addRecord("That is not an option.");
      }
    }
    break;
  case ExamineNPC:
    {
      if (rooms[player.getCurrentRoom()].getNPCS().size() >= inInt) {
        state = NPCList;
        ActionRecord::addRecord(examineNPC(inInt));
      } else {
        ActionRecord::addRecord("That is not an option.");
      }
    }
    break;
  case Talk:
    nextChat = inInt;
    state = TalkSecond;
    break;
  case TalkSecond:
    nextChat = inInt;
    state = TalkSecond;
    break;
  case RiddleTalk:
    std::cout << inString;
    solveRiddle(inString);
    state = Play;
    break;
  default:
    ActionRecord::addRecord("Unrecognized command.");
    break;
  }
  inStr.clear();
}

void Game::handleInputPlay(char inChar) {
  switch (inChar) {
  case INVENTORY:
    if (player.getInventory().size() > 0) {
      state = Inventory;
      ActionRecord::addRecord("You open your inventory.");
    } else {
      ActionRecord::addRecord("Your inventory is empty.");
    }
    break;
  case UP:
  case DOWN:
  case LEFT:
  case RIGHT:
    movePlayer(inChar);
    break;
  case PICK:
    lootRoom();
    break;
  case EXIT:
    state = Pause;
    break;
  case NPCVIEW: {
    if (rooms[player.getCurrentRoom()].getNPCS().size() > 0) {
      state = NPCList;
      ActionRecord::addRecord("The NPCS in this room.");
    } else {
      ActionRecord::addRecord("There are no NPCS in this room.");
    }
  }
  break;
  default:
    ActionRecord::addRecord("Unrecognized command.");
    break;
  }
}

void Game::handleInputInventory(char inChar) {
  switch (inChar) {
  case USE:
    state = ItemUse;
    break;
  case DROP:
    state = ItemDrop;
    break;
  case EXAMINE:
    state = ItemExamine;
    break;
  case EXIT:
    state = Play;
    ActionRecord::addRecord("You close your inventory.");
    break;
  default:
    ActionRecord::addRecord("Unrecognized command.");
    break;
  }
}

void Game::handleInputPause(char inChar) {
  switch (inChar) {
  case EXIT:
    state = Play;
    break;
  case QUIT:
    std::cout << std::endl;
    exit(0);
    break;
  case SAVE:
    state = Save;
    break;
  }
}

void Game::handleInputNPCMenu(char inChar) {
  switch (inChar) {
  case TALK:
    state = TalkNPC;
    break;
  case EXMNPC:
    state = ExamineNPC;
    break;
  case EXIT:
    state = Play;
    ActionRecord::addRecord("You are out of the NPC screen.");
    break;
  }
}


void Game::movePlayer(char dir) {
  int moveInt = 0;
  int currentRoom = player.getCurrentRoom();
  int mapWidth = sqrt(rooms.size());
  bool moved = false;
  std::string dirString;
  switch (std::toupper(dir)) {
  case UP :
    if (currentRoom < mapWidth) {
      ActionRecord::addRecord("You cannot go that way.");
      break;
    }
    dirString = "north";
    moveInt = -mapWidth;
    moved = true;
    break;
  case DOWN :
    if (currentRoom + mapWidth >= rooms.size()) {
      ActionRecord::addRecord("You cannot go that way.");
      break;
    }
    dirString = "south";
    moveInt = mapWidth;
    moved = true;
    break;
  case LEFT :
    if (currentRoom % mapWidth == 0) {
      ActionRecord::addRecord("You cannot go that way.");
      break;
    }
    dirString = "west";
    moveInt = -1;
    moved = true;
    break;
  case RIGHT :
    if ((currentRoom + 1) % mapWidth == 0) {
      ActionRecord::addRecord("You cannot go that way.");
      break;
    }
    dirString = "east";
    moveInt = 1;
    moved = true;
    break;
  default:
    ActionRecord::addRecord("Unrecognized command.");
    return;
  }
  if (moved) {
    int roomIndex = currentRoom + moveInt;

    if (rooms[roomIndex].locked) {
      for (Item it : player.getInventory()) {
        if (rooms[roomIndex].tryKey(it)) {
          ActionRecord::addRecord("You use " +
                                  it.name + " to unlock the room.");
          player.removeItem(it);
        }
      }
    }
    if (!rooms[roomIndex].locked) {
      player.moveTo(roomIndex);
      rooms[roomIndex].visited = true;
      ActionRecord::addRecord("You move " + dirString + ".");
    } else {
      rooms[roomIndex].visited = true;
      ActionRecord::addRecord("That room is locked");
    }
  }
  if (player.getCurrentRoom() == WINRAR) {
    state = Win;
  }
}

// NPC STUFF
std::string Game::examineNPC(int id) {
  int currentRoom = player.getCurrentRoom();
  return rooms[currentRoom].getNPCS()[id - 1].examine;
}

void Game::solveRiddle(std::string inp) {
  int currentRoom = player.getCurrentRoom();
  std::string npc = rooms[currentRoom].getNPCS()[currentChatNpc - 1].name;
  std::cout << nextChat << std::endl;
  std::cout << "input: " << inp << std::endl;
  if (inp == RANS.at(RIDDLEANSWERS.at(nextChat))) {
    if (!player.checkRiddle(nextChat)) {
      ActionRecord::addRecord("You got the right answer! " +npc +
                              " rewards you, check your inventory.");
      player.finishRiddle(nextChat);
      for (int id : REWARDS.at(nextChat)) {
        player.addItem(ITEMS.at(id));
      }
      state = Play;
    } else {
      ActionRecord::addRecord("You already solved this "
                              "riddle and received the rewards..");
      state = Play;
    }
  } else {
    ActionRecord::addRecord("You got the wrong answer. Speak to " + npc +
                            " to try again.");
    state = TalkSecond;
  }
}
//  END NPC

void Game::lootRoom() {
  int currentRoom = player.getCurrentRoom();
  std::vector<Item> items = rooms[currentRoom].getItems();
  if (items.size() > 0) {
    for (int i = 0; i < items.size(); i++) {
      player.addItem(items[i]);
    }
    rooms[currentRoom].removeAllItems();
    ActionRecord::addRecord("You loot the room.");
  }
}

void Game::show_ascii(std::string loc) {
  std::ifstream open(loc);
  std::string out;
  if (open.is_open()) {
    while (open.eof() == false) {
      getline(open, out);
      std::cout << out << std::endl;
    }
  }
}

std::vector<std::string> Game::miniMap() {
  int roomCount = rooms.size();
  int s = sqrt(roomCount);
  std::vector<std::string> outVec;
  int currentRoom = player.getCurrentRoom();
  int tempCounter = 0;
  std::stringstream ss;
  for (int h = 0; h < s; h++) {
    for (int w = 0; w < s; w++) {
      if (currentRoom == tempCounter) {
        ss << "[*]";
      } else if (rooms[tempCounter].locked && rooms[tempCounter].visited) {
        ss << "[#]";
      } else {
        ss << "[ ]";
      }
      tempCounter++;
    }
    outVec.push_back(ss.str());
    ss.str("");
  }
  return outVec;
}

std::string Game::getRoomDescription(int r) {
  return rooms[r].getDescriptionOnly();
}

std::vector<std::string> Game::getRoomItemNames() {
  return rooms[player.getCurrentRoom()].getItemList();
}

std::vector<std::string> Game::getRoomNPCNames() {
  return rooms[player.getCurrentRoom()].getNPCList();
}

std::vector<std::string> Game::getNpcOptions(int id, int width) {
  int currentRoom = player.getCurrentRoom();

  std::vector<std::string> outVec;

  // std::cout << "current chat: " << currentChat <<
  //  " Next chat: " << nextChat<<
  //   ". Entered id: " << id << ". State is: " << state << std::endl;

  if (id == 0) {
    state = Play;
  } else {
    // input validation
    /* if (id <= rooms[currentRoom].getNPCS()[id - 1].chatid) {
         std::cout << "no" << std::endl;
     }
     else if (id > id <= rooms[currentRoom].getNPCS()[id - 1].chatid){
         std::cout << "yes" << std::endl;
     } */

    int counter = 0;
    std::string npc = rooms[currentRoom].getNPCS()[currentChatNpc - 1].name;
    outVec.push_back("You are speaking with: " + npc);
    int cid = 0;
    switch (state) {
    case Talk:
      cid = rooms[currentRoom].getNPCS()[id - 1].chatid;
      currentChat = cid;
      for (auto const& x : chats.at(cid)) {
        counter++;
        outVec.push_back(std::to_string(counter) + ". " + x.second.title);
      }
      state = TalkSecond;
      break;
    case TalkSecond:
      switch (chats.at(currentChat).at(id).type) {
      case Riddle: {
        state = RiddleTalk;
        nextChat = chats.at(currentChat).at(id).nextChatId;

        int tStart = 0;
        int tLen = width;
        std::string riddle = npc + " replies: "
                             + chats.at(currentChat).at(id).reply;
        while (tStart + tLen < riddle.length()) {
          outVec.push_back(riddle.substr(tStart, tLen));
          tStart += tLen;
        }
        outVec.push_back(riddle.substr(tStart, riddle.length() - tStart));
      }
      break;

      case Chat: {
        int tStart = 0;
        int tLen = width;
        std::string reply = npc +
                            " replies: " + chats.at(currentChat).at(id).reply;
        while (tStart + tLen < reply.length()) {
          outVec.push_back(reply.substr(tStart, tLen));
          tStart += tLen;
        }
        outVec.push_back(reply.substr(tStart, reply.length() - tStart));
        int nchat = chats.at(currentChat).at(id).nextChatId;
        // end chat
        if (nchat == 0) {
          state = Play;
          outVec.push_back("Press any key to continue...");
        } else {
          currentChat = nchat;

          for (auto const& x : chats.at(currentChat)) {
            counter++;
            outVec.push_back(std::to_string(counter) + ". " + x.second.title);
          }
        }
      }
      }
      break;
    }
  }
  return outVec;
}

Game::~Game() {
}
