#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "../include/cnf.hpp"

void backtrack() {
    backtrackFlag = false;
    btc++;
    // unassign until the last branching variable.
    while (!assig.empty() && vars[assig.top()].forced) {
        int toUnassign = assig.top();
        updateBacktrack(toUnassign);
        vars[toUnassign].val = FREE;
        vars[toUnassign].forced = false;

        assig.pop();
    }

    // clear queue of unit and pure literals
    while (!toPropagate.empty()) {
        vars[std::abs(toPropagate.front())].enqueued = false;
        toPropagate.pop();
    }

    // UNSAT
    if (assig.empty()) {
        finished = true;
        pthread_exit((void *)1);
    }

    // handle most recent branching variable
    int b = assig.top();
    updateBacktrack(b);
    vars[b].forced = true;

    // assign negated val
    vars[b].val = Assig(int(2 - std::pow(2.0, vars[b].val)));
    curVar = b;
    update(b);
    propagate();
}