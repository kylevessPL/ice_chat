#ifndef PROJECT_CLIENT_HPP
#define PROJECT_CLIENT_HPP

#include <Ice/Application.h>

class Client : public Ice::Application
{
    public:
        int run(int argc, char **argv) override;

};

#endif //PROJECT_CLIENT_HPP
