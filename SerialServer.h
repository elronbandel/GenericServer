//
// Created by elronbandel on 1/3/19.
//

#ifndef GR_SERIALSERVER_H
#define GR_SERIALSERVER_H


#include <thread>
#include "GenericServer.h"

class SerialServer: public GenericServer {
public:
    SerialServer() = default;
    SerialServer(int time) {
        setTimeOut(time);
    }
protected:
    thread serverThread;
public:
    int open(int port, ClientHandler& handler) override;
    thread& mainThread()  {
        return serverThread;
    }
private:
    static void startServerThread(SerialServer* server,int port, ClientHandler* handler);

};



#endif //GR_SERIALSERVER_H
