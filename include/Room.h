#ifndef ROOM_H
#define ROOM_H

#include <string>


class Room
{
  public:
    Room();
    Room(const std::string desc);
    std::string getDescription();
    std::string setDescription();
    virtual ~Room();

  protected:

  private:
    std::string description;
};

#endif // ROOM_H
