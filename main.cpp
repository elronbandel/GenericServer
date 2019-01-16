#include <iostream>
#include <string>
#include "Solver.h"
#include "StringReverser.h"
#include "SearchSolver.h"
#include "MatrixGraph.h"
#include "MatrixCreator.h"
#include "ISearcher.h"
#include "BFS.h"
#include "DFS.h"
#include "BestFirstSearch.h"
#include "ParallelServer.h"
#include "SearchingClientHandler.h"
#include "FileCacheManager.h"
#include <ctime>
#include <cstdlib>

#define SERVER_TIMOUT 30

using std::cout;
using std::string;
using std::rand;

int main(int argc, char* argv[]) {
    if (argc == 2) {
        int port = stoi(argv[1]);
        vector<State<string> *> path;
        string row;
        vector<string> rows;
        ISearcher<vector<State<string> *>, string> *searcher = new DFS<vector<State<string> *>, string>();
        Solver<Searchable<string>, vector<State<string> *>>* solver =
                 new SearchSolver<Searchable<string>, vector<State<string> *>, string>(searcher);
        CacheManager<string,string>* cacheManager = new FileCacheManager<string,string>("cache.txt");
        SearchingClientHandler<Searchable<string>, vector<State<string> *>> handler(solver, cacheManager);
        ParallelServer server(SERVER_TIMOUT); //start server with timeout of 30
        server.open(port, handler);
        sleep(60);
    }

    return 0;
}