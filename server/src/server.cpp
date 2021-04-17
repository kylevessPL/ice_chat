#include <chat.h>
#include <server.hpp>
#include <ChatServerI.hpp>

int Server::run(int argc, char **argv)
{
    Ice::PropertiesPtr properties = communicator()->getProperties();
    int serverPort = properties->getPropertyAsIntWithDefault("server.port.set", 49152);
    Ice::ObjectAdapterPtr adapterPtr = communicator()->createObjectAdapterWithEndpoints(
            "server_adapter",
            "default -p " + std::to_string(serverPort));
    Chat::ChatServerPtr serverPtr = new ChatServerI();
    adapterPtr->add(serverPtr, Ice::stringToIdentity("server"));
    adapterPtr->activate();

    std::cout << "Server running..." << std::endl;
    communicator()->waitForShutdown();

    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    Server app;
    return app.main(argc, argv, "chat.prop");
}