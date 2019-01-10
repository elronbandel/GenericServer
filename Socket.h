//
// Created by elronbandel on 1/9/19.
//

#ifndef GSERVER_SOCKET_H
#define GSERVER_SOCKET_H

#include <string>
#define FAILED -1

using namespace std;

class Socket {
    int sock;
    bool mode;

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
    int read(char* buffer, int buffer_size);
    int write(const char* buffer, int buffer_size);
    void write(const string& msg);
private:
    Socket(int sockfd, bool mood);
};


#endif //GSERVER_SOCKET_H
