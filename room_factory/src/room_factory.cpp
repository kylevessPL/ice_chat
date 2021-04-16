#include <chat.h>
#include <room_factory.hpp>
#include <ChatRoomFactoryI.hpp>

int RoomFactory::run(int argc, char **argv)
{
    Ice::PropertiesPtr properties = communicator()->getProperties();
    int serverPort = properties->getPropertyAsIntWithDefault("server.port.set", 49152);
    Ice::ObjectPrx proxy = communicator()->stringToProxy("server:default -p " + std::to_string(serverPort));
    Chat::ChatServerPrx serverPrx = serverPrx.uncheckedCast(proxy);

    int roomFactoryPort = properties->getPropertyAsIntWithDefault("roomfactory.port.set", 49153);
    Ice::ObjectAdapterPtr adapterPtr = communicator()->createObjectAdapterWithEndpoints(
            "room_factory_adapter",
            "default -p " + std::to_string(roomFactoryPort));
    Chat::ChatRoomFactoryPtr roomFactoryPtr = new ChatRoomFactoryI();
    Chat::ChatRoomFactoryPrx roomFactoryPrx = roomFactoryPrx.uncheckedCast(adapterPtr->addWithUUID(roomFactoryPtr));
    adapterPtr->activate();
    serverPrx->registerChatRoomFactory(roomFactoryPrx);

    std::cout << "Room factory running..." << std::endl;
    std::cout << "Enter /stop command to kill room factory" << std::endl;
    for(;;)
    {
        std::string command;
        std::cout << "$ ";
        std::cin >> command;
        if (command == "/stop")
        {
            break;
        }
        std::cout << "Unknown command" << std::endl;
    }

    serverPrx->unregisterChatRoomFactory(roomFactoryPrx);
    communicator()->shutdown();
    communicator()->waitForShutdown();

    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    RoomFactory app;
    return app.main(argc, argv, "chat.prop");
}
