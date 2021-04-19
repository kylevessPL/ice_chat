#include <ChatServerI.hpp>

Chat::ChatRoomList ChatServerI::getRooms(const Ice::Current &current)
{
    return this->roomList;
}

Chat::ChatRoomPrx ChatServerI::createChatRoom(const std::string &name, const Ice::Current &current)
{
    auto it1 = std::find_if(this->roomList.begin(),
                           this->roomList.end(),
                           [name](const Chat::ChatRoomPrx& list) {return list->getName() == name;});
    if (it1 != this->roomList.end())
    {
        throw Chat::RoomNameAlreadyRegisteredException();
    }
    if (this->roomFactoryList.empty())
    {
        throw Chat::NoRoomFactoryAvailableException();
    }
    auto it2 = std::min_element(this->roomFactoryList.begin(),
                                       this->roomFactoryList.end(),
                                       [](Chat::ChatRoomFactoryPrx const& lhs, Chat::ChatRoomFactoryPrx const& rhs)
                                       {return lhs->numOfChatroomsRunning() < rhs->numOfChatroomsRunning();});
    Chat::ChatRoomFactoryPrx chatRoomFactoryPrx = chatRoomFactoryPrx.checkedCast(*it2);
    Chat::ChatRoomPrx chatRoomPrx = chatRoomFactoryPrx->createChatRoom(name);
    this->roomList.push_back(chatRoomPrx);
    std::cout << "Room " << name << " created" << std::endl;
    return chatRoomPrx;
}

void ChatServerI::registerChatRoomFactory(const Chat::ChatRoomFactoryPrx &factory, const Ice::Current &current)
{
    this->roomFactoryList.push_back(factory);
    std::cout << "Room factory " << Ice::identityToString(factory->ice_getIdentity()) << " registered" << std::endl;
}

void ChatServerI::unregisterChatRoomFactory(const Chat::ChatRoomFactoryPrx &factory, const Ice::Current &current)
{
    this->roomFactoryList.erase(std::remove(this->roomFactoryList.begin(), this->roomFactoryList.end(), factory),
                                this->roomFactoryList.end());
    std::cout << "Room factory " << Ice::identityToString(factory->ice_getIdentity()) << " unregistered" << std::endl;
}

void ChatServerI::registerUser(const Chat::ChatUserPrx &who, const Ice::Current &current)
{
    std::string username = who->getName();
    auto it = std::find_if(this->registeredUserList.begin(),
                           this->registeredUserList.end(),
                           [username](const Chat::ChatUserPrx& list) {return list->getName() == username;});
    if (it != this->registeredUserList.end())
    {
        throw Chat::UsernameAlreadyRegisteredException();
    }
    registeredUserList.push_back(who);
    std::cout << "User " << username << " registered" << std::endl;
}

void ChatServerI::unregisterUser(const Chat::ChatUserPrx &who, const Ice::Current &current)
{
    this->registeredUserList.erase(std::remove(this->registeredUserList.begin(), this->registeredUserList.end(), who),
                         this->registeredUserList.end());
    std::cout << "User " << who->getName() << " unregistered" << std::endl;
}
