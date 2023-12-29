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
            Clause clause = cnf[variables[curVar].neg_watched[i]];

            int *pointerToMove = -clause.literals[clause.w1] == curVar ? &clause.w1 : &clause.w2;

            int otherPointer = clause.w1 + clause.w2 - *(pointerToMove);

            for (int i = 0; i < clause.literals.size(); i++) {
                // assign as the new pointer a literal that evaluates to true and
                // is
                // not the other watched literal
                if (evaluateLiteral(clause.literals[i]) && i != otherPointer) {
                    *(pointerToMove) = i;
                    break;
                }

                // Search for a distinct new pointer unsuccessful, try UP on
                // otherPointer else backtrack
                if (i + 1 == size) {
                    if (evaluateLiteral(clause.literals[otherPointer]))
                        unitQueue.push(clause.literals[otherPointer]);
                    else
                        // backtrack()
                        ;
                }
            }
        }
        // for negative occurances

        while (!unitQueue.empty()) {
            int current = unitQueue.front();
            std::cout << "current queue elm= " << current << "\n";
            unitQueue.pop();
            variables[current].forced = true;
            cnf[variables[curVar].neg_watched[i]].satLiteral = std::abs(current);
            (current > 0) ? variables[std::abs(current)].val = Assig::TRUE
                          : variables[std::abs(current)].val = Assig::FALSE;
            std::cout << "Value of var after setting= " << variables[std::abs(current)].val << "\n"
                      << " and the number of clause " << variables[curVar].neg_watched[i] << "\n";
            dpll(std::abs(current));
        }
    }

    std::cout << "queue size= " << unitQueue.size() << '\n';
    curVar++;

    return true;
}

bool evaluateLiteral(int literal) {
    if (variables[std::abs(literal)].val == FREE) return true;

    if (variables[std::abs(literal)].val == TRUE && literal > 0) return true;

    if (variables[std::abs(literal)].val == FALSE && literal < 0) return true;

    return false;
}
