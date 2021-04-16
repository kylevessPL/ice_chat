#ifndef PROJECT_ROOM_FACTORY_HPP
#define PROJECT_ROOM_FACTORY_HPP

#include <Ice/Application.h>

class RoomFactory : public Ice::Application
{
    public:
    int run(int argc, char **argv) override;

};

#endif //PROJECT_ROOM_FACTORY_HPP
