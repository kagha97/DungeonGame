#ifndef GAME_H
#define GAME_H
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include "Room.h"
#include "Player.h"
#include "GameConstants.h"
#include "Exceptions.h"

class Game
{
  public:
    Game(int roomCount);
    Game(std::string filePath);
    Player player;
    void draw(std::ostream& os);
    void movePlayer(char dir);
    void otherRoomOptions (char op);
    std::string getOptionsString();
    void inventoryScreen();
    virtual ~Game();

  protected:

  private:
    std::vector<Room> rooms;
};

#endif // GAME_H
