#ifndef GAME_H
#define GAME_H
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include "Room.h"
#include "Player.h"
#include "GameConstants.h"
#include "Exceptions.h"
#include "GameState.h"
#include "ActionRecord.h"
#include "StringManipulations.h"

class Game
{
  public:
    Game(int roomCount);
    Game(std::string filePath);
    void save(std::string filePath);
    void getInput(std::istream& inStr);
    void show_ascii(std::string loc);
    void drawChatOptions(int id);
    void drawChatMenu (int id);
    void solveRiddle (std::string inp);
    Player player;
    std::string getRoomDescription(int r);
    std::string examineNPC (int id);
    State state;
    virtual ~Game();
    std::vector<std::string> miniMap();
    std::vector<std::string> getRoomItemNames();
    std::vector<std::string> getNpcOptions(int id, int width);
    std::vector<std::string> getRoomNPCNames();
    int currentChat;
    int nextChat;
  protected:

  private:

    int currentChatNpc;

    void movePlayer(char dir);
    void lootRoom();
    void drawNpcList(std::ostream& os);
    void drawNpcSubMenu(std::ostream& os);
    std::vector<Room> rooms;
};

#endif // GAME_H
