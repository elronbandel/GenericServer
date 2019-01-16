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
#include "CacheManager.h"

template<class Problem, class Solution>
class SearchingClientHandler : public ClientHandler {
    Solver<Problem, Solution> *solver;
    CacheManager<string, string> *cacheManager;

    pair<int, int> getRowAndCol(string type) {
        string str;
        str += type[0];
        int row = stoi(str);
        str = "";
        str += type[type.size() - 1];
        int col = stoi(str);
        pair<int, int> rowAndCol(row, col);
        return rowAndCol;
    }

    string getPath(Solution solution) {
        size_t size = solution.size();
        string str, path;
        pair<int, int> currState;
        pair<int, int> nextState;
        if (!solution.empty()) {
            for (int i = 1; i < size; i++) {
                currState = getRowAndCol((string) *solution.at(i - 1));
                nextState = getRowAndCol((string) *solution.at(i));
                //for every state check what action needed.
                if (currState.first < nextState.first) {
                    path += "Down";
                } else if (currState.first > nextState.first) {
                    path += "Up";
                } else if (currState.second < nextState.second) {
                    path += "Right";
                } else if (currState.second > nextState.second) {
                    path += "Left";
                }
                if (i != size - 1) {
                    path += ",";
                }
            }
        }
        return path;
    }

public:
    SearchingClientHandler(Solver<Problem, Solution> *s, CacheManager<string, string> *cm) {
        solver = s;
        cacheManager = cm;
    }

    virtual void handle(istream &sin, ostream &sout) {
        string line, result, matrixRow, helpStr, initStr, goalStr;
        vector<string> rows;
        string matrixString;
        unsigned long int endOfRow;
        while (line != "end") {
            //sin will override the info if there is info left in the line.
            if (line.empty()) {
                sin >> line;
            } else {
                sin >> helpStr;
                line += helpStr;
            }
            //concatenate the lines received from stream;
            //notice that the line might contain another row.
            while ((endOfRow = line.find("\n")) != -1) {
                //if we got a few rows we need to get each of them separate.
                matrixRow = line.substr(0, endOfRow);
                rows.push_back(matrixRow);
                matrixString += matrixRow + "$";
                line = line.substr(endOfRow + 1, line.size() - 1);
            }
        }
        //check if the solution exists, if it does, return it to the client.
        if (cacheManager->contains(matrixString)) {
            sout << cacheManager->request(matrixString);
            return;
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

        //create and solve the problem.
        Searchable<string> *mg = MatrixCreator<string>::create(rows, initStr, goalStr);
        Solution solution = solver->solve(mg);
        //get the wanted result to the client and save it in the cache.
        result = this->getPath(solution);
        sout << result;
        sout.flush();
        cacheManager->store(matrixString, result);
    }
};


#endif //ADVPROGPROJ2_SEARCHINGCLIENTHANDLER_H
