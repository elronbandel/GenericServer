#include <iostream>
#include <string>
#include "Solver.h"
#include "StringReverser.h"
#include "SearchSolver.h"
#include "MatrixGraph.h"
#include "MatrixCreator.h"
#include "ISearcher.h"
#include "BFS.h"
#include "DFS.h"
#include "BestFirstSearch.h"
#include <ctime>
#include <cstdlib>

using std::cout;
using std::string;
using std::rand;

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    vector<State<string> *> path;
    string row;
    vector<string> rows;
    ISearcher<vector<State<string> *>, string> *searcher = new DFS<vector<State<string> *>, string>();
    Solver<Searchable<string>, vector<State<string> *>> *solver =
            new SearchSolver<Searchable<string>, vector<State<string> *>, string>(searcher);
    int sum = 0;
    for (int i = 1; i <= 25; i++) {
        row += to_string(i) + ",";
        if (i % 5 == 0) {
            rows.push_back(row);
            row = "";
        }
    }
    Searchable<string> *searchable = MatrixCreator<string>::create(rows, "0,0", "4,4");
    path = solver->solve(searchable);
    for (auto &i : path) {
        sum+= i->getCost();
        cout << (string) *i << endl;
    }
    cout << "this is the total cost: " << sum << endl;
    return 0;
}