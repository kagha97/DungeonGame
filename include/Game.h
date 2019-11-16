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

class Game
{
  public:
    Game(int roomCount);
    Game(std::string filePath);
    void save(std::string filePath);
    Player player;
    void draw(std::ostream& os);
    void getInput(std::istream& inStr);
    void show_ascii(std::string loc);
    std::string getOptionsString();
    std::string getRoomDescription(int r);
    void inventoryScreen();
    State state;
    virtual ~Game();
    std::vector<std::string> miniMap();
  protected:

  private:
    void movePlayer(char dir);
    void lootRoom();
    void drawPlay(std::ostream& os);
    void drawInventory(std::ostream& os);
    void drawInventorySubMenu(std::ostream& os);
    std::vector<Room> rooms;
};

#endif // GAME_H
