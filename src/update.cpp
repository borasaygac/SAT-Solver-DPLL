#include "../include/cnf.hpp"

void updateCNF(int assertedVar) {
    // verifyModel();

    /*std::cout << "asserted var " << assertedVar << "\n";

    std::cout << "[";
    for (int i = 1; i < numOfVars; i++) {
        int value;
        if (vars[i].val == FREE) value = 0;
        if (vars[i].val == TRUE) value = i;
        if (vars[i].val == FALSE) value = -i;

        std::cout << value << ", ";
    }
    int value;
    if (vars[numOfVars].val == FREE) value = 0;
    if (vars[numOfVars].val == TRUE) value = numOfVars;
    if (vars[numOfVars].val == FALSE) value = -numOfVars;
    std::cout << value;
    std::cout << "]"
              << "\n";*/

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
    // printf("asserted var %i and value %i\n", assertedVar, vars[assertedVar].val);
    // printf("Is %i branching or forced? Forced: %i \n", assertedVar, vars[assertedVar].forced);
    // std::cout << "asserted var " << assertedVar << " and value" <<  vars[assertedVar].val << "\n";
    // std::cout << "Is " << assertedVar << " branching or forced?" << "Forced: " << vars[assertedVar].forced << "\n";

    // While clauses to mark satisfied are unsatisfied, mark satisfied and
    // erase all references of the literals occuring in the clause, since it can be disregarded
    for (clauseIndex = copy.begin(); clauseIndex != copy.end(); ++clauseIndex) {
        // unneccesary
        // if (cnf[*clauseIndex].sat != 0) continue;
        Clause* clause = &cnf[*clauseIndex];
        clause->sat = assertedVar;
        // printf("mark clause sat %i\n", *clauseIndex);
        // std::cout <<"mark clause sat " << *clauseIndex << "\n";
        for (int i = 0; i < clause->literals.size(); i++) {
            clause->literals[i] > 0 ? vars[std::abs(clause->literals[i])].pos_occ.erase(*clauseIndex)
                                    : vars[std::abs(clause->literals[i])].neg_occ.erase(*clauseIndex);

            if (vars[std::abs(clause->literals[i])].val == FREE && !vars[std::abs(clause->literals[i])].enqueued) {
                // // if (vars[std::abs(assertedVar)].pos_occ.size() * vars[std::abs(assertedVar)].neg_occ.size() == 0 &&
                // //     vars[std::abs(assertedVar)].pos_occ.size() + vars[std::abs(assertedVar)].neg_occ.size() >= 1)
                // //     pureLitQueue.push(assertedVar);

                // if (vars[std::abs(clause->literals[i])].pos_occ.size() == 0 &&
                //     vars[std::abs(clause->literals[i])].neg_occ.size() > 0) {
                //     printf("SI %i", -std::abs(clause->literals[i]));
                //     pureLitQueue.push(-std::abs(clause->literals[i]));
                //     vars[std::abs(clause->literals[i])].enqueued = true;
                // }
                // if (vars[std::abs(clause->literals[i])].neg_occ.size() == 0 &&
                //     vars[std::abs(clause->literals[i])].pos_occ.size() > 0) {
                //     pureLitQueue.push(std::abs(clause->literals[i]));
                //     vars[std::abs(clause->literals[i])].enqueued = true;
                // }
            }
        }

        numOfSatClauses++;
        // std::cout << "Num of sat clauses " << numOfSatClauses << "\n";
        // std::cout << "and the unit queue size " << unitQueue.size() << "\n";
        // std::cout << "and the assig stack size " << assig.size() << "\n";
    }

    // While clauses to update have more than one literal, decrement act, else also start unitProp
    // or report conflict
    std::set<int>::iterator clauseIndex2;
    std::set<int> copy2 = *clausesToUpdate;
    // std::cout << "size of clauses to update "<< clausesToUpdate->size() << "\n";
    for (clauseIndex2 = copy2.begin(); clauseIndex2 != copy2.end(); ++clauseIndex2) {
        cnf[*clauseIndex2].active--;
        if (cnf[*clauseIndex2].sat != 0) continue;
        Clause* clause = &cnf[*clauseIndex2];
        // std::cout << "decremented clause " << *clauseIndex2 << "\nand the active number " << cnf[*clauseIndex2].active << "\n";
        //  printf("decremented clause %i\n and the anctive number %i,\n", *clauseIndex2, clause->active);
        if (clause->active == 0) {
            // printf("Conflict in clause %i,\n", *clauseIndex2);
            // std::cout << "Conflict in clause " << *clauseIndex2 << "\n";
            backtrackFlag = 1;
            // return;
        }
        if (cnf[*clauseIndex2].active == 1) {
            for (int i = 0; i < clause->literals.size(); i++) {
                if (vars[std::abs(clause->literals[i])].val == FREE && !vars[std::abs(clause->literals[i])].enqueued) {
                    unitQueue.push(clause->literals[i]);
                    // printf("pushed elem %i\n", clause->literals[i]);
                    // std::cout << "pushed elem " << clause->literals[i] << "\n";
                    vars[std::abs(clause->literals[i])].enqueued = true;
                }
            }
        }
    }
    /*std::cout << "[";
    for (int i = 1; i < numOfClauses; i++) {
        int value = cnf[i].active;

        std::cout << value << ", ";
    }
    int activeval = cnf[numOfClauses].active;

    std::cout << activeval;
    std::cout << "]\n";*/
    if (backtrackFlag == 1) {
        backtrack();
    }
}

