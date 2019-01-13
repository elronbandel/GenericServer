//
// Created by fatuity on 1/7/19.
//

#ifndef ADVPROGPROJ2_SEARCHSOLVER_H
#define ADVPROGPROJ2_SEARCHSOLVER_H

#include "Solver.h"
#include "ISearcher.h"
template <class Problem,class Solution>
class SearchSolver : public Solver<Problem,Solution> {
    ISearcher<Solution> *searcher;
public:
    SearchSolver(ISearcher<Solution> srchr){
        searcher = srchr;
    }
    virtual Solution *solve(Problem *p) {
        Solution *solution;
        solution = searcher->search(p);
        return solution;
    }
};

#endif //ADVPROGPROJ2_SEARCHSOLVER_H
