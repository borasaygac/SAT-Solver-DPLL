#include "../include/cnf.hpp"

void* dpll(void* arg) {
    // TODO: We should implement the more optimised appproach of checking the satisfaction of every clause
    while (true) {
        unitPropagate();
        if (unitQueue.empty() && numOfUnassigned < 1) {
            // std::cout << "VORBEII!! \n";

            pthread_exit(0);
        }
        chooseLiteral();

        // std::cout << "Current Var :" << curVar << " and current value " << vars[curVar].getValue() << '\n';

        // std::cout << "queue size= " << unitQueue.size() << '\n';
    }
}

void unitPropagate() {
    int unitLiteral;
    while (!unitQueue.empty()) {
        unitLiteral = unitQueue.front();
        std::cout << "current queue elm= " << unitLiteral << "\n";
        unitQueue.pop();
        vars[std::abs(unitLiteral)].enqueued = false;
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
    std::set<int>* clausesToUpdate;

    clausesToUpdate = (vars[assertedVar].getValue() == TRUE) ? &vars[assertedVar].neg_watched : &vars[assertedVar].pos_watched;
    // std::cout << "UPDATE CLAUSES SIZE: " << clausesToUpdate->size() << "!\n";
    std::set<int>::iterator clauseIndex;
    std::set<int> copy = *clausesToUpdate;
    for (clauseIndex = copy.begin(); clauseIndex != copy.end(); ++clauseIndex) {
        Clause* clause = &cnf[*clauseIndex];
        std::cout << "clauseIndex " << *clauseIndex << ": ";
        for (int i = 0; i < clause->literals.size(); i++) {
            std::cout << clause->literals[i] << " ";
        }
        std::cout << "\n ";
        int* pointerToMove = std::abs(clause->literals[clause->w1]) == assertedVar ? &clause->w1 : &clause->w2;

        std::cout << "POINTERTOMOVE " << *pointerToMove << "!\n";

        int otherPointer = clause->w1 + clause->w2 - *pointerToMove;

        std::cout << "OTHERPOINTER  " << otherPointer << "!\n";

        
        for (int i = 0; i < clause->literals.size(); i++) {
            // assign as the new pointer a literal that evaluates to true and is not the other watched literal
            if (i != otherPointer && evaluateLiteral(clause->literals[i])) {
                *(pointerToMove) = i;

                // Remove the reference from assertedVar to the clause
                std::cout << "REMOVING clause " << *clauseIndex << " from " << assertedVar << "!\n";

                std::cout << "Set elements before: ";
                for (const auto& element : *clausesToUpdate) {
                    std::cout << element << " ";
                }
                std::cout << std::endl;

                clausesToUpdate->erase(*clauseIndex);

                std::cout << "Set elements after: ";
                for (const auto& element : *clausesToUpdate) {
                    std::cout << element << " ";
                }
                std::cout << std::endl;

                std::cout << "Adding clause " << *clauseIndex << " to " << std::abs(clause->literals[*pointerToMove]) << "!\n";
                // Add a reference from new found watched literal to the clause
                clause->literals[*pointerToMove] > 0
                    ? vars[std::abs(clause->literals[*pointerToMove])].pos_watched.insert(*clauseIndex)
                    : vars[std::abs(clause->literals[*pointerToMove])].neg_watched.insert(*clauseIndex);

                /* if ((!evaluateLiteral((clause->literals[otherPointer])) || vars[std::abs(clause->literals[otherPointer])].getValue() != FREE) &&
                    !vars[std::abs(clause->literals[*pointerToMove])].enqueued && vars[std::abs(clause->literals[*pointerToMove])].getValue() == FREE) {
                        unitQueue.push(clause->literals[*pointerToMove]);
                        std::cout << "Push " << clause->literals[*pointerToMove] << " on unit queue\n";
                    } */
                    
                break;
            }
            // Search for a distinct new pointer unsuccessful, try UP on otherPointer else backtrack
            if (i + 1 == clause->literals.size()) {
                if (vars[std::abs(clause->literals[otherPointer])].getValue() == FREE &&
                    !vars[std::abs(clause->literals[otherPointer])].enqueued) {
                    std::cout << "Push " << clause->literals[otherPointer] << " on unit queue\n";
                    vars[std::abs(clause->literals[otherPointer])].enqueued = true;
                    unitQueue.push(clause->literals[otherPointer]);
                } else {
                    if (!evaluateLiteral(clause->literals[otherPointer])) {
                        std::cout << "INIT BACKTRACK!\n";
                        std::cout << "(w1, assig): (" << clause->literals[*pointerToMove]
                                  << evaluateLiteral(clause->literals[*pointerToMove]) << ") (w2, assig): ("
                                  << clause->literals[otherPointer] << evaluateLiteral(clause->literals[otherPointer])
                                  << "), size: " << clause->literals.size() << "\n";
                        backtrack();
                        return;
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
