#include <iostream>

#include "SearchingClientHandler.h"
#include "SerialServer.h"
#include "ParallelServer.h"
#include "FileCacheManager.h"

int main() {

    FileCacheManager<string, string> cache("cache.txt");
    cache.store("p1", "s1.1");


   // server.open(5400, handler);
    cout << "server on thread" <<endl;
    //sleep(60);
}