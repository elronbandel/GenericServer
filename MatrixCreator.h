//
// Created by fatuity on 1/8/19.
//

#ifndef ADVPROGPROJ2_MATRIXCREATOR_H
#define ADVPROGPROJ2_MATRIXCREATOR_H


#include "MatrixGraph.h"
#include "State.h"
#include <limits>

template<class T>
class MatrixCreator {
public:
    // a function to create matrix
    static MatrixGraph<T> create(vector<string> strMatrix, string init, string goal) {
        int initRow, initCol, goalRow, goalCol;
        int rowSize, col;
        int rowNum = strMatrix.size();
        unsigned long int comma;
        double inf = numeric_limits<double>::infinity();
        unordered_map<T, State<string> *> matrix;
        string strCost, row, key;
        State<string> *goalState = nullptr, *initState = nullptr;
        //find the initial state and the goal state values.
        initRow = stoi(init.substr(comma = init.find(",")));
        initCol = stoi(init.substr(comma, init.size() - 1));
        goalRow = stoi(goal.substr(comma = goal.find(",")));
        goalCol = stoi(goal.substr(comma, goal.size() - 1));
        //for each row
        for (int i = 0; i < rowNum; i++) {
            col = 0;
            row = strMatrix[i];
            rowSize = row.size();
            // might need another comma for the last number in the row.
            if (row[rowSize - 1] != ',') {
                row = row + ",";
            }
            //run for each char and combine it to a number of one column.
            for (int j = 0; j < rowSize; j++) {
                if (row[j] != ',') {
                    strCost += row[j];
                } else {
                    key = to_string(i) + "," + to_string(col);
                    State<string> *state = new State<string>(new string(key));
                    if (col == initCol && i == initRow) {
                        initState = state;
                    } else if (col == goalCol && i == goalRow) {
                        goalState = state;
                    }
                    if (strCost != "-1") {
                        state->setCost(stod(strCost));
                        state->setPathCost(stod(strCost));
                    } else {
                        state->setCost(inf);
                        state->setPathCost(inf);
                    }
                    col++;
                    matrix.emplace(key, state);
                }
            }
        }
        return MatrixGraph<T>(matrix, initState, goalState, col, rowNum);
    }
//    static vector<vector<string>> split(vector<string> strMatrix){
//        string strCost;
//        for(int i = 0; i<strMatrix.size(); i++){
//            string s = strMatrix.at(i);
//            for(int j = 0;j<s.size(); j++){
//                if(s[j] != ','){
//                    strCost + =
//                }
//            }
//        }
//    }
};


#endif //ADVPROGPROJ2_MATRIXCREATOR_H
