#ifndef GSERVER_SOLVER_H
#define GSERVER_SOLVER_H

template<class Problem, class Solution>
class Solver {
public:
    virtual Solution *solve(Problem *p) = 0;
};


#endif //GSERVER_SOLVER_H
