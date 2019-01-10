//
// Created by elronbandel on 1/3/19.
//

#ifndef GR_PARALLELSERVER_H
#define GR_PARALLELSERVER_H


#include <map>
#include "SerialServer.h"
#include <mutex>
#include <condition_variable>

class ParallelServer : public SerialServer {
    map<thread::id, thread*> clientsThreads;
    int routine(ClientHandler& handler) override;

protected:
    mutex mutx;
    condition_variable condition;
private:
    static void startClientThread(ParallelServer* server, ClientHandler* handler);
    void notifyClientAccepted() override {
        condition.notify_one();
        SerialServer::notifyClientAccepted();
    }
    void terminate(thread::id id) {
        thread* trd = clientsThreads[id];
        clientsThreads.erase(id);
        trd->detach();
        delete trd;
    }
};


#endif //UNTITLED6_PARALLELSERVER_H
