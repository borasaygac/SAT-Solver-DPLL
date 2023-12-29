#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "../include/cnf.hpp"

void chooseLiteral() {
    switch (heuristic) {
        case INC:
            while (variables[curVar].getValue() != FREE) curVar++;
            variables[curVar].setValue(TRUE);
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
    updateCNF(curVar);
}