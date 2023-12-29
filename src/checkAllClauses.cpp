#include <iostream>
#include <string>
#include <vector>

#include "../include/cnf.hpp"

bool checkAllClauses() {
    int count = 0;
    for (int i = 1; i <= numOfClauses; i++) {
        if (evaluateLiteral(cnf[i].literals[cnf[i].w1], false) || evaluateLiteral(cnf[i].literals[cnf[i].w2], false)) {
            count++;
        }
    }
    if (count == numOfClauses) {
        std::cout << "All clauses satisfied!"
                  << "\n";
        std::cout << "Model: ";

    } else {
        std::cout
            << "Not all clauses satisfied. Number of satisfied clauses is "
            << count << " != " << numOfClauses << "\n";
    }
    std::cout << "[";
    for (int i = 1; i < numOfVars; i++) {
        int val = variables[i].val == 0 ? -i : i;
        std::cout << val << ", ";
    }
    int val = variables[numOfVars].val == 0 ? -numOfVars : numOfVars;
    std::cout << val;
    std::cout << "]";
    return false;
}