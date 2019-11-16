#include "Game.h"

void Game::draw(std::ostream& os) {
  int cr = player.getCurrentRoom();
  switch (GlobalState) {
  case Play:
    drawPlay(os);
    os << rooms[cr].getDescription() << std::endl;
    os << ActionRecord::getRecords() << std::endl;
    break;
  case Inventory:
    drawInventory(os);
    os << ActionRecord::getLatest() << std::endl;
    break;
  case ItemUse:
  case ItemDrop:
  case ItemExamine:
    drawInventorySubMenu(os);
    break;
  case NPCList:
    drawNpcList(os);
    os << ActionRecord::getLatest() << std::endl;
    break;
  case TalkNPC:
  case ExamineNPC:
    drawNpcSubMenu(os);
    break;
  case Talk:
    drawChatMenu(currentChat);
    break;
  case TalkSecond:
  case RiddleTalk:
    drawChatMenu(nextChat);
  default:
    break;
  }
  os << std::endl;
  os << "Enter Option: ";
}

void Game::drawPlay(std::ostream& os) {
  int roomCount = rooms.size();
  if (roomCount < 1)
    return;
  int currentRoom = player.getCurrentRoom();
  //ActionRecord::addRecord(rooms[currentRoom].getDescription());

  int tmpNewLine = 0;
  for (int i = 0; i < roomCount; i++) {
    if (currentRoom == i) {
      os << '[' << "P" << ']';
    } else {
      os << '[' << " " << ']';
    }
    tmpNewLine++;
    if (tmpNewLine == sqrt(roomCount)) {
      os << std::endl;
      tmpNewLine=0;
    }
  }
  os << getOptionsString() << std::endl;
  os << player.getStatsString() << std::endl;
}

void Game::drawInventory(std::ostream& os) {
  os << player.showInventory() << std::endl;
  char opt = ' ';
  int number = -1;
  os << "Enter " << USE << " to use an item, " << EXAMINE <<
     " to examine the item, and " << DROP << " to drop an item." << std::endl;
}

void Game::drawInventorySubMenu(std::ostream& os) {
  drawInventory(os);
  switch (GlobalState) {
  case ItemUse:
    os << "Which item do you want to use?" << std::endl;
    break;
  case ItemDrop:
    os << "Which item do you want to drop?" << std::endl;
    break;
  case ItemExamine:
    os << "Which item do you want to examine?" << std::endl;
    break;
  }
}

std::string Game::getOptionsString() {
  std::stringstream ss;

  ss << "Enter " << UP << " , " << DOWN << " , " << LEFT << " , " << RIGHT <<
     " to move north, south, west, or east." << std::endl;
  ss << "Enter " << PICK << " to pick up items in the room, if there are any." <<
     std::endl;
  ss << "Enter " << NPCVIEW << " to see list of NPCS in the room." <<
     std::endl;

  return ss.str();
}


Game::Game(std::string filePath) {

}

Game::Game(int roomCount) {
  double sr = sqrt(roomCount);
  if ((sr - floor(sr)) != 0) {
    throw room_count_not_square_error("The number of rooms must be a square number");
  }
  if (roomCount > 25) {
    throw room_count_too_large_error("Cannot have more than 25 rooms");
  }

  GlobalState = Play;

  // Create rooms
  for (int i = 0; i < roomCount; i++) {

    Room newRoom(i, ROOMDESC[i]);
    rooms.push_back(newRoom);

  }


  for (auto const& x : ITEMLOCATIONS) {
    for (int i : x.second) {
      rooms[i].addItem(ITEMS.at(x.first));
    }
    if (ITEMS.find(x.first)->second.type == Key) {
      //If the item is a key, lock the room corresponding to its value
      rooms[ITEMS.find(x.first)->second.value].locked = true;
    }
  }

  //add npc to room
  for (auto const& x : NPCLOCATIONS) {
    for (int i : x.second) {
      rooms[i].addNPC(NPCS.at(x.first));
    }
  }

}

