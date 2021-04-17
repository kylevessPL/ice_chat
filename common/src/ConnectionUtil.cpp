#include <ConnectionUtil.h>
#include <cstdlib>
#include <iostream>

int ConnectionUtil::getRandomPort(int portMin, int portMax) {
    return portMin + rand() % (portMax - portMin);
}
