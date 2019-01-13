//
// Created by fatuity on 1/8/19.
//

#ifndef ADVPROGPROJ2_SEARCHABLE_H
#define ADVPROGPROJ2_SEARCHABLE_H

#include <list>
#include "State.h"

template<class T>
class Searchable {
public:
    virtual State<T> *getInitialState() = 0;

    virtual bool isGoalState(State<T> *state) = 0;

    virtual std::list<State<T> *> getPossibleStates(State<T> *state) = 0;
};


#endif //ADVPROGPROJ2_SEARCHABLE_H
