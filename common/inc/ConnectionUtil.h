#ifndef PROJECT_CONNECTIONUTIL_H
#define PROJECT_CONNECTIONUTIL_H

#include <vector>

class ConnectionUtil
{
    public:
        static int getRandomPort(int portMin, int portMax);
    private:
        ConnectionUtil();

};

#endif //PROJECT_CONNECTIONUTIL_H
