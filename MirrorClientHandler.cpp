//
// Created by elronbandel on 1/10/19.
//

#include "MirrorClientHandler.h"

void MirrorClientHandler::handle(istream &sin, ostream &sout) {
    string s;
    sin >> s;
    sout << s << endl;
    sout.flush();
}
