#include <chat.h>
#include <client.hpp>
#include <characters_not_allowed_exception.hpp>
#include <ChatServerI.hpp>
#include <ConnectionUtil.h>
#include <ChatUserI.hpp>
#include <regex>

int Client::run(int argc, char **argv)
{
    Ice::PropertiesPtr properties = communicator()->getProperties();
    int serverPort = properties->getPropertyAsIntWithDefault("server.port.set", 49152);
    Ice::ObjectPrx proxy = communicator()->stringToProxy("server:default -p " + std::to_string(serverPort));
    this->serverPrx = serverPrx.uncheckedCast(proxy);
    int portMin = properties->getPropertyAsIntWithDefault("client.port.range.min", 55555);
    int portMax= properties->getPropertyAsIntWithDefault("client.port.range.max", 65535);
    this->adapterPtr = getAdapter(portMin, portMax);
    this->adapterPtr->activate();
    registerUsername();
    listen();
    if (this->chatRoomPrx != ICE_NULLPTR)
    {
        this->chatRoomPrx->removeUser(this->userPrx);
    }
    this->serverPrx->unregisterUser(this->userPrx);
    communicator()->shutdown();
    communicator()->waitForShutdown();
    return EXIT_SUCCESS;
}

Ice::ObjectAdapterPtr Client::getAdapter(int portMin, int portMax)
{
    while (true)
    {
        int port = ConnectionUtil::getRandomPort(portMin, portMax);
        try
        {
            Ice::ObjectAdapterPtr ptr = communicator()->createObjectAdapterWithEndpoints(
                    "client_adapter",
                    "default -p " + std::to_string(port));
            return ptr;
        }
        catch (Ice::SocketException ex)
        {
            continue;
        }
    }
}

void Client::registerUsername()
{
    std::string username;
    std::cout << "Please choose your username" << std::endl;
    for(;;)
    {
        try
        {
            std::cout << "Username: ";
            std::getline(std::cin, username);
            if (!regex_match(username, std::regex("^[a-zA-Z0-9]+$")))
            {
                throw CharactersNotAllowedException("Username can contain only letters or digits");
            }
            Chat::ChatUserPtr userPtr = new ChatUserI(username);
            this->userPrx = userPrx.uncheckedCast(adapterPtr->addWithUUID(userPtr));
            this->serverPrx->registerUser(this->userPrx);
            return;
        }
        catch (CharactersNotAllowedException ex)
        {
            std::cerr << ex.what() << std::endl;
            continue;
        }
        catch (Chat::UsernameAlreadyRegisteredException ex)
        {
            std::cerr << "Username not available, please choose another one" << std::endl;
            this->adapterPtr->remove(this->userPrx->ice_getIdentity());
            continue;
        }
    }
}

void Client::listen()
{
    std::cout << "Type /help to see list of available commands" << std::endl;
    for(;;)
    {
        std::string command;
        getline(std::cin, command);
        std::vector<std::string> tokenList = tokenize(command);
        command = tokenList.at(0);
        if (command == "/help")
        {
            showHelp();
        }
        else if (command == "/rooms")
        {
            showRoomList();
        }
        else if (command == "/users")
        {
            showUserList();
        }
        else if (command == "/leave")
        {
            leaveRoom();
        }
        else if (command == "/join")
        {
            joinRoom(tokenList[1]);
        }
        else if (command == "/create")
        {
            createRoom(tokenList[1]);
        }
        else if (command == "/msgprv")
        {
            std::vector<std::string> args = tokenize(tokenList[1]);
            sendPrivateMessage(args[0], args[1]);
        }
        else if (command == "/msg")
        {
            sendMessage(tokenList[1]);
        }
        else if (command == "/quit")
        {
            break;
        }
        else
        {
            std::cout << "Unknown command" << std::endl;
        }
    }
}

std::vector<std::string> Client::tokenize(std::string &command)
{
    command = std::regex_replace(command, std::regex("^ +| +$|( ) +"), "$1");
    std::vector<std::string> tokenList(2);
    int pos = command.find(" ");
    tokenList[0] = command.substr(0, pos);
    if (pos != std::string::npos)
    {
        tokenList[1] = command.substr(pos + 1);
    }
    return tokenList;
}

void Client::showHelp()
{
    std::cout << "List of available commands:" << std::endl;
    std::cout << "/join <RoomName> - joins chat room" << std::endl;
    std::cout << "/leave - leaves current chat room" << std::endl;
    std::cout << "/rooms - lists available chat rooms" << std::endl;
    std::cout << "/create <RoomName> - creates chat room" << std::endl;
    std::cout << "/users - lists all users in chat room" << std::endl;
    std::cout << "/msg <message> - sends message to everyone in chat room" << std::endl;
    std::cout << "/msgprv <user> <message> - sends private message to specific user in chat room" << std::endl;
    std::cout << "/help - lists available commands" << std::endl;
    std::cout << "/quit - disconnects and exits application" << std::endl;
}

