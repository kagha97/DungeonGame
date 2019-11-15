#include "ChatOption.h"


ChatOption::~ChatOption()
{
    //dtor
}
ChatOption::ChatOption(std::string titl, std::string rep, int id)
{
    title = titl;
    reply = rep;
    nextChatId = id;
}
