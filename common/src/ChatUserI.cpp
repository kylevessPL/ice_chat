#include <ChatUserI.hpp>

ChatUserI::ChatUserI(const std::string& name) : name(name) {}

void ChatUserI::sendMessage(const Chat::ChatUserPrx &from, const std::string &message, const Ice::Current &current)
{
    std::cout << "<" << from->getName() << "><everybody> " << message << std::endl;
}

std::string ChatUserI::getName(const Ice::Current &current)
{
    return this->name;
}

void ChatUserI::sendPrivateMessage(const Chat::ChatUserPrx &from, const std::string &message, const Ice::Current &current)
{
    std::cout << "<" << from->getName() << "><you> " << message << std::endl;
}
