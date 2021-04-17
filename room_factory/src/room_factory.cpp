#include <chat.h>
#include <room_factory.hpp>
#include <ChatRoomFactoryI.hpp>
#include <ConnectionUtil.h>

int RoomFactory::run(int argc, char **argv)
{
    Ice::PropertiesPtr properties = communicator()->getProperties();
    int serverPort = properties->getPropertyAsIntWithDefault("server.port.set", 49152);
    Chat::ChatServerPrx serverPrx;
    Ice::ObjectPrx proxy = communicator()->stringToProxy("server:default -p " + std::to_string(serverPort));
    serverPrx = serverPrx.uncheckedCast(proxy);
    int portMin = properties->getPropertyAsIntWithDefault("roomfactory.port.range.min", 49153);
    int portMax= properties->getPropertyAsIntWithDefault("roomfactory.port.range.max", 55554);
    Ice::ObjectAdapterPtr adapterPtr = getAdapter(portMin, portMax);
    Chat::ChatRoomFactoryPtr roomFactoryPtr = new ChatRoomFactoryI();
    Chat::ChatRoomFactoryPrx roomFactoryPrx = roomFactoryPrx.uncheckedCast(adapterPtr->addWithUUID(roomFactoryPtr));
    adapterPtr->activate();
    serverPrx->registerChatRoomFactory(roomFactoryPrx);
    std::cout << "Room factory running..." << std::endl;
    listen();
    serverPrx->unregisterChatRoomFactory(roomFactoryPrx);
    communicator()->shutdown();
    communicator()->waitForShutdown();
    return EXIT_SUCCESS;
}

Ice::ObjectAdapterPtr RoomFactory::getAdapter(int portMin, int portMax)
{
    while (true)
    {
        int port = ConnectionUtil::getRandomPort(portMin, portMax);
        try
        {
            Ice::ObjectAdapterPtr adapterPtr = communicator()->createObjectAdapterWithEndpoints(
                    "room_factory_adapter",
                    "default -p " + std::to_string(port));
            std::cout << "Running room factory at port " << port << std::endl;
            return adapterPtr;
        }
        catch (Ice::SocketException ex)
        {
            continue;
        }
    }
}

void RoomFactory::listen()
{
    std::cout << "Enter /stop command to stop room factory" << std::endl;
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
}

int main(int argc, char **argv)
{
    RoomFactory app;
    return app.main(argc, argv, "chat.prop");
}
