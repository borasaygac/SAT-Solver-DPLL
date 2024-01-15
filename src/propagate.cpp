#include "../include/cnf.hpp"

void propagate() {
    int prop;
    while (!toPropagate.empty()) {
        prop = toPropagate.front();
        // printf("current queue elm = %i\n", prop);
        // std::cout << "current queue elm = " << prop << "\n";
        toPropagate.pop();
        // std::cout << "SET PROP " << prop << "\n";
        //  if(vars[std::abs(prop)].prioPureLit){std::cout << "PURELiT!! " << prop << "\n";}

        int absProp = std::abs(prop);

        (prop > 0) ? vars[absProp].val = TRUE : vars[absProp].val = FALSE;
        vars[absProp].enqueued = false;
        vars[absProp].forced = true;
        // printf("UP variable %i set to %i\n", prop, vars[absProp].val);
        // std::cout << "UP variable " << prop << "set to " << vars[absProp].val << "\n";
        assig.push(absProp);

        update(absProp);
    }
}