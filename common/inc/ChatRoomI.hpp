#ifndef PROJECT_CHATROOMI_HPP
#define PROJECT_CHATROOMI_HPP

#include <Ice/Ice.h>
#include <chat.h>

class ChatRoomI : public Chat::ChatRoom
{
    public:
        ChatRoomI(const std::string& name);
        void sendMessage(const Chat::ChatUserPrx &from, const std::string &message, const Ice::Current &current) override;
        void addUser(const Chat::ChatUserPrx &who, const Ice::Current &current) override;
        void removeUser(const Chat::ChatUserPrx &who, const Ice::Current &current) override;
        Chat::UserList getUsers(const Ice::Current &current) override;
        std::string getName(const Ice::Current &current) override;

    private:
        std::string name;
        Chat::UserList userList;

};

#endif //PROJECT_CHATROOMI_HPP
