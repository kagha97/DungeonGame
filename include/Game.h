#ifndef GAME_H
#define GAME_H

#include "Room.h"

class Game
{
  public:
    Game();
    virtual ~Game();

  protected:

  private:
    Room rooms[];
    int** roomLinks;
};

#endif // GAME_H
