#include <ChatRoomFactoryI.hpp>
#include <ChatRoomI.hpp>

Chat::ChatRoomPrx ChatRoomFactoryI::createChatRoom(const std::string &name, const Ice::Current &current)
{
    Chat::ChatRoomPtr chatRoomPtr = new ChatRoomI(name);
    Chat::ChatRoomPrx chatRoomPrx = chatRoomPrx.uncheckedCast(current.adapter->addWithUUID(chatRoomPtr));
    this->numOfChatRoomsRunning++;
    return chatRoomPrx;
}

Ice::Int ChatRoomFactoryI::numOfChatroomsRunning(const Ice::Current &current)
{
    return this->numOfChatRoomsRunning;
}
