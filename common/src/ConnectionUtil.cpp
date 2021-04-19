#include <ConnectionUtil.h>
#include <cstdlib>

ConnectionUtil::ConnectionUtil() {}

int ConnectionUtil::getRandomPort(int portMin, int portMax) {
    return portMin + rand() % (portMax - portMin);
}
