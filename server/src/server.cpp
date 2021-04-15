#include <server.hpp>

int Server::run(int argc, char **argv)
{
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    Server app;
    return app.main(argc, argv, "chat.prop");
}