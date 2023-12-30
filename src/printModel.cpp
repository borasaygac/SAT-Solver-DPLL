#include "../include/cnf.hpp"

bool printModel() {
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
        if (vars[i].getValue() == FREE) val = 0;
        if (vars[i].getValue() == TRUE) val = i;
        if (vars[i].getValue() == FALSE) val = -i;

        std::cout << val << ", ";
    }
    int val;
    if (vars[numOfVars].getValue() == FREE) val = 0;
    if (vars[numOfVars].getValue() == TRUE) val = numOfVars;
    if (vars[numOfVars].getValue() == FALSE) val = -numOfVars;
    std::cout << val;
    std::cout << "]";
    return false;
}