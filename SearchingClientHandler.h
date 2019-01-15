//
// Created by fatuity on 1/13/19.
//

#ifndef ADVPROGPROJ2_SEARCHINGCLIENTHANDLER_H
#define ADVPROGPROJ2_SEARCHINGCLIENTHANDLER_H

#include <vector>
#include "ClientHandler.h"
#include "Solver.h"
#include "MatrixCreator.h"
#include "MatrixGraph.h"

template<class Problem, class Solution>
class SearchingClientHandler : public ClientHandler {
    Solver<Problem, Solution> solver;
//    CacheManager cacheManager;
public:
//    SearchingClientHandler(Solver<Problem,Solution> s, CacheManager cm){
//        solver = s;
//        cacheManager = cm;
//    }
    virtual void handle(istream &sin, ostream &sout) {
        string line, result, matrixRow, helpStr, initStr, goalStr;
        vector<string> rows;
        unsigned long int endOfRow;
        while (line != "end") {
            //sin will override the info if there is info left in the line.
            if (line.empty()) {
                sin >> line;
            } else {
                sin >> helpStr;
                line += helpStr;
            }
            //notice that the line might contain another row.
            while (endOfRow = line.find("\n") != -1) {
                //if we got a few rows we need to get each of them separate.
                matrixRow = line.substr(0, endOfRow);
                rows.push_back(matrixRow);
                line = line.substr(endOfRow, line.size() - 1);
            }
        }
        //we finished receiving information, check if "end" entered the vector and remove it.
        if (rows.back() == "end") {
            rows.pop_back();
        }
        //get the init and goal states.
        goalStr = rows.back();
        rows.pop_back();
        initStr = rows.back();
        rows.pop_back();
        //solve the problem;
        MatrixCreator<string> matrixCreator;
        MatrixGraph<string> mg = matrixCreator.create(rows, initStr, goalStr);
        Solution *solution = solver.solve(mg);
        size_t size = solution->size();
        for (int i = 0; i < size; i++) {
            result += solution->at(i);
        }
        sout << result;
        sout.flush();
    }
};


#endif //ADVPROGPROJ2_SEARCHINGCLIENTHANDLER_H
