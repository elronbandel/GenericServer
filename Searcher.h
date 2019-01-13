//
// Created by fatuity on 1/9/19.
//

#ifndef ADVPROGPROJ2_SEARCHER_H
#define ADVPROGPROJ2_SEARCHER_H


#include "ISearcher.h"
#include "PriorityQueue.h"

template<class Solution>
class Searcher : public ISearcher<Solution> {
    int NodesEvaluated;
protected:
    PriorityQueue<class T> openList;

    State<class T> popOpenList() {
        NodesEvaluated++;
        return openList.pop();
    }
    //tracing the path from beginning to goal;
    vector<State<T>*> backtrace(State<T> *goal) {
        vector<State<T>*> path;
        while (goal != nullptr) {
            path.push_back(goal);
            goal = goal->getCameFrom();
        }
        return path;
    }

public:
    Searcher() {
        NodesEvaluated = 0;
    }

    virtual Solution *search(Searchable<class T> searchable) = 0;

    virtual int getNodesEvaluated() {
        return NodesEvaluated;
    }
};


#endif //ADVPROGPROJ2_SEARCHER_H
