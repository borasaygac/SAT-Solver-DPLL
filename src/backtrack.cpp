#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "../include/cnf.hpp"

void backtrack() {
    btc++;
    backtrackFlag = 0;
    //std::cout << "Intro backtrack\n";
    while (!assig.empty() && vars[assig.top()].forced) {  // until the last branching variable.
        int toUnassign = assig.top();
        //printf("Unassigned %i\n", toUnassign);
        //std::cout << "Unassigned " << toUnassign << "\n";
        updateBacktrack(toUnassign);
        vars[toUnassign].val = FREE;
        vars[toUnassign].forced = false;

        assig.pop();
        //  std::cout << "Removed literal " << toUnassign << " from assig stack \n";
    }

    // clear unit queue
    while (!unitQueue.empty()) {
        // std::cout << "Element to be popped from queue: " << unitQueue.front() << "\n";
        vars[std::abs(unitQueue.front())].enqueued = false;
        unitQueue.pop();
    }

    // TODO
    while (!pureLitQueue.empty()) {
        vars[std::abs(pureLitQueue.front())].enqueued = false;
        pureLitQueue.pop();
    }

    if (assig.empty()) {
        // UNSAT
        pthread_exit((void *)1);
    }  

    // Most recent branching variable
    int b = assig.top();
    updateBacktrack(b);
    vars[b].forced = true;
    
    // Assign negated val
    vars[b].val = Assig(int(2 - std::pow(2.0, vars[b].val)));
    //std::cout << "New branch var" << b << ", OLD: " << oldval << ", NEW: " << vars[b].val << "\n";
    curVar = b;
    update(b);
    propagate();
}