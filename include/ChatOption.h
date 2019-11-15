#ifndef CHATOPTION_H
#define CHATOPTION_H
#include <string>


class ChatOption
{
    public:
        ChatOption(std::string titl, std::string rep, int id);
        virtual ~ChatOption();
        std::string title;
        std::string reply;
        int nextChatId;

    protected:

    private:

};

#endif // CHATOPTION_H
