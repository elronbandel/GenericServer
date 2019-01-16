//
// Created by fatuity on 1/11/19.
//

#ifndef ADVPROGPROJ2_BFS_H
#define ADVPROGPROJ2_BFS_H

#include <queue>
#include "Searcher.h"

template<class Solution,class T>
class BFS : public Searcher<Solution,T> {
    queue<State<T> *> q;
    unordered_map<string, State<T> *&> visited;
    Solution path = Solution();
public:
    Solution search(Searchable<T>* searchable) {
        State<T> *initState = searchable->getInitialState();
        return bfs(initState, searchable);
    }

    Solution bfs(State<T> *current, Searchable<T>* searchable) {
        q.push(current);
        visited.emplace(current->getType(), current);
        while (!q.empty()) {
            current = q.front();
            q.pop();
            if (searchable->isGoalState(current)) {
                path = this->backtrace(current);
                return path;
            }
            list<State<T> *> neighbours = searchable->getPossibleStates(current);
            for (State<T> *st : neighbours) {
                if (visited.count((string)(*st)) == 0) {
                    st->setCameFrom(current);
                    visited.emplace(st->getType(), st);
                    q.push(st);
                }
            }
        }
    }

};


#endif //ADVPROGPROJ2_BFS_H
