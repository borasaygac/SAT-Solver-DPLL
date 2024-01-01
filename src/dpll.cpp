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
        if (unitQueue.empty() && numOfUnassigned < 1) {
            // std::cout << "VORBEII!! \n";

            pthread_exit(0);
        }
        // std::cout << "Current Var :" << curVar << " and current value " << vars[curVar].getValue() << '\n';

        // std::cout << "queue size= " << unitQueue.size() << '\n';
    }
}

void unitPropagate() {
    int unitLiteral;
    while (!unitQueue.empty()) {
        unitLiteral = unitQueue.front();
        // std::cout << "current queue elm= " << unitLiteral << "\n";
        unitQueue.pop();
        vars[std::abs(unitLiteral)].enqueued = false;
        vars[std::abs(unitLiteral)].forced = true;
        (unitLiteral > 0) ? vars[std::abs(unitLiteral)].setValue(TRUE) : vars[std::abs(unitLiteral)].setValue(FALSE);
        // std::cout << "UP variable " << std::abs(unitLiteral) << " set to " << vars[std::abs(unitLiteral)].getValue() << "\n";

        assig.push(std::abs(unitLiteral));

        updateWatchedLiterals(std::abs(unitLiteral));
    }
}

void chooseLiteral() {
    switch (heuristic) {
        case INC:
            while (vars[curVar].getValue() != FREE) curVar++;
            vars[curVar].setValue(TRUE);
            vars[curVar].forced = false;
            assig.push(curVar);
            // std::cout << "CHOOSE_LIT:" << curVar;
            break;
        case DLIS:
            break;
        case DLCS:
            break;
        case MOM:
            break;
        case JW:
            break;
    }
    updateWatchedLiterals(curVar);
}

bool evaluateLiteral(int literal) {
    if (vars[std::abs(literal)].getValue() == FREE) return true;

    if (vars[std::abs(literal)].getValue() == TRUE && literal > 0) return true;

    if (vars[std::abs(literal)].getValue() == FALSE && literal < 0) return true;

    return false;
}
