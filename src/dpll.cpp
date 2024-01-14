#include "../include/cnf.hpp"

void* dpll(void* arg) {
    while (true) {
        pureLiteralElimination();

        propagate();

        chooseLiteral();
        //  std::cout << "Current Var :" << curVar << " and current value " << vars[curVar].getValue() << '\n';

        //  std::cout << "queue size= " << unitQueue.size() << '\n';
    }
}

void pureLiteralElimination() {
    int pureLiteral;
    while (!pureLitQueue.empty()) {
        pureLiteral = pureLitQueue.front();
        std::cout << "PURELiT!! " << pureLiteral << "\n";
        pureLitQueue.pop();
        vars[std::abs(pureLiteral)].enqueued = false;
        (pureLiteral > 0) ? vars[std::abs(pureLiteral)].val = TRUE : vars[std::abs(pureLiteral)].val = FALSE;
        vars[std::abs(pureLiteral)].forced = true;
        assig.push(std::abs(pureLiteral));

        update(std::abs(pureLiteral));
    }
}

void propagate() {
    int unitLiteral;
    while (!unitQueue.empty()) {
        unitLiteral = unitQueue.front();
        // printf("current queue elm = %i\n", unitLiteral);
        // std::cout << "current queue elm = " << unitLiteral << "\n";
        unitQueue.pop();
        // if(vars[std::abs(unitLiteral)].prioPureLit){std::cout << "PURELiT!! " << unitLiteral << "\n";}
        vars[std::abs(unitLiteral)].enqueued = false;
        vars[std::abs(unitLiteral)].forced = true;
        (unitLiteral > 0) ? vars[std::abs(unitLiteral)].val = TRUE : vars[std::abs(unitLiteral)].val = FALSE;

        // printf("UP variable %i set to %i\n", unitLiteral, vars[std::abs(unitLiteral)].val);
        // std::cout << "UP variable " << unitLiteral << "set to " << vars[std::abs(unitLiteral)].val << "\n";

        assig.push(std::abs(unitLiteral));

        update(std::abs(unitLiteral));
    }
}