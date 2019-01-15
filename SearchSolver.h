//
// Created by fatuity on 1/7/19.
//

#ifndef ADVPROGPROJ2_SEARCHSOLVER_H
#define ADVPROGPROJ2_SEARCHSOLVER_H

#include "Solver.h"
#include "ISearcher.h"
#include <string>
template <class Problem,class Solution,class T>
class SearchSolver : public Solver<Problem,Solution> {
    ISearcher<Solution,T> *searcher;
public:
    SearchSolver(ISearcher<Solution,T>* srchr){
        searcher = srchr;
    }
    virtual Solution *solve(Problem *p) {
        Solution *solution;
        solution = searcher->search(p);
        return solution;
    }
};

#endif //ADVPROGPROJ2_SEARCHSOLVER_H