void Game::getInput(std::istream& inStr) {
  int inInt = 0;
  char inChar = ' ';
  std::string inString = "";

  switch (GlobalState) {
  case MainMenu:
  case Play:
  case Inventory:
    inStr >> inChar;
    inChar = std::toupper(inChar);
    break;
  case ItemUse:
  case ItemDrop:
  case ItemExamine:
    inStr >> inInt;
    break;
  case NPCList:
    inStr >> inChar;
    inChar = std::toupper(inChar);
    break;
  case TalkNPC:
  case Talk:
  case TalkSecond:
  case ExamineNPC:
    inStr >> inInt;
    break;
  case RiddleTalk:
   //inStr >> inChar;
   break;
  }

  switch (GlobalState) {
  case MainMenu:
  case Play:
    switch (inChar) {
    case INVENTORY:
      GlobalState = Inventory;
      ActionRecord::addRecord("You open your inventory.");
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
    case NPCVIEW:
        GlobalState = NPCList;
        ActionRecord::addRecord("The NPCS in this room.");
        break;
    }
    break;
  case Inventory:
    switch (inChar) {
    case USE:
      GlobalState = ItemUse;
      break;
    case DROP:
      GlobalState = ItemDrop;
      break;
    case EXAMINE:
      GlobalState = ItemExamine;
      break;
    case EXIT:
      GlobalState = Play;
      ActionRecord::addRecord("You close your inventory.");
      break;
    }
    break;
  case ItemUse:
    player.consumeItem(inInt - 1);
    GlobalState = Inventory;
    break;
  case ItemDrop:
    player.dropItem(inInt - 1, &rooms[player.getCurrentRoom()]);
    GlobalState = Inventory;
    break;
  case ItemExamine:
    player.examineItem(inInt - 1);
    GlobalState = Inventory;
    break;

  case NPCList:
    switch (inChar) {
      case TALK:
       GlobalState = TalkNPC;
        break;
      case EXMNPC:
       GlobalState = ExamineNPC;
        break;
      case EXIT:
      GlobalState = Play;
      ActionRecord::addRecord("You are out of the NPC screen.");
      break;
    }
    break;
    case TalkNPC:
        currentChatNpc = inInt;
        currentChat = inInt;
        GlobalState = Talk;
        break;
    case ExamineNPC:
        GlobalState = NPCList;
        break;
    case Talk:
    nextChat = inInt;
        drawChatMenu(currentChat);
        GlobalState = TalkSecond;
        break;
    case TalkSecond:
      nextChat = inInt;
      // drawChatMenu(inInt);

       GlobalState = TalkSecond;
       break;
    case RiddleTalk:
        inStr >> inString;
      // std::getline(inStr, inString);
       solveRiddle(inString);
       GlobalState = Play;
       break;
  }

  inStr.clear();
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
    if (currentRoom + mapWidth >= rooms.size() ) {
      ActionRecord::addRecord("You cannot go that way.");
      break;
    }
    dirString = "south";
    moveInt = mapWidth;
    moved = true;
    break;
  case LEFT :
    if (currentRoom % mapWidth == 0 ) {
      ActionRecord::addRecord("You cannot go that way.");
      break;
    }
    dirString = "west";
    moveInt = -1;
    moved = true;
    break;
  case RIGHT :
    if ((currentRoom + 1) % mapWidth == 0 ) {
      ActionRecord::addRecord("You cannot go that way.");
      break;
    }
    dirString = "east";
    moveInt = 1;
    moved = true;
    break;
  default :
    return;
    //break;
  }
  if (moved) {
    int roomIndex = currentRoom + moveInt;

    if (rooms[roomIndex].locked) {
      for (Item it : player.getInventory()) {
        if (rooms[roomIndex].tryKey(it)) {
          ActionRecord::addRecord("You use " + it.name + " to unlock the room.");
          player.removeItem(it);
        }
      }
    }
    if (!rooms[roomIndex].locked) {
      player.moveTo(roomIndex);
      ActionRecord::addRecord("You move " + dirString + ".");
    } else {
      ActionRecord::addRecord("That room is locked");
    }
  }
  player.updateValues();
}

