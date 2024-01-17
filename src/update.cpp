#include "../include/cnf.hpp"

void update(int assertedVar) {
    // clauses where assertedVar evaluates to FALSE
    std::set<int>* clausesToUpdate;

    // clauses where assertedVar evaluates to TRUE
    std::set<int>* clausesToMarkSatisfied;

    clausesToUpdate = (vars[assertedVar].val == TRUE) ? &vars[assertedVar].static_neg_occ : &vars[assertedVar].static_pos_occ;

    if (vars[assertedVar].val == TRUE) {
        clausesToMarkSatisfied = &vars[assertedVar].pos_occ;
    } else {
        clausesToMarkSatisfied = &vars[assertedVar].neg_occ;
        assertedVar = -assertedVar;
    }

    std::set<int>::iterator clauseIndex;
    std::set<int> copy = *clausesToMarkSatisfied;

    // While clauses to mark satisfied are unsatisfied, mark satisfied and
    // erase all references of the literals occuring in the clause, since it can be disregarded
    for (clauseIndex = copy.begin(); clauseIndex != copy.end(); ++clauseIndex) {
        Clause* clause = &clauses[*clauseIndex];
        clause->sat = assertedVar;

        for (int i = 0; i < clause->literals.size(); i++) {
            auto var = &vars[std::abs(clause->literals[i])];

            clause->literals[i] > 0 ? (*var).pos_occ.erase(*clauseIndex) : (*var).neg_occ.erase(*clauseIndex);

            // detect pure literals
            if ((*var).val == FREE && !(*var).enqueued) {
                if ((*var).pos_occ.size() == 0 && (*var).neg_occ.size() > 0) {
                    toPropagate.push(-std::abs(clause->literals[i]));
                    (*var).enqueued = true;
                }
                if ((*var).neg_occ.size() == 0 && (*var).pos_occ.size() > 0) {
                    toPropagate.push(std::abs(clause->literals[i]));
                    (*var).enqueued = true;
                }
            }
        }
        numOfSatClauses++;
    }

    // While clauses to update have more than one literal, decrement act and identify unit literals
    // or conflicts
    std::set<int>::iterator clauseIndex2;
    std::set<int> copy2 = *clausesToUpdate;
    
    for (clauseIndex2 = copy2.begin(); clauseIndex2 != copy2.end(); ++clauseIndex2) {
        clauses[*clauseIndex2].active--;
        if (clauses[*clauseIndex2].sat != 0) continue;
        Clause* clause = &clauses[*clauseIndex2];

        if (clause->active == 0) {
            backtrackFlag = true;
        }
        if (clauses[*clauseIndex2].active == 1) {
            for (int i = 0; i < clause->literals.size(); i++) {
                if (vars[std::abs(clause->literals[i])].val == FREE && !vars[std::abs(clause->literals[i])].enqueued) {
                    toPropagate.push(clause->literals[i]);
                    vars[std::abs(clause->literals[i])].enqueued = true;
                }
            }
        }
    }

    if (backtrackFlag) backtrack();

    // All clauses are sat and there are no more pure/unit literals threatening that? => SAT!
    if (toPropagate.empty() && numOfSatClauses == numOfClauses) pthread_exit(0);
}

void updateBacktrack(int unassignedVar) {
    // clauses where assertedVar evaluates to FALSE
    std::set<int>* clausesToIncrement;

    // all clauses the unassignedVar appears in (including satisfied clauses) and evaluates to TRUE
    std::set<int>* allOccurences;

    allOccurences = (vars[unassignedVar].val == TRUE) ? &vars[unassignedVar].static_pos_occ : &vars[unassignedVar].static_neg_occ;

    if (vars[unassignedVar].val == TRUE) {
        clausesToIncrement = &vars[unassignedVar].static_neg_occ;
    } else {
        clausesToIncrement = &vars[unassignedVar].static_pos_occ;
        unassignedVar = -unassignedVar;
    }

    std::set<int>::iterator clauseIndex2;
    std::set<int> copy2 = *clausesToIncrement;

    for (clauseIndex2 = copy2.begin(); clauseIndex2 != copy2.end(); ++clauseIndex2) clauses[*clauseIndex2].active++;

    std::set<int>::iterator clauseIndex;
    std::set<int> copy = *allOccurences;

    // restore the previously deleted clauses and its var references
    for (clauseIndex = copy.begin(); clauseIndex != copy.end(); ++clauseIndex) {
        if (clauses[*clauseIndex].sat != unassignedVar) continue;

        Clause* clause = &clauses[*clauseIndex];

        clause->sat = 0;

        for (int i = 0; i < clause->literals.size(); i++) {
            clause->literals[i] > 0 ? vars[std::abs(clause->literals[i])].pos_occ.insert(*clauseIndex)
                                    : vars[std::abs(clause->literals[i])].neg_occ.insert(*clauseIndex);
        }
        numOfSatClauses--;
    }
}