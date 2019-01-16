//
// Created by fatuity on 1/9/19.
//

#ifndef ADVPROGPROJ2_SEARCHER_H
#define ADVPROGPROJ2_SEARCHER_H


#include "ISearcher.h"
#include "PriorityQueue.h"

template<class Solution,class T>
class Searcher : public ISearcher<Solution,T> {
    int NodesEvaluated;
protected:
    PriorityQueue<T> openList;

    State<T> popOpenList() {
        NodesEvaluated++;
        return openList.pop();
    }
    //tracing the path from beginning to goal;
    Solution backtrace(State<T> *goal) {
        Solution path;
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

    virtual Solution search(Searchable<T>* searchable) = 0;

    virtual int getNodesEvaluated() {
        return NodesEvaluated;
    }
};


#endif //ADVPROGPROJ2_SEARCHER_H
