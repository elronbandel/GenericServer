//
// Created by elronbandel on 1/10/19.
//

#ifndef GSERVER_MIRRORCLIENTHANDLER_H
#define GSERVER_MIRRORCLIENTHANDLER_H


#include "ClientHandler.h"

class MirrorClientHandler: public ClientHandler {
public:
    void handle(istream &sin, ostream &sout) override;
};


#endif //GSERVER_MIRRORCLIENTHANDLER_H
