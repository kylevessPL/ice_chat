#include <client.hpp>

int Client::run(int argc, char **argv)
{
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    Client app;
    return app.main(argc, argv, "chat.prop");
}
