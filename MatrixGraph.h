//
// Created by fatuity on 1/8/19.
//

#ifndef ADVPROGPROJ2_MATRIXGRAPH_H
#define ADVPROGPROJ2_MATRIXGRAPH_H


#include "Searchable.h"
#include "State.h"
#include <map>
#include <vector>
#include <unordered_map>

using namespace std;

template<class T>
class MatrixGraph : public Searchable<T> {
    State<T> *goal;
    State<T> *initialState;
    int height, width;
    unordered_map<string, State<T> *> matrix;
public:
    MatrixGraph(unordered_map<string, State<T> *> states, State<T> *init,
                State<T> *goalState, int colNum, int rowNum) {
        matrix = states;
        initialState = init;
        goal = goalState;
        height = colNum;
        width = rowNum;
    }

    pair<int, int> getRowAndCol(T type) {
        string str;
        str += type[0];
        int row = stoi(str);
        str = "";
        str += type[type.size() - 1];
        int col = stoi(str);
        pair<int, int> rowAndCol(row, col);
        return rowAndCol;
    }

    virtual State<T> *getInitialState() {
        return initialState;
    }

    virtual bool isGoalState(State<T> *state) {
        return state == goal;
    }

    virtual std::list<State<T> *> getPossibleStates(State<T> *state) {
        list<State<T> *> states;
        pair<int, int> rowAndCol = getRowAndCol(*(state->getType()));
        int row = rowAndCol.first, col = rowAndCol.second;
        string key;
        int minus_1 = stoi("-1");
        if (row + 1 < height) {
            key = to_string(row + 1) + "," + to_string(col);
            if(matrix[key]->getCost() != minus_1){
                states.push_back(matrix[key]);
            }
        }
        if (row - 1 >= 0) {
            key = to_string(row - 1) + "," + to_string(col);
            if(matrix[key]->getCost() != minus_1){
                states.push_back(matrix[key]);
            }
        }
        if (col + 1 < width) {
            key = to_string(row) + "," + to_string(col + 1);
            if(matrix[key]->getCost() != minus_1){
                states.push_back(matrix[key]);
            }
        }
        if (col - 1 >= 0) {
            key = to_string(row) + "," + to_string(col - 1);
            if(matrix[key]->getCost() != minus_1){
                states.push_back(matrix[key]);
            }
        }
        return states;
    }
};


#endif //ADVPROGPROJ2_MATRIXGRAPH_H
