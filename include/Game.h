#ifndef GAME_H
#define GAME_H
#include <vector>
#include <string>
#include "Room.h"
#include "Player.h"
#include "GameConstants.h"

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

    virtual ~Game();

  protected:

  private:
    std::vector<Room> rooms;
};

#endif // GAME_H
