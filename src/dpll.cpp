#include "../include/cnf.hpp"

void* dpll(void* arg) {
    while (true) {
        pureLiteralElimination();

        propagate();
        dc++;
        chooseLiteral();

        //  std::cout << "Current Var :" << curVar << " and current value " << vars[curVar].getValue() << '\n';

        //  std::cout << "queue size= " << unitQueue.size() << '\n';
    }
}

void pureLiteralElimination() {

    // FOUND PURELIT 1 -> QUEUE
    // FOUND UNIT 2 ->

    // SET PURELIT 1 -> UPDATE -> UNIT 2 -> UPDATE -> NEW PURE LITERALS -> QUEUE -> SET

    int pureLiteral;
    while (!pureLitQueue.empty()) {
        pureLiteral = pureLitQueue.front();
        std::cout << "SET PURELIT " << pureLiteral << "\n";
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
        std::cout << "SET UNIT " << unitLiteral << "\n";
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