#ifndef PROJECT_CHATROOMFACTORYI_HPP
#define PROJECT_CHATROOMFACTORYI_HPP

#include <Ice/Ice.h>
#include <chat.h>

class ChatRoomFactoryI : public Chat::ChatRoomFactory
{
    public:
        Chat::ChatRoomPrx createChatRoom(const std::string &name, const Ice::Current &current) override;
        Ice::Int numOfChatroomsRunning(const Ice::Current &current) override;

    private:
        Chat::ChatServerPrx chatServerPrx;
        Ice::Int numOfChatRoomsRunning;
};

#endif //PROJECT_CHATROOMFACTORYI_HPP
