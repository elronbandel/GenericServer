//
// Created by elronbandel on 1/3/19.
//

#ifndef GSERVER_FILECACHEMANAGER_H
#define GSERVER_FILECACHEMANAGER_H

#define DEFAULT_CACHE_SIZE 3
#define TEMP_FILE "file_cache_manager_temp.txt"
#define END_OF_LINE_SYM '$'
#define SPACE_SYMBOL '@'
#include "CacheManager.h"
#include <map>
#include <fstream>
#include <list>
#include <vector>
#include <limits.h>
#include <algorithm>

using namespace std;

template<class Problem, class Solution>

class FileCacheManager: public CacheManager<Problem, Solution> {
    map <string, string> localCache;
    map <string, int> keyToOrder;
    map <int, string> orderToKey;
    string filedCachePath;
    unsigned int enteredCounter;
    unsigned int cacheSize;

public:

    explicit FileCacheManager(string filePath) {
        filedCachePath = filePath;
        cacheSize = DEFAULT_CACHE_SIZE;
        enteredCounter = 0;
        load();
    }
    ~FileCacheManager() {
        save();
    }

    //interface functions:

    bool contains(Problem problem) override {

        if (localCache.find((string) problem) != localCache.end())
            return true;
        else
            return load((string) problem);

    }

    Solution request(Problem problem) override {
        if (contains(problem)) {

            return Solution(localCache[problem]);
        }
    }
    void updateOrder(Problem problem) {
        string key = (string) problem;
        if (keyToOrder.find(key) != keyToOrder.end())
            orderToKey.erase(keyToOrder[key]);
        orderToKey[enteredCounter] = key;
        keyToOrder[key] = enteredCounter;
        if (enteredCounter <= UINT_MAX) {
            enteredCounter++;
        } else {
            save();
            localCache.clear();
            orderToKey.clear();
            keyToOrder.clear();
            enteredCounter = 0;
            load();
        }
    }
    void store(Problem problem, Solution solution) override {
        contains(problem);
        storeLocaly((string) problem, (string) solution);
    }


private:
    string storableLine(const string& str) {
        string newString = str;
        std::replace( newString.begin(), newString.end(), '\n', END_OF_LINE_SYM);
        return newString;
    }
    string originalLine(const string& str) {
        string newString = str;
        std::replace( newString.begin(), newString.end(), END_OF_LINE_SYM, '\n');
        return newString;
    }
    void storeLocaly(string first, string second) {
            if (localCache.size() >= cacheSize &&
                                localCache.find(first) == localCache.end()) { //cache overflow
                saveNonPriortized();
            }
        localCache[originalLine(first)] = originalLine(second);
        updateOrder(first);
    }
    void save() {
        if (!localCache.empty()) {
            ofstream fout(filedCachePath, ios::app);
            if (fout.is_open()) {
                for (auto it = orderToKey.begin() ; it != orderToKey.end(); it++) {
                    string key = it->second;
                    fout << storableLine(key) << " " << storableLine(localCache[key]) << endl;
                }
                fout.close();
            }
        }

    }
    void store(vector<pair<string, string>>& dataVector) {
        std::ofstream fout(filedCachePath);
        if (fout.is_open()) {
            for (auto& data : dataVector)
                fout << storableLine(data.first) << " " << storableLine(data.second) << endl;
            fout.close();
        }
    }
    void saveNonPriortized() {
        std::ofstream fout(filedCachePath, ios::app); //open file as logger
        if (fout.is_open()) {
                string key = (localCache.begin())->first;
                fout << storableLine(key) << " " << storableLine(localCache[key]) << endl;
                eraseLocal(key);

            fout.close();
        }
    }
    void eraseLocal(string key) {
        localCache.erase(key);
        orderToKey.erase(keyToOrder[key]);
        keyToOrder.erase(key);
    }
    vector<pair<string, string>> retrive() {
        vector<pair<string, string>> filedData;
        ifstream fin(filedCachePath);
        if (fin.is_open()) {
            pair<string, string> temp;
            while (fin >> temp.first >> temp.second) {
                filedData.emplace_back(temp);
            }
            fin.close();
        }
        return filedData;
    }
    void load() {
        string solution,problem;
        list<string> order;
        vector<pair<string, string>> filedData = retrive();
        for (int i = 0; i < cacheSize && !filedData.empty(); i++) {
            localCache[originalLine(filedData.back().first)]
                          = originalLine(filedData.back().second);
            order.emplace_front(filedData.back().first);
            filedData.pop_back();
        }
        for (auto key : order)
            updateOrder(key);
        if (!filedData.empty())
            store(filedData); //store the leftovers by order
        else
            remove(filedCachePath.c_str());
    }
    bool load(string key) {
        bool loaded = false;
        ofstream fout(TEMP_FILE, ios::app);
        string first, second;
        string value;
        if (fout.is_open()) {
            ifstream fin(filedCachePath);
            if (fin.is_open()) {
                while (fin >> first >> second) {
                    if (first != key) {
                        fout << first << " " << second << endl;
                    } else {
                       value = second;
                        loaded = true;
                    }
                }
                fin.close();
            }
            fout.close();
            rename(TEMP_FILE, filedCachePath.c_str());
            if (loaded)
                storeLocaly(key, value);
        }
        return loaded;
    }
};


#endif //GSERVER_FILECACHEMANAGER_H
