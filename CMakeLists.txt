cmake_minimum_required(VERSION 3.13)
project(gserver)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(gserver main.cpp Server.cpp Server.h ParallelServer.cpp ParallelServer.h SerialServer.cpp SerialServer.h ClientHandler.cpp ClientHandler.h TestClientHandler.cpp TestClientHandler.h Solver.cpp Solver.h CacheManager.h StringReverser.cpp StringReverser.h SearchSolver.cpp SearchSolver.h ISearcher.h BestFirstSearch.h BFS.cpp BFS.h DFS.cpp DFS.h HillClimbingAlgorithm.cpp HillClimbingAlgorithm.h Searchable.cpp Searchable.h SPSP.cpp SPSP.h MatrixBuilder.cpp MatrixBuilder.h FileCacheManager.cpp FileCacheManager.h SocketStream.cpp SocketStream.h GenericServer.cpp GenericServer.h Socket.cpp Socket.h MirrorClientHandler.cpp MirrorClientHandler.h)