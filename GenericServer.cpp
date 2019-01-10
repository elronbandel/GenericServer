//
// Created by elronbandel on 1/7/19.
//

#include "GenericServer.h"

void GenericServer::start(int port) {
   server = Socket();
   server.create();
   server.bind(port);
   server.listen(maxClients);
}

int GenericServer::open(int port, ClientHandler& handler) {
    openServer(port, handler);
}

void GenericServer::openServer(int port, ClientHandler& handler) {
    start(port);
    runing = true;
    while (this->runing) {
        routine(handler);
    }
}

int GenericServer::routine(ClientHandler& handler) {
    serveOneClient(handler);
    return 1;
}

void GenericServer::notifyClientAccepted() {

}

void GenericServer::serveOneClient(ClientHandler& handler) {
    if (runing) {
        Socket clientSocket = server.accept();
        notifyClientAccepted();
        SocketStream client(clientSocket);
        handler.handle(client, client);
        clientSocket.close();
    }
}


int GenericServer::stop() {
    runing = false;
}

