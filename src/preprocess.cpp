
#include "../include/cnf.hpp"

void preprocess() {
    if (heuristic == Heuristics::MOM) {
        for (int i = 1; i <= numOfClauses; i++) {
            if (clauses[i].active == minWidth) {
                minClauses.push(i);
            }
            minWidth = std::min(minWidth, clauses[i].active);
        }
    }

    // Find pure lits and assign them to pure lit queue
    for (int i = 1; i <= numOfVars; i++) {
        if (vars[i].static_neg_occ.size() == 0 && vars[i].static_pos_occ.size() > 0) {
            // std::cout << "Var no: " << i << " is a pure lit"
            //   << "\n"
            //   << std::flush;
            vars[std::abs(i)].enqueued = true;
            toPropagate.push(i);
        }
        if (vars[i].static_pos_occ.size() == 0 && vars[i].static_neg_occ.size() > 0) {
            // std::cout << "Var no: " << i << " is a pure lit"
            //   << "\n"
            //   << std::flush;
            vars[std::abs(i)].enqueued = true;
            toPropagate.push(-i);
            // TODO FOR LATER: Fix the queue structure
        }
    }
}