//NPC STUFF

void Game::drawNpcList(std::ostream& os) {
  int currentRoom = player.getCurrentRoom();
  os << rooms[currentRoom].showNPCS() << std::endl;
  char opt = ' ';
  int number = -1;
  os << "Enter " << TALK << " to talk to an NPC, " << EXMNPC <<
     " to examine an NPC." << std::endl;
}


void Game::drawNpcSubMenu(std::ostream& os) {
  drawNpcList(os);
  switch (GlobalState) {
  case TalkNPC:
    os << "Which NPC do you want to talk to?" << std::endl;
    break;
  case ExamineNPC:
    os << "Which NPC do you want to examine?" << std::endl;
    break;
  }
}


void Game::drawChatMenu(int id) {
  drawChatOptions(id);
  switch (GlobalState) {
  case TalkNPC:
    std::cout << "Which NPC do you want to talk to?" << std::endl;
    break;
  case ExamineNPC:
    std::cout << "Which NPC do you want to examine?" << std::endl;
    break;
  }

}


void Game::drawChatOptions(int id) {

  int currentRoom = player.getCurrentRoom();
//  os << rooms[currentRoom].getNPCS()[id - 1] << std::endl;
  int counter = 0;

  if (id == 0) {
    GlobalState = Play;
  } else {
   std::string npc = rooms[currentRoom].getNPCS()[currentChatNpc - 1].name;
  std::cout << "You are speaking with: " << npc << std::endl;
    int cid = 0;
  switch (GlobalState) {
  case Talk:
   cid = rooms[currentRoom].getNPCS()[id - 1].chatid;

    for (auto const& x : chats.at(cid)) {
            counter++;
            std::cout << counter << ". " << x.second.title << std::endl;
            //os << i+1 << ". " << c.title << std::endl;
        }
    break;
  case TalkSecond:

    switch (chats.at(currentChat).at(id).type) {

        case Riddle:
            GlobalState = RiddleTalk;
             nextChat = chats.at(currentChat).at(id).nextChatId;
             std::cout << npc << " replies: " << chats.at(currentChat).at(id).reply << std::endl;
            break;

        case Chat:
    std::cout << npc << " replies: " << chats.at(currentChat).at(id).reply << std::endl;
    int nchat = chats.at(currentChat).at(id).nextChatId;
    currentChat = nchat;

    //counter = 0;
    for (auto const& x : chats.at(currentChat)) {
            counter++;
            std::cout << counter << ". " << x.second.title << std::endl;
            //os << i+1 << ". " << c.title << std::endl;
        }


    }
    break;
  }
  }

    std::cout << "Please choose an option. Enter 0 to end chat. " << std::endl;
}


void Game::solveRiddle(std::string inp)
{
    int currentRoom = player.getCurrentRoom();
    std::string npc = rooms[currentRoom].getNPCS()[currentChatNpc - 1].name;
    std::cout << nextChat << std::endl;
    std::cout << "input: " << inp << std::endl;
    if (inp == RANS.at(RIDDLEANSWERS.at(nextChat))) {

        if (!player.checkRiddle(nextChat)) {
        ActionRecord::addRecord("You got the right answer! " +npc + " rewards you, check your inventory.");
        player.finishRiddle(nextChat);
        for (int id : REWARDS.at(nextChat)) {
            player.addItem(ITEMS.at(id));
        }
        GlobalState = Play;
        } else {
         ActionRecord::addRecord("You already solved this riddle and recieved the rewards..");
        GlobalState = Play;
        }
    }

    else {
            ActionRecord::addRecord("You got the wrong answer. Speak to " + npc + " to try again.");
            GlobalState = TalkSecond;
    }
}



//END NPC




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

Game::~Game() {

}
