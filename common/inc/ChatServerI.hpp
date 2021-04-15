#ifndef PROJECT_CHATSERVERI_HPP
#define PROJECT_CHATSERVERI_HPP

#include <Ice/Ice.h>
#include <chat.h>

class ChatServerI : public Chat::ChatServer {
    public:
        Chat::ChatRoomList getRooms(const Ice::Current &current) override;
        Chat::ChatRoomPrx createChatRoom(const std::string &name, const Ice::Current &current) override;
        void registerChatRoomFactory(const Chat::ChatRoomFactoryPrx &factory, const Ice::Current &current) override;
        void unregisterChatRoomFactory(const Chat::ChatRoomFactoryPrx &factory, const Ice::Current &current) override;
        void registerUser(const Chat::ChatUserPrx &who, const Ice::Current &current) override;
        void unregisterUser(const Chat::ChatUserPrx &who, const Ice::Current &current) override;

    private:
            Chat::ChatRoomList roomList;
            Chat::UserList registeredUserList;
            std::vector<Chat::ChatRoomFactoryPrx> roomFactoryList;

};

#endif //PROJECT_CHATSERVERI_HPP
