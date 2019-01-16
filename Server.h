//
// Created by elronbandel on 1/3/19.
//

#ifndef GR_SERVER_H
#define GR_SERVER_H


#include "ClientHandler.h"
#include "SocketStream.h"

class Server {

public:
    virtual int open(int port, ClientHandler& cl) = 0;
    virtual int stop() = 0;
};

#endif //UNTITLED6_SERVER_H
