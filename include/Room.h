#ifndef ROOM_H
#define ROOM_H

#include <string>


class Room
{
  public:
    Room();
    Room(std::string desc);
    std::string getDescription();
    void setDescription(std::string desc);
    virtual ~Room();

  protected:

  private:
    std::string description;
};

#endif // ROOM_H