void Client::leaveRoom()
{
    if (this->chatRoomPrx == ICE_NULLPTR)
    {
        std::cerr << "You ain't connected to any chat room" << std::endl;
        return;
    }
    std::string name = this->chatRoomPrx->getName();
    this->chatRoomPrx->removeUser(this->userPrx);
    this->chatRoomPrx = ICE_NULLPTR;
    std::cout << "You've left chat room " << name << std::endl;
}

void Client::joinRoom(std::string &name)
{
    if (name.empty())
    {
        std::cerr << "Chat room name not specified" << std::endl;
        return;
    }
    if (this->chatRoomPrx != ICE_NULLPTR && this->chatRoomPrx->getName() == name)
    {
        std::cerr << "You are already connected to this chat room" << std::endl;
        return;
    }
    Chat::ChatRoomList roomList = serverPrx->getRooms();
    for (auto it = std::begin(roomList); it != std::end(roomList); ++it)
    {
        Chat::ChatRoomPrx room = *it;
        if (room->getName() == name)
        {
            room->addUser(this->userPrx);
            this->chatRoomPrx = room;
            std::cout << "You joined chat room " << name << std::endl;
            return;
        }
    }
    std::cerr << "Chat room " << name << " not found" << std::endl;
}

void Client::createRoom(std::string &name)
{
    if (name.empty())
    {
        std::cerr << "Chat room name not specified" << std::endl;
        return;
    }
    try
    {
        this->serverPrx->createChatRoom(name);
        std::cout << "Chat room " << name << " created, join using /join " << name << " command" << std::endl;
    }
    catch (Chat::NoRoomFactoryAvailableException ex)
    {
        std::cerr << "No room factories available at the moment, please try again later" << std::endl;
    }
    catch (Chat::RoomNameAlreadyRegisteredException ex)
    {
        std::cerr << "Chat room with this name already exists, please choose another one" << std::endl;
    }
}

void Client::sendPrivateMessage(std::string &username, std::string &message)
{
    if (this->chatRoomPrx == ICE_NULLPTR)
    {
        std::cerr << "You ain't connected to any chat room" << std::endl;
        return;
    }
    if (username.empty())
    {
        std::cerr << "Username not specified" << std::endl;
        return;
    }
    if (message.empty())
    {
        std::cerr << "Message not specified" << std::endl;
        return;
    }
    if (username == this->userPrx->getName())
    {
        std::cerr << "Cannot send message to yourself, you fool!";
        return;
    }
    Chat::UserList userList = this->chatRoomPrx->getUsers();
    for (auto it = std::begin(userList); it != std::end(userList); ++it)
    {
        Chat::ChatUserPrx user = *it;
        if (user->getName() == username)
        {
            user->sendPrivateMessage(this->userPrx, message);
            std::cout << "<" << this->userPrx->getName() << "><EVERYBODY> " << message << std::endl;
            return;
        }
    }
    std::cerr << "User not found" << std::endl;
}

void Client::sendMessage(std::string &message)
{
    if (this->chatRoomPrx == ICE_NULLPTR)
    {
        std::cerr << "You ain't connected to any chat room" << std::endl;
        return;
    }
    if (message.empty())
    {
        std::cerr << "Message not specified" << std::endl;
        return;
    }
    chatRoomPrx->sendMessage(this->userPrx, message);
}

void Client::showRoomList()
{
    Chat::ChatRoomList roomList = serverPrx->getRooms();
    if (roomList.empty())
    {
        std::cout << "No chat rooms available" << std::endl;
        return;
    }
    std::cout << "Available chat rooms:" << std::endl;
    for (auto it = std::begin(roomList); it != std::end(roomList); ++it)
    {
        Chat::ChatRoomPrx room = *it;
        std::cout << "Room: " << room->getName() << ", Users: " << room->getUsers().size() << std::endl;
    }
}

void Client::showUserList()
{
    if (this->chatRoomPrx == ICE_NULLPTR)
    {
        std::cerr << "You ain't connected to any chat room" << std::endl;
        return;
    }
    Chat::UserList userList = this->chatRoomPrx->getUsers();
    if (userList.size() == 1)
    {
        std::cout << "You're the lonely guy" << std::endl;
        return;
    }
    std::cout << "Users online:" << std::endl;
    for (auto it = std::begin(userList); it != std::end(userList); ++it)
    {
        Chat::ChatUserPrx user = *it;
        std::cout << user->getName() << std::endl;
    }
}

int main(int argc, char **argv)
{
    Client app;
    return app.main(argc, argv, "chat.prop");
}
