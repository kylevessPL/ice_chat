#ifndef PROJECT_CLIENT_HPP
#define PROJECT_CLIENT_HPP

#include <Ice/Application.h>
#include <memory>

class Client : public Ice::Application
{
    public:
        int run(int argc, char **argv) override;
    private:
        Ice::ObjectAdapterPtr adapterPtr;
        Chat::ChatUserPrx userPrx;
        Chat::ChatServerPrx serverPrx;
        Chat::ChatRoomPrx chatRoomPrx;
        Ice::ObjectAdapterPtr getAdapter(int portMin, int portMax);
        void registerUsername();
        void listen();
        void showHelp();
        void leaveRoom();
        void joinRoom(std::string &name);
        void createRoom(std::string &name);
        void sendPrivateMessage(std::string &username, std::string &message);
        void sendMessage(std::string &message);
        void showRoomList();
        void showUserList();
        std::vector<std::string> tokenize(std::string &command);

};

#endif //PROJECT_CLIENT_HPP
