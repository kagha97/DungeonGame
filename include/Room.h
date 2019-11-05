#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <string>


class Room
{
  public:
    Room();
    Room(std::string desc);
    std::string getDescription();
    std::vector<Room*> doors;
    void setDescription(std::string desc);
    void addConnection(Room* r);

    bool locked;

    virtual ~Room();

  protected:

  private:
    std::string description;
};

#endif // ROOM_H
