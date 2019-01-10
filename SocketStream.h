//
// Created by elronbandel on 1/7/19.
//

#ifndef GSERVER_SOCKETSTREAM_H
#define GSERVER_SOCKETSTREAM_H

#include <string>
#include <iostream>
#include <unistd.h>
#include <iostream>

#include "Socket.h"

#define SOCKBUFSIZE 256

using namespace std;
class sockbuf;

class SocketStream : public iostream {
    sockbuf* skbuf;
public:
    SocketStream(Socket s);
//    ~SocketStream() {
//        delete skbuf;
//    }
};

class sockbuf : public streambuf {
    Socket s;

public:
    sockbuf(Socket sock);
    ~sockbuf();

    int underflow();	 // get data from socket into get area
    int overflow(int c); // put data from put area into socket
    int sync();		     // flush pbuf

    int in_avail(void);

private:
    char gbuf[SOCKBUFSIZE];
    char pbuf[SOCKBUFSIZE];

};


#endif //GSERVER_SOCKETSTREAM_H
