#include "../include/cnf.hpp"

void* dpll(void* arg) {
    // TODO: We should implement the more optimised appproach of checking the satisfaction of every clause
    while (true) {
        unitPropagate();

        chooseLiteral();

        std::cout << "Current Var :" << curVar << " and current value " << vars[curVar].getValue() << '\n';

        std::cout << "queue size= " << unitQueue.size() << '\n';
    }
}

void unitPropagate() {
    int unitLiteral;
    while (!unitQueue.empty()) {
        unitLiteral = unitQueue.front();
        std::cout << "current queue elm= " << unitLiteral << "\n";
        unitQueue.pop();

        vars[std::abs(unitLiteral)].forced = true;
        (unitLiteral > 0) ? vars[std::abs(unitLiteral)].setValue(TRUE) : vars[std::abs(unitLiteral)].setValue(FALSE);
        assig.push(std::abs(unitLiteral));
        std::cout << "UP variable " << std::abs(unitLiteral) << " set to " << vars[std::abs(unitLiteral)].getValue()
                  << "\n";

        updateWatchedLiterals(std::abs(unitLiteral));
    }
}

void updateWatchedLiterals(int assertedVar) {
    // watched literals have to point to unassigned or to true evaluating variables

    std::cout << "UPDATING FOR " << assertedVar << "!\n";
    std::set<int> watched;
    if (vars[assertedVar].getValue() == TRUE) {
        watched = vars[assertedVar].neg_watched;
    }

    else {
        watched = vars[assertedVar].pos_watched;
    }

    std::set<int>::iterator clauseIndex;
    for (clauseIndex = watched.begin(); clauseIndex != watched.end(); ++clauseIndex) {
        // TODO: We need to make reference?
        Clause* clause = &cnf[*clauseIndex];
        clause->sat = true;

        int* pointerToMove = std::abs(clause->literals[clause->w1]) == assertedVar ? &clause->w1 : &clause->w2;

        int otherPointer = clause->w1 + clause->w2 - *pointerToMove;

        for (int i = 0; i < clause->literals.size(); i++) {
            // assign as the new pointer a literal that evaluates to true and is not the other watched literal
            if (evaluateLiteral(clause->literals[i]) && i != otherPointer) {
                *(pointerToMove) = i;

                // Remove the current link from assertedVar to the clause
                watched.erase(clauseIndex);

                clause->literals[*pointerToMove] > 0
                    ? vars[std::abs(clause->literals[*pointerToMove])].pos_watched.insert(*clauseIndex)
                    : vars[std::abs(clause->literals[*pointerToMove])].neg_watched.insert(*clauseIndex);

                break;
            }

            // Search for a distinct new pointer unsuccessful, try UP on otherPointer else backtrack
            if (i + 1 == clause->literals.size()) {
                if (evaluateLiteral(clause->literals[otherPointer])) {
                    printf("Push %i on unit queue\n", clause->literals[otherPointer]);
                    unitQueue.push(clause->literals[otherPointer]);
                } else {
                    printf("INIT BACKTRACK!\n");
                    printf("(w1, assig): (%i, %i), (w2, assig): (%i, %i), size: %i \n",
                           clause->literals[*pointerToMove], evaluateLiteral(clause->literals[*pointerToMove]),
                           clause->literals[otherPointer], evaluateLiteral(clause->literals[otherPointer]),
                           clause->literals.size());
                    backtrack();  // signal UNSAT
                }
            }
        }
    }
}

bool evaluateLiteral(int literal) {
    if (vars[std::abs(literal)].getValue() == FREE) return true;

    if (vars[std::abs(literal)].getValue() == TRUE && literal > 0) return true;

    if (vars[std::abs(literal)].getValue() == FALSE && literal < 0) return true;

    return false;
}
