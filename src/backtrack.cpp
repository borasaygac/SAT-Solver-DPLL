#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "../include/cnf.hpp"

bool backtrack() {
    while (!assig.empty() && vars[assig.top()].forced) {  // until the last branching variable.
        int toUnassign = assig.top();
        vars[toUnassign].setValue(FREE);
        assig.pop();
        printf("Removed literal %i from assig stack \n", toUnassign);
    }

    if (assig.empty()) {
        return false;
    }  // UNSAT
    
    // clear unit queue
    while (!unitQueue.empty()) unitQueue.pop();
    // alternatively: unitQueue = std::queue<int>();
    if (unitQueue.empty()) printf("EMPTY!\n");
    // Most recent branching variable
    int b = assig.top();
    int oldval = vars[b].getValue();
    // Assign negated val
    vars[b].forced = true;
    numOfUnassigned++;
    vars[b].setValue(Assig(int(2 - std::pow(2.0, vars[b].getValue()))));
    printf("New branch var %i, OLD: %i, NEW: %i \n", b, oldval, vars[b].getValue());
    curVar = b;
    updateWatchedLiterals(b);
    return true;
}