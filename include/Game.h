#ifndef GAME_H
#define GAME_H
#include <vector>
#include <string>
#include "Room.h"
#include "Player.h"

class Game
{
  public:
    Game(int roomCount);
    Game(std::string filePath);
    int currentRoom;
    static Player player;
    void draw(std::ostream& os);
    void movePlayer(char dir);
    virtual ~Game();

  protected:

  private:
    std::vector<Room> rooms;
    std::vector<std::vector<int>> roomLinks;
};

#endif // GAME_H
