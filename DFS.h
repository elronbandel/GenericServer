//
// Created by fatuity on 1/10/19.
//

#ifndef ADVPROGPROJ2_DFS_H
#define ADVPROGPROJ2_DFS_H


#include "Searcher.h"

/**
 * remember that we might need to allocate "path" vector on heap so that it will stay as it was in every function call.
 *
 */
template<class Solution>
class DFS : public Searcher<Solution> {
    unordered_map<string, State<T> *> greys;
    unordered_map<string, State<T> *> blacks;
    vector<State<T> *> path;

    //recursive function to get path of dfs.
    Solution *dfs(State<T> *currentState, Searchable<T>* searchable) {
        greys.emplace(currentState->getType(), currentState);
        if (searchable->isGoalState(currentState)) {
            //create a new vector in case its null.
            path = vector<State<T> *>();
            path.push_back(currentState);
            return path;
        }
        list<State<T> *> states = searchable->getPossibleStates(currentState);
        for (State<T> *st : states) {
            //might not use it but its good to keep info about who is the parent.
            st->setCameFrom(currentState);
            if (greys.count((string)(*st)) == 0 && blacks.count((string)(*st)) == 0) {
                if (path = dfs(st, searchable) != nullptr) {
                    path.push_back(currentState);
                    return path;
                }
            }
        }
        blacks.emplace(currentState);
        return nullptr;
    }

public:
    virtual Solution *search(Searchable<T>* searchable) {
        State<T> *currentState = searchable->getInitialState();
        return dfs(currentState, searchable);
    }
};


#endif //ADVPROGPROJ2_DFS_H
