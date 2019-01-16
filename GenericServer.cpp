//
// Created by elronbandel on 1/7/19.
//

#include "GenericServer.h"

void GenericServer::start(int port) {
   server = Socket();
   server.create();
   server.bind(port);
   server.listen(maxClients);
   if (timeOutSeconds > NO_TIMEOUT) {
       server.setTimeOut(timeOutSeconds);
   }
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
void GenericServer::endRoutine() {

}

int GenericServer::routine(ClientHandler& handler) {
    serveOneClient(handler);
    return 1;
}

void GenericServer::notifyClientAccepted() {
    clientsCounter++;
}

void GenericServer::serveOneClient(ClientHandler& handler) {
    if (runing) {
        if (!timeOut()) {
            if (timeOutSeconds > NO_TIMEOUT) {
                server.setTimeOut(timeOutSeconds);
            }
            Socket clientSocket = server.accept();
            if (clientSocket.is_open()) {
                notifyClientAccepted();
                SocketStream client(clientSocket);
                handler.handle(client, client);
                clientSocket.close();
                clientsCounter--;
            }
        }
    }
}


int GenericServer::stop() {
    runing = false;
}

