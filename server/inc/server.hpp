#ifndef PROJECT_SERVER_HPP
#define PROJECT_SERVER_HPP

#include <Ice/Application.h>

class Server : public Ice::Application
{
public:
    int run(int argc, char **argv) override;

};

#endif //PROJECT_SERVER_HPP
