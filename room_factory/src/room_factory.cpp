#include <chat.h>
#include <room_factory.hpp>
#include <ChatRoomFactoryI.hpp>

int RoomFactory::run(int argc, char **argv)
{
    std::string name;
    do
    {
        std::cout << "Please enter room factory name: ";
        getline(std::cin, name);
        if (name.empty())
        {
            std::cout << "Room factory name cannot be empty!" << std::endl;
        }
    }
    while (name.empty());

    Ice::PropertiesPtr properties = communicator()->getProperties();
    int serverPort = properties->getPropertyAsIntWithDefault("server.port.set", 49152);
    Ice::ObjectPrx proxy = communicator()->stringToProxy(&"server:default -p " [serverPort]);
    Chat::ChatServerPrx serverPrx = serverPrx.uncheckedCast(proxy);

    int roomFactoryPort = properties->getPropertyAsIntWithDefault("roomfactory.port.set", 49153);
    Ice::ObjectAdapterPtr adapterPtr = communicator()->createObjectAdapterWithEndpoints(
            "room_factory",
            &"default -p " [roomFactoryPort]);
    Chat::ChatRoomFactoryPtr roomFactoryPtr = new ChatRoomFactoryI();
    Chat::ChatRoomFactoryPrx roomFactoryPrx = roomFactoryPrx.uncheckedCast(adapterPtr->addWithUUID(roomFactoryPtr));
    adapterPtr->activate();

    serverPrx->registerChatRoomFactory(roomFactoryPrx);
    communicator()->waitForShutdown();
    serverPrx->unregisterChatRoomFactory(roomFactoryPrx);

    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    RoomFactory app;
    return app.main(argc, argv, "chat.prop");
}
