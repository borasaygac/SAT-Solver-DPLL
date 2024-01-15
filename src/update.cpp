#include "../include/cnf.hpp"

void update(int assertedVar) {
    pthread_testcancel();
    // verifyModel();

    // std::cout << "asserted var " << assertedVar << "\n";

    // std::cout << "[";
    // for (int i = 1; i < numOfVars; i++) {
    //     int value;
    //     if (vars[i].val == FREE) value = 0;
    //     if (vars[i].val == TRUE) value = i;
    //     if (vars[i].val == FALSE) value = -i;

    //     std::cout << value << ", ";
    // }
    // int value;
    // if (vars[numOfVars].val == FREE) value = 0;
    // if (vars[numOfVars].val == TRUE) value = numOfVars;
    // if (vars[numOfVars].val == FALSE) value = -numOfVars;
    // std::cout << value;
    // std::cout << "]"
    //           << "\n";

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
    // std::cout << "asserted var " << assertedVar << " and value" << vars[assertedVar].val << "\n";
    // std::cout << "Is " << assertedVar << " branching or forced?" << "Forced: " << vars[assertedVar].forced << "\n";

    // While clauses to mark satisfied are unsatisfied, mark satisfied and
    // erase all references of the literals occuring in the clause, since it can be disregarded
    for (clauseIndex = copy.begin(); clauseIndex != copy.end(); ++clauseIndex) {
        // unneccesary
        // if (clauses[*clauseIndex].sat != 0) continue;
        Clause* clause = &clauses[*clauseIndex];
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

                if (vars[std::abs(clause->literals[i])].pos_occ.size() == 0 &&
                    vars[std::abs(clause->literals[i])].neg_occ.size() > 0) {
                    // for (int i = 1; i <= numOfClauses; i++) {
                    //     if (clauses[i].sat != 0) continue;
                    //     for (int j = 0; j < clauses[i].literals.size(); j++) {
                    //         if (evaluateLiteral(clauses[i].literals[j])) printf("%i ", clauses[i].literals[j]);
                    //     }
                    //     printf("\n");
                    // }
                    // printf("PURELIT FOUND: %i\n", -std::abs(clause->literals[i]));
                    toPropagate.push(-std::abs(clause->literals[i]));
                    vars[std::abs(clause->literals[i])].enqueued = true;
                }
                if (vars[std::abs(clause->literals[i])].neg_occ.size() == 0 &&
                    vars[std::abs(clause->literals[i])].pos_occ.size() > 0) {
                    // for (int i = 1; i <= numOfClauses; i++) {
                    //     if (clauses[i].sat != 0) continue;
                    //     for (int j = 0; j < clauses[i].literals.size(); j++) {
                    //         if (evaluateLiteral(clauses[i].literals[j])) printf("%i ", clauses[i].literals[j]);
                    //     }
                    //     printf("\n");
                    // }
                    // printf("PURELIT FOUND: %i\n", std::abs(clause->literals[i]));
                    toPropagate.push(std::abs(clause->literals[i]));
                    vars[std::abs(clause->literals[i])].enqueued = true;
                }
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
        clauses[*clauseIndex2].active--;
        if (clauses[*clauseIndex2].sat != 0) continue;
        Clause* clause = &clauses[*clauseIndex2];
        // std::cout << "decremented clause " << *clauseIndex2 << "\nand the active number " << clauses[*clauseIndex2].active <<
        // "\n";
        //  printf("decremented clause %i\n and the anctive number %i,\n", *clauseIndex2, clause->active);
        if (clause->active == 0) {
            // printf("Conflict in clause %i,\n", *clauseIndex2);
            // std::cout << "Conflict in clause " << *clauseIndex2 << "\n";
            backtrackFlag = true;
            // return;
        }
        if (clauses[*clauseIndex2].active == 1) {
            for (int i = 0; i < clause->literals.size(); i++) {
                if (vars[std::abs(clause->literals[i])].val == FREE && !vars[std::abs(clause->literals[i])].enqueued) {
                    toPropagate.push(clause->literals[i]);
                    // printf("UNIT FOUND: %i\n", clause->literals[i]);

                    vars[std::abs(clause->literals[i])].enqueued = true;
                }
            }
        }
    }
    if (backtrackFlag) {
        backtrack();
    }

    // All clauses are sat and there are no more pure/unit literals threatenings that? => SAT!
    if (toPropagate.empty() && numOfSatClauses == numOfClauses) {
        finished = true;
        pthread_exit(0);
    }
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
    // dynOccurences = (vars[unassignedVar].val == TRUE) ? &vars[unassignedVar].pos_occ : &vars[unassignedVar].neg_occ;

    std::set<int>::iterator clauseIndex2;
    std::set<int> copy2 = *clausesToIncrement;

    for (clauseIndex2 = copy2.begin(); clauseIndex2 != copy2.end(); ++clauseIndex2) clauses[*clauseIndex2].active++;

    std::set<int>::iterator clauseIndex;
    std::set<int> copy = *allOccurences;

    // if clause of dynOccurencies is sat by unassignedVar,
    // restore the previous literal references
    for (clauseIndex = copy.begin(); clauseIndex != copy.end(); ++clauseIndex) {
        if (clauses[*clauseIndex].sat != unassignedVar) continue;

        Clause* clause = &clauses[*clauseIndex];

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