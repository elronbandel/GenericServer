//
// Created by fatuity on 1/11/19.
//

#ifndef ADVPROGPROJ2_BFS_H
#define ADVPROGPROJ2_BFS_H

#include <queue>
#include "Searcher.h"

template<class Solution>
class BFS : public Searcher<Solution> {
    queue<State<T> *> q;
    unordered_map<T, State<T> *> visited;
    vector<State<T> *> path;
public:
    Solution *search(Searchable<T> searchable) {
        State<T> *initState = searchable.getInitialState();
        return bfs(initState, searchable);
    }

    Solution *bfs(State<T> *current, Searchable<T> searchable) {
        q.push(current);
        visited.emplace(current->getType(), current);
        while (!q.empty()) {
            current = q.front();
            q.pop();
            if (searchable.isGoalState(current)) {
                path = backtrace(current);
                return path;
            }
            list<State<T> *> neighbours = searchable.getPossibleStates(current);
            for (State<T> *st : neighbours) {
                st->setCameFrom(current);
                if (visited.count(st) == 0) {
                    visited.emplace(st->getType(), st);
                    q.push(st);
                }
            }
        }
    }

};


#endif //ADVPROGPROJ2_BFS_H
