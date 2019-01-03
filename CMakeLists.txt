cmake_minimum_required(VERSION 3.13)
project(gserver)

set(CMAKE_CXX_STANDARD 14)

add_executable(gserver main.cpp Server.cpp Server.h ParallelServer.cpp ParallelServer.h SerialServer.cpp SerialServer.h ClientHandler.cpp ClientHandler.h TestClientHandler.cpp TestClientHandler.h Solver.cpp Solver.h CacheManager.h StringReverser.cpp StringReverser.h SearchSolver.cpp SearchSolver.h ISearcher.h BestFirstSearch.h BFS.cpp BFS.h DFS.cpp DFS.h HillClimbingAlgorithm.cpp HillClimbingAlgorithm.h)