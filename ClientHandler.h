//
// Created by elronbandel on 1/3/19.
//

#ifndef GSERVER_CLIENTHANDLER_H
#define GSERVER_CLIENTHANDLER_H

#include <iostream>

using namespace std;

class ClientHandler {
public:
    virtual void handle(istream& sin, ostream& sout) = 0;
    virtual ~ClientHandler(){}
};


#endif //GSERVER_CLIENTHANDLER_H
