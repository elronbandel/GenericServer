//
// Created by elronbandel on 1/16/19.
//

#ifndef GSERVER_ASTAR_H
#define GSERVER_ASTAR_H

#include <unordered_set>
#include "Searcher.h"
#include <math.h>
#include <sstream>

class EuklidianHuresticator {
    pair<double, double> goal;
public:
    EuklidianHuresticator(){
    }
    explicit EuklidianHuresticator(const string& goal) {
        this->goal = stringToPair(goal);
    }
    double operator () (const string& point) {
        return distance(stringToPair(point), goal);
    }
    //setter for goal.
    void setGoal(const string& goal){
        this->goal = stringToPair(goal);
    }
private:
    double distance(pair<double, double> a, pair<double,double> b) {
        return sqrt(pow(2, a.first - b.first) + pow (2, a.second - b.second));
    }
    pair<double, double> stringToPair(const string& str) {
        pair<double, double> result;
        vector<string> temp = split(str, ',');
        if (temp.size() == 2) {
                result.first = stod(temp[0]);
                result.second = stod(temp[1]);
            return result;
        } else {
            throw string("Error: not string represents pair<double,double>.");
        }
    }
    vector<string> split(const string& s, char delimiter){
        vector<string> tokens;
        string token;
        istringstream tokenStream(s);
        while (getline(tokenStream, token, delimiter))
        {
            tokens.push_back(token);
        }
        return tokens;
    }
};

template<class Solution,class T, class Huresticator>
class AStar : public Searcher<Solution,T> {
    Huresticator huristic;
public:
    AStar(Huresticator h) {
        huristic = h;
    }

    virtual Solution search(Searchable<T>* searchable) {
        //get the initial state.
        this->openList.add(searchable->getInitialState());
        unordered_set<string> closed;
        Solution path;

        while (!this->openList.empty()) {
            State<T> *state = this->openList.pop();
            closed.emplace(state->getType());
            if (searchable->isGoalState(state)) {
                path = this->backtrace(state);
                return path;
            }
            //get the neighbours
            list<State<T> *> neighbours = searchable->getPossibleStates(state);
            double currentPathCost = state->getPathCost();
            for (State<T> *st : neighbours) {
                //if neighbour is not in open and not in closed
                double neighbourPathCost = st->getPathCost();
                double neighbourCost = st->getCost();
                if (!this->openList.contains(st) && closed.count((string)(*st)) == 0) {
                    //set state as neighbour parent and add the neighbour to open.
                    st->setCameFrom(state);
                    this->openList.add(st);
                    //**************need to check this part with michael.********************
                    //else if the current path is better then the previous
                } else if (currentPathCost + neighbourCost < neighbourPathCost) {
                    //set that we came from current state
                    st->setCameFrom(state);
                    //if the neighbour isnt in open set the new path and add it to open.
                    if (!this->openList.contains(st)) {
                        st->setPathCost(currentPathCost + neighbourCost + this->huristic((string)(*st)));
                        this->openList.add(st);
                    }else{
                        // else adjust its priority
                        this->openList.setPriority(st);
                    }
                }
            }
        }
        //return nullptr if there is no solution.
        return path;
    }
};



#endif //GSERVER_ASTAR_H
