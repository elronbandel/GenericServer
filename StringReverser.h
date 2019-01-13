#ifndef ADVPROGPROJ2_STRINGREVERSER_H
#define ADVPROGPROJ2_STRINGREVERSER_H


#include "Solver.h"
#include <string>
#include <bits/stdc++.h>

using namespace std;

template<class Problem, class Solution>
class StringReverser : public Solver<Problem, Solution> {
public:
    virtual Solution *solve(Problem *p) {
        Solution *s = (Solution *) p;
        int len = s->size();
        for (int i = 0; i < len / 2; i++) {
            swap((*s)[i], (*s)[len - i - 1]);
        }
        return s;
    }
};


#endif