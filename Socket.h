//
// Created by elronbandel on 1/9/19.
//

#ifndef GSERVER_SOCKET_H
#define GSERVER_SOCKET_H

#include <string>
#include <stdexcept>
#include <cerrno>

#define FAILED -1

using namespace std;

class timeout_exception : public std::runtime_error
{
public:
    timeout_exception(const char* msg) : std::runtime_error(msg){}
    timeout_exception(std::string msg) : std::runtime_error(msg){}
};

class Socket {
    int sock;
    bool mode;
    bool isWouldBlock;

public:
    Socket() {
        sock = FAILED;
    }
    void create();
    void bind(int port);
    void listen(int maxClients);
    Socket accept();
    void connect(string host, int port);
    void close();
    string read();
    void setTimeOut(int val);
    bool wouldBlock() {
        return isWouldBlock;
    }
    int read(char* buffer, int buffer_size);
    int write(const char* buffer, int buffer_size);
    void write(const string& msg);
private:
    Socket(int sockfd, bool mood);
};


#endif //GSERVER_SOCKET_H
