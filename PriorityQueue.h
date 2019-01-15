//
// Created by fatuity on 1/9/19.
//

#ifndef ADVPROGPROJ2_PRIORITYQUEUE_H
#define ADVPROGPROJ2_PRIORITYQUEUE_H


#include <queue>
#include <unordered_map>
#include "State.h"

using namespace std;

template<class T>
class PriorityQueue {
    priority_queue<State<T> *, vector<State<T> *>, greater<State<T> *>> pq;
    unordered_map<string, State<T> *> container;
public:
    State<T> *pop() {
        State<T> *top = pq.top();
        pq.pop();
        container.erase(top->getType());
        return top;
    }

    bool empty() {
        return pq.empty();
    }

    bool contains(State<T> *state) {
        return (bool) container.count(state->getType());
    }

//    int size() {
//        return pq.size();
//    }

    void add(State<T> *state) {
        //create a new state so that we wont change the actual cost of the original state
        State<T>* newState;
        *(newState) = *(state);
        pq.push(newState);
        container.emplace(newState->getType(), newState);
    }

    void setPriority(State<T> *state) {
        state->setPathCost(state->getCost() + state->getCameFrom()->getPathCost());
    }
};


#endif //ADVPROGPROJ2_PRIORITYQUEUE_H
