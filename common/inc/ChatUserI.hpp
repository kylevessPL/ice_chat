#ifndef PROJECT_CHATUSERI_HPP
#define PROJECT_CHATUSERI_HPP

#include <Ice/Ice.h>
#include <chat.h>

class ChatUserI : public Chat::ChatUser
{
    public:
        explicit ChatUserI(const std::string& name);
        void sendMessage(const Chat::ChatUserPrx &from, const std::string &message, const Ice::Current &current) override;
        std::string getName(const Ice::Current &current) override;
        void sendPrivateMessage(const Chat::ChatUserPrx &from, const std::string &message, const Ice::Current &current) override;

    private:
        std::string name;

};

#endif //PROJECT_CHATUSERI_HPP
