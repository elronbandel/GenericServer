//
// Created by fatuity on 1/8/19.
//

#ifndef ADVPROGPROJ2_NODE_H
#define ADVPROGPROJ2_NODE_H

#include <list>
#include <string>

template<class T>
class State {
    T t;
    double nodeCost, pathCost;
    State<T> *cameFrom;
public:
    State() {
        t = nullptr;
        cameFrom = nullptr;
    }

    explicit State(T &type) : t(type) {
        t = type;
        cameFrom = nullptr;
    }

    void setCost(double cost) {
        nodeCost = cost;
    }

    double getCost() const {
        return nodeCost;
    }

    T getType() const {
        return t;
    }

    bool operator==(const State<T> *node) const {
        return t == node->getT();
    }

    void setCameFrom(State<T> *parent) {
        cameFrom = parent;
    }

    State<T> *getCameFrom() const {
        return cameFrom;
    }

    bool operator>(const State<T> *state) const {
        return pathCost > state->getPathCost();
    }

    bool operator<(const State<T> *state) const {
        return pathCost < state->getPathCost();
    }

    void setPathCost(double cost) {
        pathCost = cost;
    }

    double getPathCost() const {
        return pathCost;
    }
    explicit operator std::string() const{
        return (std::string)t;
    }
};


#endif //ADVPROGPROJ2_NODE_H
