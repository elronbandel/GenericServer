//
// Created by elronbandel on 1/7/19.
//

#ifndef GSERVER_GENERICSERVER_H
#define GSERVER_GENERICSERVER_H

#define DEFAULT_MAX_CLIENTS 10

#include "Server.h"
#include "Socket.h"

class GenericServer: public Server {
    Socket server;
    int maxClients;
    int clientsCounter;
    bool runing;
    bool accepting;


public:

    explicit GenericServer(int maxClientNum) : runing(false), maxClients(maxClientNum){}
    GenericServer() : runing(false), maxClients(DEFAULT_MAX_CLIENTS) {}
    int open(int port, ClientHandler& handler) override;
    int stop() override;


protected:
    virtual int routine(ClientHandler& handler);
    void start(int port);
    void serveOneClient(ClientHandler& handler);
    void openServer(int port, ClientHandler& handler);
    virtual void notifyClientAccepted();
};


#endif //GSERVER_GENERICSERVER_H
