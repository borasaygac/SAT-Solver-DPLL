#include "../include/cnf.hpp"

void updateWatchedLiterals(int assertedVar) {
    // watched literals have to point to unassigned or to true evaluating variables

    // std::cout << "UPDATING FOR " << assertedVar << "!\n";
    std::set<int>* clausesToUpdatePointers;
    std::set<int>* clausesToMarkSatisfied;

    clausesToUpdatePointers =
        (vars[assertedVar].getValue() == TRUE) ? &vars[assertedVar].neg_watched : &vars[assertedVar].pos_watched;

    clausesToMarkSatisfied =
        (vars[assertedVar].getValue() == TRUE) ? &vars[assertedVar].pos_watched : &vars[assertedVar].neg_watched;

    std::set<int>::iterator clauseIndex;
    std::set<int> copy = *clausesToUpdatePointers;
    for (clauseIndex = copy.begin(); clauseIndex != copy.end(); ++clauseIndex) {
        Clause* clause = &cnf[*clauseIndex];
        // std::cout << "clauseIndex " << *clauseIndex << ": ";
        // for (int i = 0; i < clause->literals.size(); i++) {
        //     //  std::cout << clause->literals[i] << " ";
        // }
        // //  std::cout << "\n ";
        int* pointerToMoveIndex = std::abs(clause->literals[clause->w1]) == assertedVar ? &clause->w1 : &clause->w2;

        int otherPointerIndex = clause->w1 + clause->w2 - *pointerToMoveIndex;

        // std::cout << "POINTERTOMOVE " << *pointerToMove << "!\n";
        // std::cout << "OTHERPOINTER  " << otherPointer << "!\n";

        for (int i = 0; i < clause->literals.size(); i++) {
            // assign as the new pointer a literal that evaluates to true and is not the other watched literal
            if (i != otherPointerIndex && evaluateLiteral(clause->literals[i])) {
                *(pointerToMoveIndex) = i;

                // Remove the reference from assertedVar to the clause
                // std::cout << "REMOVING clause " << *clauseIndex << " from " << assertedVar << "!\n";

                // std::cout << "Set elements before: ";
                // for (const auto& element : *clausesToUpdate) {
                //     //  std::cout << element << " ";
                // }
                // std::cout << std::endl;

                clausesToUpdatePointers->erase(*clauseIndex);

                //  std::cout << "Set elements after: ";
                // for (const auto& element : *clausesToUpdate) {
                //     //  std::cout << element << " ";
                // }
                // //  std::cout << std::endl;

                //  std::cout << "Adding clause " << *clauseIndex << " to " << std::abs(clause->literals[*pointerToMove]) <<
                //  "!\n";
                // Add a reference from new found watched literal to the clause
                clause->literals[*pointerToMoveIndex] > 0
                    ? vars[std::abs(clause->literals[*pointerToMoveIndex])].pos_watched.insert(*clauseIndex)
                    : vars[std::abs(clause->literals[*pointerToMoveIndex])].neg_watched.insert(*clauseIndex);

                /* if ((!evaluateLiteral((clause->literals[otherPointer])) ||
                   vars[std::abs(clause->literals[otherPointer])].getValue() != FREE) &&
                    !vars[std::abs(clause->literals[*pointerToMove])].enqueued &&
                   vars[std::abs(clause->literals[*pointerToMove])].getValue() == FREE) {
                        unitQueue.push(clause->literals[*pointerToMove]);
                        std::cout << "Push " << clause->literals[*pointerToMove] << " on unit queue\n";
                    } */

                break;
            }

            // Search for a distinct new pointer unsuccessful, try UP on otherPointer else backtrack
            if (i + 1 == clause->literals.size()) {
                int otherPointer = clause->literals[otherPointerIndex];
                bool enqueued = vars[std::abs(otherPointer)].enqueued;

                if (vars[std::abs(otherPointer)].getValue() == FREE && !enqueued) {
                    // std::cout << "Push " << clause->literals[otherPointer] << " on unit queue\n";
                    vars[std::abs(otherPointer)].enqueued = true;
                    unitQueue.push(otherPointer);
                } else {
                    if (!evaluateLiteral(otherPointer)) {
                        // std::cout << "INIT BACKTRACK!\n";
                        //  std::cout << "(w1, assig): (" << clause->literals[*pointerToMove] << " "
                        //    << evaluateLiteral(clause->literals[*pointerToMove]) << ") (w2, assig): ("
                        //    << clause->literals[otherPointer] << " " << evaluateLiteral(clause->literals[otherPointer])
                        //    << "), size: " << clause->literals.size() << "\n";
                        backtrack();
                        return;
                    }
                }
            }
        }

        // if ((evaluateLiteral(clause->literals[clause->w1]) && vars[std::abs(clause->literals[clause->w1])].getValue() != FREE)

        // ||
        //     (evaluateLiteral(clause->literals[clause->w2]) && vars[std::abs(clause->literals[clause->w2])].getValue() != FREE))
        //     satClauses.insert(*clauseIndex);
        // else
        //     satClauses.erase(*clauseIndex);
        //  std::cout << "AFTER ALGO:POINTERTOMOVE " << *pointerToMove << "!\n";
    }

        // std::set<int> copy2 = *clausesToMarkSatisfied;
        // for (clauseIndex = copy2.begin(); clauseIndex != copy2.end(); ++clauseIndex) {
        //     Clause* clause = &cnf[*clauseIndex];

            // clause is already satisfied
            // if (satClauses.find(*clauseIndex)) {
            //     break;
            // }

            // clause->sat = std::abs(clause->literals[clause->w1]) == assertedVar ? clause->w1 : clause->w2;

            //  satClauses.insert(*clauseIndex);
        
}

bool evaluateLiteral(int literal) {
    if (vars[std::abs(literal)].getValue() == FREE) return true;

    if (vars[std::abs(literal)].getValue() == TRUE && literal > 0) return true;

    if (vars[std::abs(literal)].getValue() == FALSE && literal < 0) return true;

    return false;
}