#include <iostream>
#include <string>
#include <vector>

#include "../include/cnf.hpp"

bool checkAllClauses() {
    int count = 0;
    for (int i = 1; i <= numOfClauses; i++) {
        if (evaluateLiteral(cnf[i].literals[cnf[i].w1]) || evaluateLiteral(cnf[i].literals[cnf[i].w2])) {
            count++;
        }
    }
    if (count == numOfClauses) {
        std::cout << "All clauses satisfied!"
                  << "\n";
        std::cout << "Model: ";

    } else {
        std::cout << "Not all clauses satisfied. Number of satisfied clauses is " << count << " != " << numOfClauses
                  << "\n";
    }
    std::cout << "[";
    for (int i = 1; i < numOfVars; i++) {
        int val;
        if (variables[i].val == FREE) val = 1000;
        if (variables[i].val == TRUE) val = i;
        if (variables[i].val == FALSE) val = -i;

        std::cout << val << ", ";
    }
    int val;
    if (variables[numOfVars].val == FREE) val = 1000;
    if (variables[numOfVars].val == TRUE) val = numOfVars;
    if (variables[numOfVars].val == FALSE) val = -numOfVars;
    std::cout << val;
    std::cout << "]";
    return false;
}