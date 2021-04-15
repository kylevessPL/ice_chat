#include <ChatRoomI.hpp>

ChatRoomI::ChatRoomI(const std::string& name) : name(name) {}

void ChatRoomI::sendMessage(const Chat::ChatUserPrx &from, const std::string &message, const Ice::Current &current)
{
    for (auto chatUserPrx : this->userList)
    {
        chatUserPrx->sendMessage(from, message);
    }
}

void ChatRoomI::addUser(const Chat::ChatUserPrx &who, const Ice::Current &current)
{
    this->userList.push_back(who);
    std::cout << "User " << who->getName() << " joined!";
}

void ChatRoomI::removeUser(const Chat::ChatUserPrx &who, const Ice::Current &current)
{
    this->userList.erase(std::remove(this->userList.begin(), this->userList.end(), who),
                         this->userList.end());
    std::cout << "User " << who->getName() << " left!";
}

Chat::UserList ChatRoomI::getUsers(const Ice::Current &current)
{
    return this->userList;
}

std::string ChatRoomI::getName(const Ice::Current &current)
{
    return this->name;
}
