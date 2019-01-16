//
// Created by elronbandel on 1/3/19.
//

#include "SerialServer.h"
#include <thread>
using namespace std;
int SerialServer::open(int port, ClientHandler& handler) {
    serverThread = thread(startServerThread, this, port, &handler);
    return 1;
}
void SerialServer::startServerThread(SerialServer* server, int port, ClientHandler* handler) {
    server->openServer(port, *handler);
    //terminate(); //close the thread
}

