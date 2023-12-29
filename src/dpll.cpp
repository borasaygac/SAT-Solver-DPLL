#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "../include/cnf.hpp"

bool dpll(int curVar) {
    // While loop
    std::queue<int> unitQueue;

    while (variables[curVar].val == Assig::FREE) {
        variables[curVar].val = Assig::TRUE;

        std::cout << "Current Var :" << curVar << " and current value " << variables[curVar].val << '\n';

        // watched literals have to point to unassigned or to true evaluating variables
        for (int i = 0, size = variables[curVar].neg_watched.size(); i < size; i++) {
            // TODO
            int clauseIndex = variables[curVar].neg_watched[i];
            Clause clause = cnf[clauseIndex];

            int *pointerToMove = -clause.literals[clause.w1] == curVar ? &clause.w1 : &clause.w2;

            int otherPointer = clause.w1 + clause.w2 - *(pointerToMove);

            for (int i = 0; i < clause.literals.size(); i++) {
                // assign as the new pointer a literal that evaluates to true and
                // is
                // not the other watched literal
                if (evaluateLiteral(clause.literals[i], true) && i != otherPointer) {
                    *(pointerToMove) = i;
                    clause.literals[*pointerToMove] > 0
                        ? variables[std::abs(clause.literals[*pointerToMove])].pos_watched.push_back(clauseIndex)
                        : variables[std::abs(clause.literals[*pointerToMove])].neg_watched.push_back(clauseIndex);

                    break;
                }

                // Search for a distinct new pointer unsuccessful, try UP on
                // otherPointer else backtrack
                if (i + 1 == size) {
                    if (evaluateLiteral(clause.literals[otherPointer], true))
                        unitQueue.push(clause.literals[otherPointer]);
                    else
                        // backtrack()
                        ;
                }
            }
        }

        while (!unitQueue.empty()) {
            int current = unitQueue.front();
            std::cout << "current queue elm= " << current << "\n";
            unitQueue.pop();
            variables[current].forced = true;
            (current > 0) ? variables[std::abs(current)].val = Assig::TRUE
                          : variables[std::abs(current)].val = Assig::FALSE;
            std::cout << "UP variable " << std::abs(current) << " set to "<< variables[std::abs(current)].val << "\n";
            dpll(std::abs(current));
            // [1,2,-3] w1 = 2, UP 3 => 3.val = true;
        }
    }

    std::cout << "queue size= " << unitQueue.size() << '\n';
    curVar++;

    return true;
}

bool evaluateLiteral(int literal, bool dpll) {
    
    if (variables[std::abs(literal)].val == FREE && dpll) return true;

    if (variables[std::abs(literal)].val == TRUE && literal > 0) return true;

    if (variables[std::abs(literal)].val == FALSE && literal < 0) return true;

    return false;
}
