#ifndef CHATOPTION_H
#define CHATOPTION_H
#include "ChatType.h"
#include <string>


class ChatOption
{
    public:
        ChatOption(std::string titl, std::string rep, ChatType tp, int id);
        virtual ~ChatOption();
        std::string title;
        std::string reply;
        int nextChatId;
        ChatType type;


    protected:

    private:

};

#endif // CHATOPTION_H
