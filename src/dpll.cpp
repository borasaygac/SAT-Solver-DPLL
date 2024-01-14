#include "../include/cnf.hpp"

void* dpll(void* arg) {
    while (true) {
        propagate();
        dc++;
        chooseLiteral();

        //  std::cout << "Current Var :" << curVar << " and current value " << vars[curVar].getValue() << '\n';

        //  std::cout << "queue size= " << unitQueue.size() << '\n';
    }
}

void propagate() {
    int prop;
    while (!toPropagate.empty()) {
        prop = toPropagate.front();
        // printf("current queue elm = %i\n", prop);
        // std::cout << "current queue elm = " << prop << "\n";
        toPropagate.pop();
        //std::cout << "SET PROP " << prop << "\n";
        // if(vars[std::abs(prop)].prioPureLit){std::cout << "PURELiT!! " << prop << "\n";}
        vars[std::abs(prop)].enqueued = false;
        vars[std::abs(prop)].forced = true;
        (prop > 0) ? vars[std::abs(prop)].val = TRUE : vars[std::abs(prop)].val = FALSE;

        // printf("UP variable %i set to %i\n", prop, vars[std::abs(prop)].val);
        // std::cout << "UP variable " << prop << "set to " << vars[std::abs(prop)].val << "\n";

        assig.push(std::abs(prop));

        update(std::abs(prop));
    }
}