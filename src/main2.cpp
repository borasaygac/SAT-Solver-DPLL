#include <stdio.h>

#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "../include/cnf2.hpp"

int numOfVars;
int numOfClauses;
std::vector<Clause> cnf;
std::vector<Variable> variables;
std::queue<int> unitQueue;
int CurVar = 1;

int main(int argc, char *argv[]) {
    std::string filename = "DIMACS/test" + std::to_string(std::stoi(argv[1])) + ".cnf";

    parseDIMACS2(filename);
    std::cout << "Params: vars " << numOfVars << " and clauses " << numOfClauses << "\n";
    for (const auto &clause : cnf) {
        std::cout << "Clause: ";
        for (const auto &literal : clause.literals) {
            std::cout << literal << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 1; i < numOfClauses + 1; i++) {
        cnf[i].w1 = &(cnf[i].literals[0]);  // Assign the first and second watcher to
                                            // the first and second literal in clause.
        cnf[i].w2 = &(cnf[i].literals[1]);
        printf("%dth Clause: w1 = %d w2 = %d\n", i, *(cnf[i].w1), *(cnf[i].w2));
    }

    dpll();
    checkAllClauses();
    return 0;
}