void updateBacktrack(int unassignedVar) {
    // clauses where assertedVar evaluates to FALSE
    std::set<int>* clausesToIncrement;

    // all clauses the unassignedVar appears in (including satisfied clauses) and evaluates to TRUE
    std::set<int>* allOccurences;

    // allOccurences without satisfied clauses
    std::set<int>* dynOccurences;

    allOccurences = (vars[unassignedVar].val == TRUE) ? &vars[unassignedVar].static_pos_occ : &vars[unassignedVar].static_neg_occ;

    if (vars[unassignedVar].val == TRUE) {
        clausesToIncrement = &vars[unassignedVar].static_neg_occ;
    } else {
        clausesToIncrement = &vars[unassignedVar].static_pos_occ;
        unassignedVar = -unassignedVar;
    }
    // dynOccurences = (vars[unassignedVar].val == TRUE) ? &vars[unassignedVar].pos_occ : &vars[unassignedVar].neg_occ;

    std::set<int>::iterator clauseIndex2;
    std::set<int> copy2 = *clausesToIncrement;

    for (clauseIndex2 = copy2.begin(); clauseIndex2 != copy2.end(); ++clauseIndex2) {
        /* If the active == size, that means we haven't visited the clause yet and made no operations on it.
        Our current setup, takes all the reverse polarity occurances, regardless of whether we've made any
        operations on the clause. So either we change the ClausesToIncrement setup to only include the clauses
        that we've made operations on, or this if loop.
        */

        cnf[*clauseIndex2].active++;
    }

    std::set<int>::iterator clauseIndex;
    std::set<int> copy = *allOccurences;

    // if clause of dynOccurencies is sat by unassignedVar,
    // restore the previous literal references
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
        // printf("\nRestored clause %i for unassigned %i\n", *clauseIndex, unassignedVar);
        // std::cout << "\nRestored clause" << *clauseIndex << "for unassigned " << unassignedVar << "\n";
        numOfSatClauses--;
    }
}

bool evaluateLiteral(int literal) {
    if (vars[std::abs(literal)].val == FREE) return true;

    if (vars[std::abs(literal)].val == TRUE && literal > 0) return true;

    if (vars[std::abs(literal)].val == FALSE && literal < 0) return true;

    return false;
}
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