#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "../include/cnf.hpp"

bool dpll() {
    while (numOfUnassigned > 0) {
        if (!unitQueue.empty()) {
            unitPropagate();
        } else {
            while (variables[curVar].getValue() != FREE) curVar++;
            variables[curVar].setValue(TRUE);
            updateCNF(curVar);
        }

        std::cout << "Current Var :" << curVar << " and current value " << variables[curVar].getValue() << '\n';

        std::cout << "queue size= " << unitQueue.size() << '\n';
    }

    return true;
}

void unitPropagate() {
    int unitLiteral;
    while (!unitQueue.empty()) {
        unitLiteral = unitQueue.front();
        std::cout << "current queue elm= " << unitLiteral << "\n";
        unitQueue.pop();
        variables[unitLiteral].forced = true;
        (unitLiteral > 0) ? variables[std::abs(unitLiteral)].setValue(TRUE)
                          : variables[std::abs(unitLiteral)].setValue(FALSE);
        std::cout << "UP variable " << std::abs(unitLiteral) << " set to " << variables[std::abs(unitLiteral)].getValue()
                  << "\n";

        updateCNF(std::abs(unitLiteral));
    }
}

void updateCNF(int assertedVar) {
    // watched literals have to point to unassigned or to true evaluating variables

    std::cout << "UPDATING FOR " << assertedVar << "!\n";

    for (int i = 0, size = variables[assertedVar].neg_watched.size(); i < size; i++) {
        int clauseIndex = variables[assertedVar].neg_watched[i];

        // TODO: We need to make reference?
        Clause clause = cnf[clauseIndex];

        int *pointerToMove = std::abs(clause.literals[clause.w1]) == assertedVar ? &clause.w1 : &clause.w2;

        int otherPointer = clause.w1 + clause.w2 - *(pointerToMove);

        for (int i = 0; i < clause.literals.size(); i++) {
            // assign as the new pointer a literal that evaluates to true and is not the other watched literal
            if (evaluateLiteral(clause.literals[i]) && i != otherPointer) {
                *(pointerToMove) = i;
                // TODO: Remove watched link from Variable => Set data structure
                clause.literals[*pointerToMove] > 0
                    ? variables[std::abs(clause.literals[*pointerToMove])].pos_watched.push_back(clauseIndex)
                    : variables[std::abs(clause.literals[*pointerToMove])].neg_watched.push_back(clauseIndex);

                break;
            }

            // Search for a distinct new pointer unsuccessful, try UP on otherPointer else backtrack
            if (i + 1 == size) {
                if (evaluateLiteral(clause.literals[otherPointer]))
                    unitQueue.push(clause.literals[otherPointer]);
                else
                    // backtrack()
                    ;
            }
        }
    }
}

bool evaluateLiteral(int literal) {
    if (variables[std::abs(literal)].getValue() == FREE) return true;

    if (variables[std::abs(literal)].getValue() == TRUE && literal > 0) return true;

    if (variables[std::abs(literal)].getValue() == FALSE && literal < 0) return true;

    return false;
}
