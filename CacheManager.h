//
// Created by elronbandel on 1/3/19.
//

#ifndef GSERVER_CACHEMANAGER_H
#define GSERVER_CACHEMANAGER_H

template<class Problem, class Solution>
class CacheManager {
public:
    virtual bool contains(Problem problem) = 0;
    virtual Solution request(Problem problem) = 0;
    virtual void store(Problem problem, Solution solution) = 0;
};


#endif //GSERVER_CACHEMANAGER_H
