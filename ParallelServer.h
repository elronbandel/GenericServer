//
// Created by elronbandel on 1/3/19.
//

#ifndef GR_PARALLELSERVER_H
#define GR_PARALLELSERVER_H


#include <map>
#include "SerialServer.h"
#include <mutex>
#include <condition_variable>
#include <vector>

class ParallelServer : public SerialServer {
    map<thread::id, thread*> clientsThreads;
    int routine(ClientHandler& handler) override;
    bool firstRound;
public:
    ParallelServer() = default;
    explicit ParallelServer(int timeOutSec) {
        setTimeOut(timeOutSec);
        firstRound = true;
    }
    void wait() {
        unique_lock<mutex> locker(mutx);
        if (!clientsThreads.empty())
            condition.wait(locker);
    }

protected:
    mutex mutx;
    condition_variable condition;
private:
    static void* startClientThread(ParallelServer* server, ClientHandler* handler);
    void notifyClientAccepted() override {
        condition.notify_one();
        SerialServer::notifyClientAccepted();
    }
    void terminate(thread::id id) {
        clientsThreads[id]->detach();
    }


    int stop() override {
        thread* trd = clientsThreads[this_thread::get_id()];
        if (this_thread::get_id() == serverThread.get_id()) {
            for (auto pair : clientsThreads) {
                trd = pair.second;
                delete trd;
            }
        }
    }

};


#endif //UNTITLED6_PARALLELSERVER_H
