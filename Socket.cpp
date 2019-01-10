//
// Created by elronbandel on 1/9/19.
//

#include "Socket.h"

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include <string>

#define FAILED -1
#define CLIENT 0
#define SERVER 1
#define BUFFER_SIZE 256


void Socket::create() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == FAILED)
        throw string("Error: failed creating socket.");
}
Socket::Socket(int sockfd, bool mood) {
    sock = sockfd;
    mode = mood;
}
void Socket::bind(int port) {
    if (sock != FAILED) {
        struct sockaddr_in serverAddress;
        socklen_t servAddrLen = sizeof(serverAddress);
        /* Initialize socket structure */
        bzero((char *) &serverAddress, sizeof(serverAddress));
        //address
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(port);
        //bind the host adress using bind
        if (::bind(sock, (struct sockaddr *) &serverAddress, servAddrLen) == FAILED)
            throw string("Error: failed binding socket to port:" + to_string(port) + ".");
    }
    mode = SERVER;
}
void Socket::listen(int maxClients) {
    if (::listen(sock,maxClients)  ==  FAILED)
        throw string("Error: failed listening from socket:" + to_string(sock) + ".");
}
Socket Socket::accept() {
    if (mode == SERVER) {
        struct sockaddr_in clientAdress;
        socklen_t cliAddrLen = sizeof(clientAdress);
        //look for clients
        int clientSocket = ::accept(sock, (struct sockaddr *) &clientAdress, &cliAddrLen);
        if (clientSocket <= FAILED)
            throw string("Error: failed to open client socket.");
        return Socket(clientSocket, CLIENT);
    }
    return Socket();



}
int Socket::read(char *buffer, int buffer_size) {
    bzero(buffer, BUFFER_SIZE);
    ssize_t bytes_readed = ::read(sock, buffer, buffer_size);
    if ( bytes_readed == FAILED)
        throw string("Error: failed reading from socket " + to_string(sock) + ".");
    return (int)bytes_readed;
}
string Socket::read() {
    char buffer[BUFFER_SIZE];
    read(buffer, BUFFER_SIZE);
    return buffer;
}
int Socket::write(const char *buffer, int buffer_size) {
    ssize_t bytes_wrriten = ::write(sock, buffer, buffer_size);
    if (bytes_wrriten == FAILED)
        throw string("Error: failed writing '" + string(buffer) + "' to socket " + to_string(sock) + ".");
    return (int)bytes_wrriten;
}
void Socket::write(const string &msg) {
    write(msg.c_str(), msg.length());
}

void Socket::close() {
    if (sock != FAILED) {
        ::close(sock);
    }
}
void Socket::connect(string host, int port) {
    //connect to server and update:
    struct sockaddr_in serverAddress;
    socklen_t addressLen = sizeof(serverAddress);
    struct hostent *server = gethostbyname(host.c_str());
    if (server == nullptr)
        throw "Error: failed finding the host";
    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serverAddress.sin_addr.s_addr, server->h_length);
    serverAddress.sin_port = htons(port);
    if (::connect(sock, (struct sockaddr *) &serverAddress, addressLen) == FAILED)
        throw "Error: client failed to connect to server";

    mode = CLIENT;
}