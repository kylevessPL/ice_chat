#ifndef PROJECT_ROOM_FACTORY_HPP
#define PROJECT_ROOM_FACTORY_HPP

#include <Ice/Application.h>

class RoomFactory : public Ice::Application
{
    public:
        int run(int argc, char **argv) override;
    private:
        Ice::ObjectAdapterPtr getAdapter(int portMin, int portMax);
        void listen();

};

#endif //PROJECT_ROOM_FACTORY_HPP
