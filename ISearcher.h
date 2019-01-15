//
// Created by fatuity on 1/8/19.
//

#ifndef ADVPROGPROJ2_ISEARCHER_H
#define ADVPROGPROJ2_ISEARCHER_H
#include "Searchable.h"
template<class Solution,class T>
class ISearcher {
public:
    virtual Solution* search (Searchable<T>* searchable) = 0;
    virtual int getNodesEvaluated() = 0;
};


#endif //ADVPROGPROJ2_ISEARCHER_H
