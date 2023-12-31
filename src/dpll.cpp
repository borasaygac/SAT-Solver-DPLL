#include "../include/cnf.hpp"

void dpll() {
    // TODO: We should implement the more optimised appproach of checking the satisfaction of every clause
    while (true) {
        unitPropagate();
        if (unitQueue.empty() && numOfUnassigned < 1) {
            std::cout << "VORBEII!! \n";

            pthread_exit(0);
        }
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
        std::cout << "UP variable " << std::abs(unitLiteral) << " set to " << vars[std::abs(unitLiteral)].getValue() << "\n";

        assig.push(std::abs(unitLiteral));

        updateWatchedLiterals(std::abs(unitLiteral));
    }
}

void updateWatchedLiterals(int assertedVar) {
    // watched literals have to point to unassigned or to true evaluating variables

    std::cout << "UPDATING FOR " << assertedVar << "!\n";
    std::set<int> clausesToUpdate;

    clausesToUpdate = (vars[assertedVar].getValue() == TRUE) ? vars[assertedVar].neg_watched : vars[assertedVar].pos_watched;
    std::cout << "UPDATE CLAUSES SIZE: " << clausesToUpdate.size() << "!\n";
    std::set<int>::iterator clauseIndex;
    for (clauseIndex = clausesToUpdate.begin(); clauseIndex != clausesToUpdate.end(); ++clauseIndex) {
        Clause* clause = &cnf[*clauseIndex];
        printf("clauseIndex %i: ", *clauseIndex);
        for (int i = 0; i < clause->literals.size(); i++) {
            printf("%i, ", clause->literals[i]);
        }
        printf("\n ");
        int* pointerToMove = std::abs(clause->literals[clause->w1]) == assertedVar ? &clause->w1 : &clause->w2;

        std::cout << "POINTERTOMOVE " << *pointerToMove << "!\n";

        int otherPointer = clause->w1 + clause->w2 - *pointerToMove;

        std::cout << "OTHERPOINTER  " << otherPointer << "!\n";

        for (int i = 0; i < clause->literals.size(); i++) {
            // assign as the new pointer a literal that evaluates to true and is not the other watched literal
            if (i != otherPointer && evaluateLiteral(clause->literals[i])) {
                *(pointerToMove) = i;

                // Remove the reference from assertedVar to the clause
                std::cout << "REMOVING  " << *clauseIndex << "from " << assertedVar << "!\n";

                clausesToUpdate.erase(*clauseIndex);

                // Add a reference from new found watched literal to the clause
                clause->literals[*pointerToMove] > 0
                    ? vars[std::abs(clause->literals[*pointerToMove])].pos_watched.insert(*clauseIndex)
                    : vars[std::abs(clause->literals[*pointerToMove])].neg_watched.insert(*clauseIndex);

                break;
            }
            // Search for a distinct new pointer unsuccessful, try UP on otherPointer else backtrack
            if (i + 1 == clause->literals.size()) {
                if (vars[std::abs(clause->literals[otherPointer])].getValue() == FREE) {
                    printf("Push %i on unit queue\n", clause->literals[otherPointer]);
                    unitQueue.push(clause->literals[otherPointer]);
                } else {
                    if (!evaluateLiteral(clause->literals[otherPointer])) {
                        printf("INIT BACKTRACK!\n");
                        printf("(w1, assig): (%i, %i), (w2, assig): (%i, %i), size: %i \n", clause->literals[*pointerToMove],
                               evaluateLiteral(clause->literals[*pointerToMove]), clause->literals[otherPointer],
                               evaluateLiteral(clause->literals[otherPointer]), clause->literals.size());
                        backtrack();
                    }
                }
            }
        }
        std::cout << "AFTER ALGO:POINTERTOMOVE " << *pointerToMove << "!\n";
    }
    std::cout << "\nFINISHED FOR " << assertedVar << "!\n\n ";
    // if (unitQueue.empty() && numOfUnassigned < 1) pthread_exit(0);
}

bool evaluateLiteral(int literal) {
    if (vars[std::abs(literal)].getValue() == FREE) return true;

    if (vars[std::abs(literal)].getValue() == TRUE && literal > 0) return true;

    if (vars[std::abs(literal)].getValue() == FALSE && literal < 0) return true;

    return false;
}
