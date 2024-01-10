#include "../include/cnf.hpp"

void updateCNF(int assertedVar) {
    // clauses where assertedVar evaluates to FALSE
    std::set<int>* clausesToUpdate;

    // clauses where assertedVar evaluates to TRUE
    std::set<int>* clausesToMarkSatisfied;

    clausesToUpdate = (vars[assertedVar].val == TRUE) ? &vars[assertedVar].neg_occ : &vars[assertedVar].pos_occ;

    clausesToMarkSatisfied = (vars[assertedVar].val == TRUE) ? &vars[assertedVar].pos_occ : &vars[assertedVar].neg_occ;

    std::set<int>::iterator clauseIndex;
    std::set<int> copy = *clausesToMarkSatisfied;
    printf("asserted var %i and value %i\n", assertedVar, vars[assertedVar].val);
    printf("Is %i branching or forced? Forced: %i \n", assertedVar, vars[assertedVar].forced);

    // While clauses to mark satisfied are unsatisfied, mark satisfied and
    // erase all references of the literals occuring in the clause, since it can be disregarded
    for (clauseIndex = copy.begin(); clauseIndex != copy.end(); ++clauseIndex) {
        if (cnf[*clauseIndex].sat > 0) continue;
        Clause* clause = &cnf[*clauseIndex];
        clause->sat = assertedVar;
        printf("mark clause sat %i\n", *clauseIndex);
        for (int i = 0; i < clause->literals.size(); i++) {
            clause->literals[i] > 0 ? vars[std::abs(clause->literals[i])].pos_occ.erase(*clauseIndex)
                                    : vars[std::abs(clause->literals[i])].neg_occ.erase(*clauseIndex);

            // if (vars[std::abs(clause->literals[i])].val == FREE) {
            //     if (vars[std::abs(clause->literals[i])].pos_occ.size() == 0 &&
            //         vars[std::abs(clause->literals[i])].neg_occ.size() > 0)
            //         pureLitQueue.push(clause->literals[i]);

            //     if (vars[std::abs(clause->literals[i])].neg_occ.size() == 0 &&
            //         vars[std::abs(clause->literals[i])].pos_occ.size() > 0)
            //         pureLitQueue.push(clause->literals[i]);
            // }
            // printf("SIZE STATIC: %i and DYN: %i\n", vars[std::abs(clause->literals[i])].static_pos_occ.size(),
            //        vars[std::abs(clause->literals[i])].pos_occ.size());

            // printf("SIZE STATIC: %i and DYN: %i\n", vars[std::abs(clause->literals[i])].static_neg_occ.size(),
            //        vars[std::abs(clause->literals[i])].neg_occ.size());
        }
        numOfSatClauses++;
    }

    // While clauses to update have more than one literal, decrement act, else also start unitProp
    // or report conflict
    std::set<int>::iterator clauseIndex2;
    std::set<int> copy2 = *clausesToUpdate;
    for (clauseIndex2 = copy2.begin(); clauseIndex2 != copy2.end(); ++clauseIndex2) {
        if (cnf[*clauseIndex2].sat > 0) continue;
        Clause* clause = &cnf[*clauseIndex2];
        clause->active--;
        printf("decremented clause %i\n and the anctive number %i,\n", *clauseIndex2, clause->active);
        if (clause->active == 0) {
            printf("Conflict in clause %i,\n", *clauseIndex2);
            backtrack();
            return;
        }
        if (clause->active == 1) {
            for (int i = 0; i < clause->literals.size(); i++) {
                if (vars[std::abs(clause->literals[i])].val == FREE && vars[std::abs(clause->literals[i])].enqueued == false) {
                    unitQueue.push(clause->literals[i]);
                    printf("pushed elem %i\n", clause->literals[i]);
                    vars[std::abs(clause->literals[i])].enqueued = true;
                }
            }
        }
    }
}

void updateBacktrack(int unassignedVar) {
    // clauses where assertedVar evaluates to FALSE
    std::set<int>* clausesToIncrement;

    // all clauses the unassignedVar appears in (including satisfied clauses) and evaluates to TRUE
    std::set<int>* allOccurences;

    // allOccurences without satisfied clauses
    std::set<int>* dynOccurences;

    clausesToIncrement = (vars[unassignedVar].val == TRUE) ? &vars[unassignedVar].neg_occ : &vars[unassignedVar].pos_occ;

    allOccurences = (vars[unassignedVar].val == TRUE) ? &vars[unassignedVar].static_pos_occ : &vars[unassignedVar].static_neg_occ;

    dynOccurences = (vars[unassignedVar].val == TRUE) ? &vars[unassignedVar].pos_occ : &vars[unassignedVar].neg_occ;

    std::set<int>::iterator clauseIndex;
    std::set<int> copy = *allOccurences;

    // if clause of dynOccurencies is sat by unassignedVar,
    // resstore the previous literal references
    for (clauseIndex = copy.begin(); clauseIndex != copy.end(); ++clauseIndex) {
        if (cnf[*clauseIndex].sat != unassignedVar) continue;

        Clause* clause = &cnf[*clauseIndex];

        clause->sat = 0;

        // Assig: 1 -> true, 2->false, 3->true
        // 1, 2, 3 sat by 1
        // Look if other literal satisfies the clause
        // ?MAYBE OTHER LIT SATSFIES OR MAYBE NOT DUE TO ASSIG ORDER?

        for (int i = 0; i < clause->literals.size(); i++) {
            clause->literals[i] > 0 ? vars[std::abs(clause->literals[i])].pos_occ.insert(*clauseIndex)
                                    : vars[std::abs(clause->literals[i])].neg_occ.insert(*clauseIndex);
        }
        printf("\nRestored clause %i for unassigned %i\n", *clauseIndex, unassignedVar);
        numOfSatClauses--;
    }

    std::set<int>::iterator clauseIndex2;
    std::set<int> copy2 = *clausesToIncrement;

    for (clauseIndex2 = copy2.begin(); clauseIndex2 != copy2.end(); ++clauseIndex2) {
        cnf[*clauseIndex2].active++;
    }
}

bool evaluateLiteral(int literal) {
    if (vars[std::abs(literal)].val == FREE) return true;

    if (vars[std::abs(literal)].val == TRUE && literal > 0) return true;

    if (vars[std::abs(literal)].val == FALSE && literal < 0) return true;

    return false;
}