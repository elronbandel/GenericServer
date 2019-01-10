#include <iostream>

#include "MirrorClientHandler.h"
#include "SerialServer.h"
#include "ParallelServer.h"

int main() {
    MirrorClientHandler handler;
    ParallelServer server;
    server.open(5400, handler);
    cout << "server on thread" <<endl;
    sleep(60);
}