//
// Created by fatuity on 1/8/19.
//

#ifndef ADVPROGPROJ2_BESTFIRSTSEARCH_H
#define ADVPROGPROJ2_BESTFIRSTSEARCH_H

#include <unordered_set>
#include "Searcher.h"
#include "PriorityQueue.h"

template<class Solution>
class BestFirstSearch : public Searcher<Solution> {
public:
    BestFirstSearch() {}

    virtual Solution *search(Searchable<class T> searchable) {
        //get the initial state.
        openList.add(searchable.getInitialState());
        unordered_set<T> closed;
        vector<State<T> *> path;

        while (!openList.empty()) {
            State<T> *state = openList.pop();
            closed.emplace(state->getType());
            if (searchable.isGoalState(state)) {
                path = backtrace(state);
                return (Solution *) path;
            }
            //get the neighbours
            list<State<T> *> neighbours = searchable.getPossibleStates(state);
            double currentPathCost = state->getPathCost();
            for (State<T> *st : neighbours) {
                //if neighbour is not in open and not in closed
                double neighbourPathCost = st->getPathCost();
                double neighbourCost = st->getCost();
                if (!openList.contains(st) && closed.count(st->getType()) == 0) {
                    //set state as neighbour parent and add the neighbour to open.
                    st->setCameFrom(state);
                    openList.add(st);
                    //**************need to check this part with michael.********************
                    //else if the current path is better then the previous
                } else if (currentPathCost + neighbourCost < neighbourPathCost) {
                    //set that we came from current state
                    st->setCameFrom(state);
                    //if the neighbour isnt in open set the new path and add it to open.
                    if (!openList.contains(st)) {
                        st->setPathCost(currentPathCost + neighbourCost);
                        openList.add(st);
                    }else{
                        // else adjust its priority
                        openList.setPriority(st);
                    }
                }
            }
        }
        //return nullptr if there is no solution.
        return nullptr;
    }
};


#endif //ADVPROGPROJ2_BESTFIRSTSEARCH_H
