//
// Created by elronbandel on 1/3/19.
//

#ifndef GSERVER_FILECACHEMANAGER_H
#define GSERVER_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <map>
#include <fstream>

using namespace std;

template<class Problem, class Solution>

class FileCacheManager: public CacheManager<Problem, Solution> {

    map<string, string> localCache;
    string filedCachePath;

public:

    FileCacheManager(string filePath) {
        filedCachePath = filePath;
    }

    //interface functions:

    bool isStored(Problem problem) override {
        localCache.find((string) problem) != localCache.end();
    }

    Solution request(Problem problem) override {
        if (isStored(problem)) {
            return Solution(localCache[problem]);
        }
    }
    void store(Problem problem, Solution solution) override {
        localCache[(string)problem] = (string)solution;
    }

private:
    void save() {
        ofstream fout(filedCachePath);
        if (fout.is_open()) {
            for (auto pair : localCache) {
                fout << pair.first << " " << pair.second << endl;
            }
            fout.close();
        }
    }
    void load() {
        string solution,problem;
        ifstream fin(filedCachePath);
        if (fin.is_open()) {
            while (fin >> problem >> solution) {
                localCache[problem] = solution;
            }
            fin.close();
        }
    }

};


#endif //GSERVER_FILECACHEMANAGER_H
