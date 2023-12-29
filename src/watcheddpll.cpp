#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "../include/cnf.hpp"

bool watcheddpll(int curVar) {
    // While loop
    std::queue<int> unitQueue;
    int varSize = variables.size();

    while (variables[curVar].val == Assig::FREE) {
        std::cout << "Current Var :" << curVar << " and current value " << variables[curVar].val << '\n';

        // for positive occurances
    }
}