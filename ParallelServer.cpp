//
// Created by elronbandel on 1/3/19.
//

#include "ParallelServer.h"

void ParallelServer::startClientThread(ParallelServer *server, ClientHandler* handler) {
    server->serveOneClient(*handler);
    server->terminate(this_thread::get_id());
}
int ParallelServer::routine(ClientHandler& handler) {
    unique_lock<mutex> locker(mutx);
    if (!clientsThreads.empty())
        condition.wait(locker);
    thread* clientThread = new thread(startClientThread, this, &handler);
    clientsThreads[clientThread->get_id()] = clientThread;
    return 1;
}
